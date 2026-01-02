using System.Text.Json;

namespace JSONRPCServer.Core;

public static class ParamParser
{
    public static (double x, double y) ParseTwoDoubles(JsonElement? p)
    {
        if (p == null) throw new JsonRpcException(-32602, "Missing params");

        if (p.Value.ValueKind == JsonValueKind.Array)
        {
            var arr = p.Value.EnumerateArray().ToArray();
            if (arr.Length < 2) throw new JsonRpcException(-32602, "Expected two parameters");
            return (arr[0].GetDouble(), arr[1].GetDouble());
        }
        else if (p.Value.ValueKind == JsonValueKind.Object)
        {
            if (!p.Value.TryGetProperty("x", out var xEl) || !p.Value.TryGetProperty("y", out var yEl))
                throw new JsonRpcException(-32602, "Named params x and y required");
            return (xEl.GetDouble(), yEl.GetDouble());
        }
        throw new JsonRpcException(-32602, "Invalid params");
    }

    public static int ParseIntParam(JsonElement? p)
    {
        if (p == null) throw new JsonRpcException(-32602, "Missing params");
        if (p.Value.ValueKind == JsonValueKind.Array)
        {
            var arr = p.Value.EnumerateArray().ToArray();
            if (arr.Length < 1) throw new JsonRpcException(-32602, "Expected one parameter");
            return arr[0].GetInt32();
        }
        else if (p.Value.ValueKind == JsonValueKind.Object)
        {
            if (!p.Value.TryGetProperty("x", out var xEl)) throw new JsonRpcException(-32602, "Named param x required");
            return xEl.GetInt32();
        }
        throw new JsonRpcException(-32602, "Invalid params");
    }
}
