using lab3b.Data;
using lab3b.Models;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Mvc;
using System.Data;

namespace lab3b.Controllers;

public class AdminController(ApplicationDbContext context, UserManager<IdentityUser> userManager, RoleManager<IdentityRole> roleManager, IPasswordHasher<IdentityUser> hasher, SignInManager<IdentityUser> signInManager) : Controller
{
    [Authorize(Roles = "Administrator")]
    public async Task<IActionResult> Index()
    {
        ViewBag.users = context.Users.ToList();
        ViewBag.roles = context.Roles.ToList();
        ViewBag.users_roles = context.UserRoles.ToList();

        var user = await userManager.GetUserAsync(User);
        var user_roles = user != null ? await userManager.GetRolesAsync(user) ?? [] : [];

        ViewBag.user_roles = user_roles;
        return View();
    }

    [Authorize(Roles = "Administrator")]
    [HttpGet]
    [HttpPost]
    public async Task<IActionResult> CreateUser(string name, string password)
    {
        if (HttpContext.Request.Method == HttpMethods.Get) return View();
        if (name == null || password == null)
        {
            return RedirectToAction(nameof(Error), new { message = "Invalid form data input" });
        }
        var existingUser = await userManager.FindByNameAsync(name);
        if (existingUser != null)
        {
            return RedirectToAction(nameof(Error), new { message = "User exists" });
        }
        IdentityUser newuser = new() { UserName = name };
        string passhash = hasher.HashPassword(newuser, password);
        newuser.PasswordHash = passhash;
        await userManager.CreateAsync(newuser);
        return View();
    }

    [Authorize(Roles = "Administrator")]
    [HttpGet]
    [HttpPost]
    public async Task<IActionResult> DeleteUser(string? username)
    {
        if (HttpContext.Request.Method == HttpMethods.Get) return View();
        if (username == null)
        {
            return RedirectToAction(nameof(Error), new { message = "Invalid form data input" });
        }
        IdentityUser? user = null;
        if ((user = await userManager.FindByNameAsync(username)) == null)
        {
            return RedirectToAction(nameof(Error), new { message = "User doesn't exist" });
        }
        var userRoles = await userManager.GetRolesAsync(user);
        if (userRoles.Contains("Administrator"))
        {
            return RedirectToAction(nameof(Error), new { message = "Can't delete Administrator" });
        }
        await userManager.DeleteAsync(user);
        return View();
    }

    [Authorize(Roles = "Administrator")]
    [HttpGet]
    [HttpPost]
    public async Task<IActionResult> Assign(string? name, string? roleName)
    {
        if (HttpContext.Request.Method == HttpMethods.Get) return View();

        if (name == null || roleName == null)
        {
            return RedirectToAction(nameof(Error), new { message = "Invalid form data input" });
        }
        IdentityUser? user;
        if ((user = await userManager.FindByNameAsync(name)) == null)
        {
            return RedirectToAction(nameof(Error), new { message = "User doesn't exist" });
        }
        if (!await roleManager.RoleExistsAsync(roleName))
        {
            return RedirectToAction(nameof(Error), new { message = "Role doesn't exist" });
        }
        await userManager.AddToRoleAsync(user, roleName);
        return View();
    }

    [Authorize(Roles = "Administrator")]
    [HttpGet]
    [HttpPost]
    public async Task<IActionResult> RemoveRole(string? name, string? roleName)
    {
        if (HttpContext.Request.Method == HttpMethods.Get) return View();

        if (name == null || roleName == null)
        {
            return RedirectToAction(nameof(Error), new { message = "Invalid form data input" });
        }
        IdentityUser? user;
        if ((user = await userManager.FindByNameAsync(name)) == null)
        {
            return RedirectToAction(nameof(Error), new { message = "User doesn't exist" });
        }
        if (!await roleManager.RoleExistsAsync(roleName))
        {
            return RedirectToAction(nameof(Error), new { message = "Role doesn't exist" });
        }
        await userManager.RemoveFromRoleAsync(user, roleName);
        return View();
    }

    [Authorize(Roles = "Administrator")]
    [HttpGet]
    [HttpPost]
    public async Task<IActionResult> CreateRole(string roleName)
    {
        if (HttpContext.Request.Method == HttpMethods.Get) return View();
        if (roleName == null)
        {
            return RedirectToAction(nameof(Error), new { message = "Invalid form data input" });
        }
        if (await roleManager.RoleExistsAsync(roleName))
        {
            return RedirectToAction(nameof(Error), new { message = "Role exists" });
        }
        IdentityRole newrole = new() { Name = roleName };
        await roleManager.CreateAsync(newrole);
        return View();
    }

    [Authorize(Roles = "Administrator")]
    [HttpGet]
    [HttpPost]
    public async Task<IActionResult> DeleteRole(string? roleName)
    {
        if (HttpContext.Request.Method == HttpMethods.Get) return View();
        if (roleName == null)
        {
            return RedirectToAction(nameof(Error), new { message = "Invalid form data input" });
        }
        IdentityRole? role;
        if ((role = await roleManager.FindByNameAsync(roleName)) == null)
        {
            return RedirectToAction(nameof(Error), new { message = "Role doesn't exists" });
        }
        await roleManager.DeleteAsync(role);
        return View();
    }

