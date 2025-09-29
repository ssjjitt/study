using Microsoft.AspNetCore.Mvc;

// https://localhost:7160/gdv?ParmA=oxo&ParmB=xox

namespace lab1.Controllers
{
    [ApiController]
    [Route("[controller]")]
    public class GDVController : ControllerBase
    {
        // 1
        [HttpGet]
        public IActionResult Get([FromQuery] string ParmA, [FromQuery] string ParmB)
        {
            var response = $"GET-Http-GDV:ParmA = {ParmA}, ParmB = {ParmB}";
            return Content(response);
        }

        // 2
        [HttpPost]
        public IActionResult Post([FromBody] RequestModel model)
        {
            var responseText = $"POST-Http-GDV:ParmA = {model.ParmA},ParmB = {model.ParmB}";
            return Content(responseText, "text/plain");
        }

        // 3
        [HttpPut]
        public IActionResult Put([FromBody] RequestModel model)
        {
            var responseText = $"PUT-Http-GDV:ParmA = {model.ParmA},ParmB = {model.ParmB}";
            return Content(responseText, "text/plain");
        }

        // 4
        [HttpPost("calc")]
        public IActionResult Calc([FromBody] Calc request)
        {
            if (request == null)
            {
                return BadRequest("Invalid request");
            }

            var sum = request.X + request.Y;
            return Ok(new { Sum = sum });
        }
    }
    public class RequestModel
    {
        public string ParmA { get; set; }
        public string ParmB { get; set; }
    }

    public class Calc
    {
        public int X { get; set; }
        public int Y { get; set; }
    }
}
