using Microsoft.AspNetCore.Mvc;
namespace lab1.Controllers
{
    [ApiController]
    [Route("[controller]")]
    public class CalculatorController : ControllerBase
    {
        [HttpGet]
        public IActionResult Get()
        {
            // GET: /calculator
            return Content(@"
                <!DOCTYPE html>
                <html lang='en'>
                <head>
                    <meta charset='UTF-8'>
                    <meta name='viewport' content='width=device-width, initial-scale=1.0'>
                    <title>Calculator</title>
                    <script>
                        function calculate() {
                            var x = document.getElementById('inputX').value;
                            var y = document.getElementById('inputY').value;

                            var xhr = new XMLHttpRequest();
                            xhr.open('POST', '/calculator', true);
                            xhr.setRequestHeader('Content-Type', 'application/json');

                            xhr.onreadystatechange = function () {
                                if (xhr.readyState === 4 && xhr.status === 200) {
                                    var result = JSON.parse(xhr.responseText);
                                    document.getElementById('result').innerText = 'Result: ' + xhr.responseText;
                                }
                            };

                            xhr.send(JSON.stringify({ x: +x, y: +y }));
                            console.log('x:', parseFloat(x), 'y:', parseFloat(y));
                        }
                    </script>
                </head>
                <body>
                    <h1>Calculator</h1>
                    <input type='number' id='inputX' placeholder='x' required>
                    <input type='number' id='inputY' placeholder='y' required>
                    <button onclick='calculate()'>=</button>
                    <p id='result'></p>
                </body>
                </html>
            ", "text/html");
        }

        // POST: /calculator
        [HttpPost]
        public IActionResult Post([FromBody] CalcRequest request)
        {
            if (request == null || request.X == 0 || request.Y == 0)
            {
                return BadRequest("Invalid input");
            }

            var product = request.X * request.Y;
            Console.WriteLine($"Product: {product}");
            return Ok(new { Product = product });
        }
    }

    public class CalcRequest
    {
        public float X { get; set; }
        public float Y { get; set; }
    }
}