    //[AllowAnonymousOnly]
    [HttpGet]
    [HttpPost]
    public async Task<IActionResult> Register(string username, string password)
    {
        if (HttpContext.Request.Method == HttpMethods.Get) return View();
        if (username == null || password == null)
        {
            return RedirectToAction(nameof(Error), new { message = "Invalid form data input" });
        }
        var existingUser = await userManager.FindByNameAsync(username);
        if (existingUser != null)
        {
            return RedirectToAction(nameof(Error), new { message = "User exists" });
        }
        IdentityUser newuser = new() { UserName = username };
        string passhash = hasher.HashPassword(newuser, password);
        newuser.PasswordHash = passhash;
        var result = await userManager.CreateAsync(newuser);
        if (result.Succeeded)
        {
            await signInManager.SignInAsync(newuser, isPersistent: false);
            return RedirectToAction("Index", "Home");
        }
        else
        {
            return RedirectToAction(nameof(Error), new
            {
                message = string.Join(" ", result.Errors.Select(e => e.Description))
            });
        }
    }

    //[AllowAnonymousOnly]
    [HttpGet]
    [HttpPost]
    public async Task<IActionResult> SignIn(string? username, string password, bool rememberMe)
    {
        if (HttpContext.Request.Method == HttpMethods.Get) return View();
        if (username == null || password == null)
        {
            return RedirectToAction(nameof(Error), new { message = "Invalid form data input" });
        }
        var result = await signInManager.PasswordSignInAsync(username, password, rememberMe, lockoutOnFailure: false);
        if (result.Succeeded)
        {
            return RedirectToAction("Index", "Home");
        }
        else
        {
            return RedirectToAction(nameof(Error), new { message = "Sign in failed" });
        }
    }

    [Authorize]
    [HttpGet]
    [HttpPost]
    public new async Task<IActionResult> SignOut()
    {
        if (HttpContext.Request.Method == HttpMethods.Get) return View();
        string? userName = HttpContext.User.Identity?.Name;
        if (userName != null)
        {
            await signInManager.SignOutAsync();
        }
        return RedirectToAction("Index", "Home");
    }

    [Authorize]
    [HttpGet]
    [HttpPost]
    public async Task<IActionResult> ChangePassword(string currentPassword, string newPassword)
    {
        if (HttpContext.Request.Method == HttpMethods.Get) return View();
        if (currentPassword == null || newPassword == null)
        {
            return RedirectToAction(nameof(Error), new { message = "Invalid form data input" });
        }
        IdentityUser? user = await userManager.GetUserAsync(User);
        var result = await userManager.ChangePasswordAsync(user!, currentPassword, newPassword);
        if (!result.Succeeded)
        {
            return RedirectToAction(nameof(Error), new
            {
                message = string.Join(" ", result.Errors.Select(e => e.Description))
            });
        }
        await signInManager.RefreshSignInAsync(user!);
        return RedirectToAction("Index", "Home");
    }

    //public async Task<IActionResult> ChangePassword(string currentPassword, string newPassword)
    //{
    //    if (HttpContext.Request.Method == HttpMethods.Get) return View();
    //    if (currentPassword == null || newPassword == null)
    //    {
    //        return RedirectToAction(nameof(Error), new { message = "Invalid form data input" });
    //    }

    //    IdentityUser? user = await userManager.GetUserAsync(User);
    //    if (user == null)
    //    {
    //        return RedirectToAction(nameof(Error), new { message = "User not found" });
    //    }

    //    var result = await userManager.ChangePasswordAsync(user, currentPassword, newPassword);
    //    if (!result.Succeeded)
    //    {
    //        return RedirectToAction(nameof(Error), new
    //        {
    //            message = string.Join(" ", result.Errors.Select(e => e.Description))
    //        });
    //    }

    //    await signInManager.RefreshSignInAsync(user);
    //    return RedirectToAction("Index", "Home");
    //}


    [Authorize]
    [HttpGet]
    [HttpPost]
    public async Task<IActionResult> DeleteAccount()
    {
        if (HttpContext.Request.Method == HttpMethods.Get) return View();
        var user = await userManager.GetUserAsync(User);
        if (user == null)
        {
            return RedirectToAction(nameof(Error), new { message = "User not found" });
        }
        var userRoles = await userManager.GetRolesAsync(user);
        if (userRoles.Contains("Administrator"))
        {
            return RedirectToAction(nameof(Error), new { message = "Can't delete Administrator" });
        }
        await signInManager.SignOutAsync();
        await userManager.DeleteAsync(user);

        return RedirectToAction("Index", "Home");
    }

    [ResponseCache(Duration = 0, Location = ResponseCacheLocation.None, NoStore = true)]
    public IActionResult Error(string message)
    {
        var model = new ErrorViewModel
        {
            Message = message
        };
        return View("Error", model);
    }
}