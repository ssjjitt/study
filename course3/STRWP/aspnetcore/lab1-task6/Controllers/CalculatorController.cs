using Microsoft.AspNetCore.Mvc;

namespace lab1_task6.Controllers
{
    [ApiController]
    [Route("[controller]")]
    public class CalculatorController : ControllerBase
    {
        // GET: /calculator
        [HttpGet]
        public IActionResult Get()
        {
            return Content(@"
                <!DOCTYPE html>
                <html lang='en'>
                <head>
                    <meta charset='UTF-8'>
                    <meta name='viewport' content='width=device-width, initial-scale=1.0'>
                    <title>Product Calculator</title>
                </head>
                <body>
                    <h1>Product Calculator</h1>
                    <form id='calculatorForm' method='post' action='/calculator'>
                        <input type='number' name='x' placeholder='Enter x' required>
                        <input type='number' name='y' placeholder='Enter y' required>
                        <button type='submit'>Calculate Product</button>
                    </form>
                    <p id='result'></p>
                </body>
                </html>
            ", "text/html");
        }

        // POST: /calculator
        [HttpPost]
        public IActionResult Post([FromForm] CalcRequest request)
        {
            if (request == null || request.X == 0 || request.Y == 0)
            {
                return BadRequest("Invalid input");
            }

            var product = request.X + request.Y;
            return Content($"Result: {product}", "text/plain");
        }
    }

    public class CalcRequest
    {
        public float X { get; set; }
        public float Y { get; set; }
    }
}
