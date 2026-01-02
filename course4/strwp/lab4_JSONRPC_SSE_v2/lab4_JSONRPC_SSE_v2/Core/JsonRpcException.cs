namespace JSONRPCServer.Core;

public class JsonRpcException : Exception
{
    public int Code { get; }
    public JsonRpcException(int code, string message) : base(message)
    {
        Code = code;
    }
}
