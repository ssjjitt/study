using Microsoft.AspNetCore.Authentication;
using Microsoft.AspNetCore.Identity;

namespace lab3b
{
    public class ValidateUserMiddleware
    {
        private readonly RequestDelegate _next;

        public ValidateUserMiddleware(RequestDelegate next)
        {
            _next = next;
        }

        public async Task InvokeAsync(HttpContext context)
        {
            if (context.User.Identity.IsAuthenticated)
            {
                var userManager = context.RequestServices.GetRequiredService<UserManager<IdentityUser>>();
                var user = await userManager.GetUserAsync(context.User);
                if (user == null)
                {
                    await context.SignOutAsync(IdentityConstants.ApplicationScheme);
                    context.Response.Redirect("/Home/Index");
                    return;
                }
            }

            await _next(context);
        }
    }
}