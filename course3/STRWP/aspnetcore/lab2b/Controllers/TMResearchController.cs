using lab2b.Models;
using Microsoft.AspNetCore.Mvc;
using System.Diagnostics;

namespace lab2b.Controllers
{
    public class TMResearchController : Controller
    {
        public IActionResult M01(string input)
        {
            return Content($"GET:M01 {input}");
        }

        public IActionResult M02(string input)
        {
            return Content($"GET:M02 {input}");
        }

        public IActionResult M03(string input)
        {
            return Content($"GET:M03 {input}");
        }

        public IActionResult MXX(string url)
        {
            return Content($"GET:MXX");
        }
    }
}
