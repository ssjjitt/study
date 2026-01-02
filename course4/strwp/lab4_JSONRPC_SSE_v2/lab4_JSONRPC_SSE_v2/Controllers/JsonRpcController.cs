using JSONRPCServer.Core;
using Microsoft.AspNetCore.Mvc;

namespace JSONRPCServer.Controllers;

[ApiController]
[Route("[controller]")]
public class JsonRpcController : ControllerBase
{
    [HttpPost]
    public async Task<IActionResult> Post()
    {
        await JsonRpcHandler.HandleRequestAsync(HttpContext);
        return new EmptyResult();
    }
}
