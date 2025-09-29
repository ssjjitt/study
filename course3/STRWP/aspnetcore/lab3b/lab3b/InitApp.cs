using lab3;
using lab3b.Data;
using Microsoft.AspNetCore.Identity;

namespace lab3b;

public class InitApp
{
    readonly UserManager<IdentityUser>? um;
    readonly RoleManager<IdentityRole>? rm;
    readonly ApplicationDbContext? db;
    readonly IPasswordHasher<IdentityUser>? hs;
    readonly ILogger<Program>? lg;
    const string adminpass = "admin";
    //const string adminemail = "admin@gmail.com";
    const string adminname = "admin";
    const string adminrole = "Administrator";

    public InitApp(WebApplication? app)
    {
        var scope = app?.Services.CreateScope();
        if (scope != null)
        {
            var services = scope.ServiceProvider;
            um = services?.GetRequiredService<UserManager<IdentityUser>>();
            rm = services?.GetRequiredService<RoleManager<IdentityRole>>();
            db = services?.GetRequiredService<ApplicationDbContext>();
            hs = services?.GetRequiredService<IPasswordHasher<IdentityUser>>();
            lg = services?.GetRequiredService<ILogger<Program>>();
        }
    }

    public async Task InitIdentity()
    {
        try
        {
            if (db == null) throw new Exception("bad ApplicationDbContext");
            if (hs == null) throw new Exception("bad IPasswordHasher");
            if (um == null) throw new Exception("bad UserManager");
            if (rm == null) throw new Exception("bad RoleManager");
            if (lg == null) throw new Exception("bad ILogger");
            if (!db.Users.Any())
            {
                IdentityUser newuser = new() { UserName = adminname };
                if ((await um.CreateAsync(newuser, adminpass)).Succeeded)
                {
                    lg.LogInformation($"{adminname}/{adminpass}");
                }
                if (!await rm.RoleExistsAsync(adminname))
                {
                    IdentityRole newrole = new() { Name = adminrole };
                    if ((await rm.CreateAsync(newrole)).Succeeded)
                    {
                        lg.LogInformation($"create role {adminrole}");
                    }
                }
                IdentityUser? user = await um.FindByNameAsync(adminname);
                if (user != null) await um.AddToRoleAsync(user, adminrole);
            }
        }
        catch (Exception ex) { lg?.LogError(ex, "Error INIT"); }
    }
}