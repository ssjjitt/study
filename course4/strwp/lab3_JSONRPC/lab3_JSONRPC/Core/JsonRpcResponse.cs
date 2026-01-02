using System.Text.Json;

namespace JSONRPCServer.Core;

public static class JsonRpcResponse
{
    public static JsonElement Success(JsonElement id, object result)
    {
        using var doc = JsonDocument.Parse(JsonSerializer.Serialize(new { jsonrpc = "2.0", result, id }));
        return doc.RootElement.Clone();
    }

    public static JsonElement Error(JsonElement? id, int code, string message)
    {
        var errObj = new { jsonrpc = "2.0", error = new { code, message }, id = id?.GetRawText() };
        using var doc = JsonDocument.Parse(JsonSerializer.Serialize(errObj));
        return doc.RootElement.Clone();
    }
}
