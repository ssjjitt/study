using lab2b_task2.Models;
using Microsoft.AspNetCore.Mvc;
using System.Diagnostics;

namespace lab2b_task2.Controllers
{
    [Route("it")]
    public class TAResearchController : Controller
    {
        [HttpGet("n/{n:int}/{string}")]
        public IActionResult M04(int n, string str)
        {
            return Content($"GET:M04:/{n}/{str}");
        }

        [HttpGet("b/{b:bool}/{letters}")]
        public IActionResult M05(bool b, string letters)
        {
            return Content($"GET:M05:/{b}/{letters}");
        }

        [HttpPost("b/{b:bool}/{letters}")]
        public IActionResult M05Post(bool b, string letters)
        {
            return Content($"POST:M05:/{b}/{letters}");
        }
        
        [HttpGet("f/{f:float}/{string:minlength(2):maxlength(5)}")]
        public IActionResult M06(float f, string str)
        {
            return Content($"GET:M06:/{f}/{str}");
        }

        [HttpDelete("f/{f:float}/{string:minlength(2):maxlength(5)}")]
        public IActionResult M06Delete(float f, string str)
        {
            return Content($"DELETE:M06:/{f}/{str}");
        }

        [HttpPut("letters/{letters:minlength(3):maxlength(4)}/{n:int:range(100,200)}")]
        public IActionResult M07(string letters, int n)
        {
            return Content($"PUT:M07:/{letters}/{n}/");
        }

        [HttpPost("{mail:regex(^\\S+@\\S+\\.\\S+$)}")]
        public IActionResult M08(string mail)
        {
            return Content($"POST:M08:/mail/{mail}");
        }
    }
}
