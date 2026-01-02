using Microsoft.AspNetCore.Authentication.JwtBearer;
using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Identity.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore;
using Microsoft.IdentityModel.Tokens;
using Results.Authenticate.Services;
using Results.Authenticate.Services.Abstractions;
using ResultsCollection.BSTU.Results.Collections;
using ResultsCollection.BSTU.Results.Collections.Abstractions;
using System.Text;

namespace REST_API
{
    public class Program
    {
        public static void Main(string[] args)
        {
            var builder = WebApplication.CreateBuilder(args);

            builder.Services.AddControllers();
            builder.Services.AddEndpointsApiExplorer();
            builder.Services.AddSwaggerGen();

            builder.Services.AddTransient<IResultsRepository, ResultsRepository>(); // регистрация сервисов
            builder.Services.AddTransient<IAuthenticateService, AuthenticateService>();

            builder.Services.AddDbContext<IdentityDbContext<IdentityUser>>(options =>
            {
                options.UseInMemoryDatabase("InMemory");
            });

            builder.Services.AddIdentity<IdentityUser, IdentityRole>()
                .AddEntityFrameworkStores<IdentityDbContext<IdentityUser>>()
                .AddDefaultTokenProviders();

            builder.Services.AddAuthentication(options =>
            {
                options.DefaultAuthenticateScheme = JwtBearerDefaults.AuthenticationScheme;
                options.DefaultChallengeScheme = JwtBearerDefaults.AuthenticationScheme;
            })
            .AddJwtBearer(options =>
            {
                options.TokenValidationParameters = new TokenValidationParameters
                {
                    ValidateIssuer = true, // кто выдал
                    ValidateAudience = true, // предназнаечн
                    ValidateLifetime = true,
                    ValidateIssuerSigningKey = true, // подпись
                    ValidIssuer = builder.Configuration["Jwt:Issuer"],
                    ValidAudience = builder.Configuration["Jwt:Audience"],
                    IssuerSigningKey = new SymmetricSecurityKey(
                        Encoding.UTF8.GetBytes(builder.Configuration["Jwt:Key"]
                            ?? throw new Exception("JWT Key is not defined")
                    ))
                };
            });

            var app = builder.Build();

            using (var scope = app.Services.CreateScope())
            {
                var userManager = scope.ServiceProvider.GetRequiredService<UserManager<IdentityUser>>();
                var roleManager = scope.ServiceProvider.GetRequiredService<RoleManager<IdentityRole>>();
                var passwordHasher = scope.ServiceProvider.GetRequiredService<IPasswordHasher<IdentityUser>>();

                var readerRole = "READER";
                var writerRole = "WRITER";

                List<string> roles = [readerRole, writerRole];

                foreach (var role in roles)
                {
                    if (!roleManager.RoleExistsAsync(role).Result)
                    {
                        roleManager.CreateAsync(new IdentityRole(role)).GetAwaiter().GetResult();
                    }
                }

                var reader = new IdentityUser
                {
                    UserName = "reader",
                    PasswordHash = passwordHasher.HashPassword(null!, "readerpass")
                };
                var writer = new IdentityUser
                {
                    UserName = "writer",
                    PasswordHash = passwordHasher.HashPassword(null!, "writerpass")
                };
                var admin = new IdentityUser
                {
                    UserName = "admin",
                    PasswordHash = passwordHasher.HashPassword(null!, "adminpass")
                };

                List<IdentityUser> users = [reader, writer, admin];

                foreach (var user in users)
                {
                    var existingUser = userManager.FindByNameAsync(user.UserName!).Result;

                    if (existingUser is null)
                    {
                        userManager.CreateAsync(user).GetAwaiter().GetResult();

                        if (user.UserName == "reader")
                        {
                            userManager.AddToRoleAsync(user, "READER").GetAwaiter().GetResult();
                        } 
                        else if (user.UserName == "writer")
                        {
                            userManager.AddToRoleAsync(user, "WRITER").GetAwaiter().GetResult();
                        }
                        else
                        {
                            userManager.AddToRolesAsync(user, ["READER", "WRITER"]).GetAwaiter().GetResult();
                        }
                    }
                }
            }

            if (app.Environment.IsDevelopment())
            {
                app.UseSwagger();
                app.UseSwaggerUI();
            }

            app.UseAuthorization();

            app.MapControllers();

            app.Run();
        }
    }
}
