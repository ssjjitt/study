var builder = WebApplication.CreateBuilder(args);

builder.Services.AddControllersWithViews();

var app = builder.Build();

app.UseHttpsRedirection();
app.UseStaticFiles();

app.UseRouting();

#pragma warning disable ASP0014 // Suggest using top level route registrations
app.UseEndpoints(endpoints =>
{
    app.MapControllerRoute(
        name: "M01",
        pattern: "MResearch/{M01?}/a",
        defaults: new { controller = "TMResearch", action = "M01" });

    app.MapControllerRoute(
       name: "M01",
       pattern: "MResearch/M01/{1?}",
       defaults: new { controller = "TMResearch", action = "M01" });

    app.MapControllerRoute(
        name: "M01",
        pattern: "",
        defaults: new { controller = "TMResearch", action = "M01" });

    app.MapControllerRoute(
        name: "M01",
        pattern: "V2/MResearch/M01",
        defaults: new { controller = "TMResearch", action = "M01" });

    app.MapControllerRoute(
        name: "M01",
        pattern: "V3/MResearch/{string}/M01",
        defaults: new { controller = "TMResearch", action = "M01" });

    app.MapControllerRoute(
        name: "M02",
        pattern: "/V2",
        defaults: new { controller = "TMResearch", action = "M02" });

    app.MapControllerRoute(
        name: "M02",
        pattern: "V2/MResearch/{M02?}",
        defaults: new { controller = "TMResearch", action = "M02" });

    app.MapControllerRoute(
        name: "M02",
        pattern: "/MResearch/M02",
        defaults: new { controller = "TMResearch", action = "M02" });

    app.MapControllerRoute(
       name: "M02",
       pattern: "V3/MResearch/{string}/M02",
       defaults: new { controller = "TMResearch", action = "M02" });

    app.MapControllerRoute(
       name: "M03",
       pattern: "/V3",
       defaults: new { controller = "TMResearch", action = "M03" });

    app.MapControllerRoute(
     name: "M03",
     pattern: "V3/MResearch/{string}/",
     defaults: new { controller = "TMResearch", action = "M03" });

    app.MapControllerRoute(
     name: "M03",
     pattern: "V3/MResearch/{string}/M03",
     defaults: new { controller = "TMResearch", action = "M03" });

    app.MapControllerRoute(
     name: "MXX",
     pattern: "{*uri}",
     defaults: new { controller = "TMResearch", action = "MXX" });

});
#pragma warning restore ASP0014 // Suggest using top level route registrations

app.Run();
/*
https://localhost:7033/MResearch/M01/1
https://localhost:7033/MResearch/M01
https://localhost:7033/MResearch
https://localhost:7033/
https://localhost:7033/V2/MResearch/M01
https://localhost:7033/V3/MResearch/string/M01
https://localhost:7033/V2
https://localhost:7033/V2/MResearch
https://localhost:7033/V2/MResearch/M02
https://localhost:7033/MResearch/M02 !
https://localhost:7033/V3/MResearch/string/M02
https://localhost:7033/V3
https://localhost:7033/V3/MResearch/string/
https://localhost:7033/V3/MResearch/string/M03
https://localhost:7033/pimpim
 */