using JSONRPCServer.Core;

var builder = WebApplication.CreateBuilder(args);
var app = builder.Build();

app.MapPost("/jsonrpc", JsonRpcHandler.HandleRequestAsync);

app.Run();
