using ASPCMVC08.Attributes;
using ASPCMVC08.Models;
using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Mvc;
using System.Diagnostics;

namespace ASPCMVC08.Controllers;

[CheckOnExist]
[ReAuthorize]
public class HomeController : Controller
{
    private readonly ILogger<HomeController> _logger;
    private readonly SignInManager<User> signInManager;
    private readonly UserManager<User> userManager;

    public HomeController(ILogger<HomeController> logger, SignInManager<User> signInManager, UserManager<User> userManager)
    {
        _logger = logger;
        this.signInManager = signInManager;
        this.userManager = userManager;
    }

    public async Task<IActionResult> Index()
    {
        try
        {
            if (!(User.Identity?.IsAuthenticated ?? false))
                return View();

            var user = await userManager.GetUserAsync(User);
            ViewBag.IsAuthorized = true;
            ViewBag.Username = user.UserName;
            ViewBag.Roles = await userManager.GetRolesAsync(user);
        }
        catch (Exception e)
        {
            await Console.Out.WriteLineAsync(e.Message);
        }
        return View();
    }

    public IActionResult Privacy()
    {
        return View();
    }

    [ResponseCache(Duration = 0, Location = ResponseCacheLocation.None, NoStore = true)]
    public IActionResult Error()
    {
        return View(new ErrorViewModel { RequestId = Activity.Current?.Id ?? HttpContext.TraceIdentifier });
    }
}
