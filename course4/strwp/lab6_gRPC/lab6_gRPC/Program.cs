using GrpcServer;
using lab6_gRPC.Services;

var builder = WebApplication.CreateBuilder(args);

builder.Services.AddGrpc();

var app = builder.Build();

app.UseRouting();
app.UseGrpcWeb();

app.MapGrpcService<CalculatorService>().EnableGrpcWeb();
app.MapGet("/", () => "gRPC is running");

app.Run();
