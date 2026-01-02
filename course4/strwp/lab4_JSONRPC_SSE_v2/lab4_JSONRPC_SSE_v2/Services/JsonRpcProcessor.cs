using JSONRPCServer.Core;
using System.Text.Json;
using JSONRPCServer.Infrastructure;
using JSONRPCServer.Services;

namespace JSONRPCServer.Services
{
    public static class JsonRpcProcessor
    {
        public static async Task<JsonElement?> ProcessRequestAsync(JsonElement el)
        {
            if (!el.TryGetProperty("jsonrpc", out var version) || version.GetString() != "2.0" ||
                !el.TryGetProperty("method", out var methodEl))
            {
                return JsonRpcResponse.Error(null, -32600, "Invalid Request");
            }

            string method = methodEl.GetString() ?? string.Empty;
            JsonElement? id = el.TryGetProperty("id", out var idEl) ? idEl : null;
            JsonElement? paramsEl = el.TryGetProperty("params", out var p) ? p : null;

            SseService? sse = null;
            try
            {
                sse = ServiceLocator.Provider?.GetService(typeof(SseService)) as SseService;
            }
            catch
            {
            }

            try
            {
                object? result = method.ToUpperInvariant() switch
                {
                    "SUM" => MathService.Sum(paramsEl),
                    "SUB" => MathService.Sub(paramsEl),
                    "MUL" => MathService.Mul(paramsEl),
                    "DIV" => MathService.Div(paramsEl),
                    "FACT" => MathService.Fact(paramsEl),
                    _ => throw new JsonRpcException(-32601, "Method not found")
                };
                
                if (sse != null)
                {
                    var data = new { result = result };
                    await sse.BroadcastAsync(method.ToUpperInvariant(), data);
                }

                if (id == null || id.Value.ValueKind == JsonValueKind.Null)
                    return null;

                return JsonRpcResponse.Success(id.Value, result);
            }
            catch (JsonRpcException jex)
            {
                if (sse != null)
                {
                    var errorData = new { error = jex.Message };
                    await sse.BroadcastAsync(method.ToUpperInvariant(), errorData);
                }

                return JsonRpcResponse.Error(id, jex.Code, jex.Message);
            }
            catch (Exception ex)
            {
                if (sse != null)
                {
                    var errorData = new { error = ex.Message };
                    await sse.BroadcastAsync(method.ToUpperInvariant(), errorData);
                }
                return JsonRpcResponse.Error(id, -32603, $"Internal error: {ex.Message}");
            }
        }
    }
}
