using JSONRPCServer.Services;
using JSONRPCServer.Infrastructure;

var builder = WebApplication.CreateBuilder(args);

builder.Services.AddSingleton<SseService>();

if (builder.Environment.IsDevelopment())
{
    builder.Services.AddCors(options =>
    {
        options.AddPolicy("AllowFrontend", policy =>
        {
            policy.WithOrigins("*")
               .AllowAnyHeader()
               .AllowAnyMethod();
        });
    });
}

var app = builder.Build();

ServiceLocator.Provider = app.Services; // доступ к DI-контейнеру

if (app.Environment.IsDevelopment())
{
    app.UseCors("AllowFrontend");
}

app.MapGet("/events", async (HttpContext ctx, SseService sseService) =>
{
    ctx.Response.Headers.Append("Content-Type", "text/event-stream");
    ctx.Response.Headers.Append("Cache-Control", "no-cache");
    ctx.Response.Headers.Append("Connection", "keep-alive");

    var (id, reader) = sseService.Subscribe();
  
    var cancellation = ctx.RequestAborted;

    try
    {
        await foreach (var message in reader.ReadAllAsync(cancellation))
        {
            try
            {
                await ctx.Response.WriteAsync(message, cancellation);
                await ctx.Response.Body.FlushAsync(cancellation);
            }
            catch
            {
                break;
            }
        }
    }
    catch (OperationCanceledException) { 
    }
    finally
    {
        sseService.Unsubscribe(id);
    }
});

app.MapPost("/jsonrpc", JSONRPCServer.Core.JsonRpcHandler.HandleRequestAsync);

app.Run();
