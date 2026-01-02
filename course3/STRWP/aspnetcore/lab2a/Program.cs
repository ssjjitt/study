using Microsoft.AspNetCore.Builder;
using Microsoft.Extensions.DependencyInjection;

var builder = WebApplication.CreateBuilder(args);

var app = builder.Build();

app.UseStaticFiles(); 

app.UseRouting();

app.MapGet("/Index.html", () => Results.File("wwwroot/Index.html"));

app.Run();