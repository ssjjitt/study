using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;

namespace lab3b;

[Authorize(Roles = "Employee,Master")]
public class CalcController : Controller
{
    [HttpGet]
    public ViewResult Index() => View();

    [HttpGet]
    public ViewResult Sum() => View();
    [HttpGet]
    public ViewResult Sub() => View();
    [HttpGet]
    public ViewResult Mul() => View();
    [HttpGet]
    public ViewResult Div() => View();

    [HttpPost]
    public ViewResult Sum(string? xStr, string? yStr)
    {
        PerformOperator((a, b) => a + b, xStr, yStr);
        return View();
    }

    [HttpPost]
    public ViewResult Sub(string? xStr, string? yStr)
    {
        PerformOperator((a, b) => a - b, xStr, yStr);
        return View();
    }

    [HttpPost]
    public ViewResult Mul(string? xStr, string? yStr)
    {
        PerformOperator((a, b) => a * b, xStr, yStr);
        return View();
    }

    [HttpPost]
    public ViewResult Div(string? xStr, string? yStr)
    {
        PerformOperator((a, b) => a / b, xStr, yStr);
        return View();
    }

    private void PerformOperator(Func<float, float, float> op, string? xStr, string? yStr)
    {
        try
        {
            bool xIsValid = float.TryParse(xStr, out var x);
            bool yIsValid = float.TryParse(yStr, out var y);
            ViewBag.x = xIsValid ? x : 0;
            ViewBag.y = yIsValid ? y : 0;
            if (!xIsValid)
            {
                throw new ArgumentException("x is invalid");
            }
            if (!yIsValid)
            {
                throw new ArgumentException("y is invalid");
            }
            ViewBag.z = op(x, y);
        }
        catch (Exception err)
        {
            ViewBag.z = null;
            ViewBag.Error = $"-- ERROR: {err.Message} --";
        }
    }
}