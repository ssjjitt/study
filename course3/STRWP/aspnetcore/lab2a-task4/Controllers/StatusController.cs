using lab2a_task4.Models;
using Microsoft.AspNetCore.Mvc;
using System.Diagnostics;

namespace lab2a_task4.Controllers
{
    public class StatusController : Controller
    {
        private static readonly Random _random = new Random();

        [HttpGet]
        public IActionResult S200()
        {
            int statusCode = _random.Next(200, 300);
            return StatusCode(statusCode, $"{statusCode}"); 
        }

        [HttpGet]
        public IActionResult S300()
        {
            int statusCode = _random.Next(300, 400);
            return StatusCode(statusCode, $"{statusCode}");
        }

        [HttpGet]
        public IActionResult S500()
        {
            //int zero = 0;
            //int result = 1 / zero; 
            int statusCode = _random.Next(500, 600);
            return StatusCode(statusCode, $"pickme error {statusCode}");
        }
    }
}
