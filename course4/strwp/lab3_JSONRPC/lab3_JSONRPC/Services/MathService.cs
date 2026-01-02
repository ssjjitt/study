using JSONRPCServer.Core;
using System.Numerics;
using System.Text.Json;

namespace JSONRPCServer.Services;

public static class MathService
{
    public static double Sum(JsonElement? p)
    {
        var (x, y) = ParamParser.ParseTwoDoubles(p);
        return x + y;
    }

    public static double Sub(JsonElement? p)
    {
        var (x, y) = ParamParser.ParseTwoDoubles(p);
        return x - y;
    }

    public static double Mul(JsonElement? p)
    {
        var (x, y) = ParamParser.ParseTwoDoubles(p);
        return x * y;
    }

    public static double Div(JsonElement? p)
    {
        var (x, y) = ParamParser.ParseTwoDoubles(p);
        if (y == 0) throw new JsonRpcException(-32000, "Division by zero");
        return x / y;
    }

    public static int Fact(JsonElement? p)
    {
        int n = ParamParser.ParseIntParam(p);
        if (n < 0) throw new JsonRpcException(-32602, "Negative factorial");
        BigInteger res = 1;
        for (int i = 2; i <= n; i++) res *= i;
        if (res > int.MaxValue) throw new JsonRpcException(-32001, "Result exceeds int range");
        return (int)res;
    }
}
