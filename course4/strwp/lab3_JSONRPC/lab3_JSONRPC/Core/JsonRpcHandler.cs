using JSONRPCServer;
using JSONRPCServer.Services;
using System.Text.Json;

namespace JSONRPCServer.Core;

public static class JsonRpcHandler
{
    public static async Task HandleRequestAsync(HttpContext ctx)
    {
        ctx.Response.ContentType = "application/json";
        using var doc = await JsonDocument.ParseAsync(ctx.Request.Body);

        JsonElement root = doc.RootElement;
        var responses = new List<JsonElement>();

        if (root.ValueKind == JsonValueKind.Array)
        {
            foreach (var el in root.EnumerateArray())
            {
                var resp = await JsonRpcProcessor.ProcessRequestAsync(el);
                if (resp.HasValue) responses.Add(resp.Value);
            }

            if (responses.Count == 0)
            {
                ctx.Response.StatusCode = 204;
                return;
            }

            await JsonSerializer.SerializeAsync(ctx.Response.Body, responses);
        }
        else
        {
            var resp = await JsonRpcProcessor.ProcessRequestAsync(root);
            if (!resp.HasValue)
            {
                ctx.Response.StatusCode = 204;
                return;
            }
            await JsonSerializer.SerializeAsync(ctx.Response.Body, resp.Value);
        }
    }
}
