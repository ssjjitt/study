using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.Filters;

namespace lab3b;

//кастомный атрибут, возвращает 404  
public class AllowAnonymousOnlyAttribute : ActionFilterAttribute
{
    public override void OnActionExecuting(ActionExecutingContext context)
    {
        var user = context.HttpContext.User;

        if (user.Identity != null && user.Identity.IsAuthenticated)
        {
            context.Result = new NotFoundResult();
        }

        base.OnActionExecuting(context);
    }
}