using Microsoft.AspNetCore.Routing.Constraints;

var builder = WebApplication.CreateBuilder(args);

builder.Services.AddControllersWithViews();

var app = builder.Build();

app.UseHttpsRedirection();
app.UseStaticFiles();

app.UseRouting();

app.UseAuthorization();

app.MapControllerRoute(
    name: "default",
    pattern: "{controller=Home}/{action=Index}/{id?}");

app.Run();
/*
https://localhost:7029/it/n/5/pimpim

https://localhost:7029/it/b/true/pimpim
https://localhost:7029/it/b/false/pimpim

https://localhost:7029/it/f/3.14/abc
https://localhost:7029/it/f/3.4/pimpim

https://localhost:7029/it/pim/120
https://localhost:7029/it/ssjjitt@gmail.com
*/
