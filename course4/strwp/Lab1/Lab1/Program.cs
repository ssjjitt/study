using System.Text.Json;

var builder = WebApplication.CreateBuilder(args);

builder.Services.AddDistributedMemoryCache();
builder.Services.AddSession(options =>
{
    options.IdleTimeout = TimeSpan.FromMinutes(1);
    options.Cookie.HttpOnly = true;
    options.Cookie.IsEssential = true;
});

var app = builder.Build();

app.UseForwardedHeaders();
app.UseSession();
app.UseStaticFiles();

int CalculateCurrentResult(ISession session)
{
    var baseResult = session.GetInt32("BASE_RESULT") ?? 0;
    var stack = GetStack(session);
    
    return stack.Count > 0 ? baseResult + stack.Peek() : baseResult;
}

Stack<int> GetStack(ISession session)
{
    var stackJson = session.GetString("STACK");
    if (!string.IsNullOrEmpty(stackJson))
    {
        try
        {
            var list = JsonSerializer.Deserialize<List<int>>(stackJson);
            if (list is { Count: > 0 })
            {
                return new Stack<int>(list);
            }
        }
        catch
        {
            return new Stack<int>();
        }
    }
    return new Stack<int>();
}

void SaveStack(ISession session, Stack<int> stack)
{
    if (stack.Count > 0)
    {
        var list = new List<int>(stack);
        list.Reverse();
        session.SetString("STACK", JsonSerializer.Serialize(list));
    }
    else
    {
        session.Remove("STACK");
    }
}

app.MapGet("/", () => Results.Redirect("/test.html"));

app.MapGet("/test.html", async context =>
{
    context.Response.ContentType = "text/html";
    await context.Response.SendFileAsync(Path.Combine("wwwroot", "test.html"));
});

app.Map("/{path}", async context =>
{
    var path = context.Request.RouteValues["path"] as string;
    
    if (string.IsNullOrEmpty(path) || !path.EndsWith(".GDV", StringComparison.OrdinalIgnoreCase))
    {
        context.Response.StatusCode = 404;
        await context.Response.WriteAsync("Use *.GDV");
        return;
    }

    context.Response.ContentType = "application/json";

    switch (context.Request.Method)
    {
        case "GET":
            {
                var result = CalculateCurrentResult(context.Session);
                await context.Response.WriteAsync($"{{\"RESULT\": {result}}}");
                break;
            }

        case "POST":
            {
                if (context.Request.Query.TryGetValue("RESULT", out var resultValue) &&
                    int.TryParse(resultValue, out int newResult))
                {
                    context.Session.SetInt32("BASE_RESULT", newResult);

                    var currentResult = CalculateCurrentResult(context.Session);
                    await context.Response.WriteAsync($"{{\"RESULT\": {currentResult}, \"status\": \"BASE_RESULT updated to {newResult}\"}}");
                }
                else
                {
                    context.Response.StatusCode = 400;
                    await context.Response.WriteAsync("{\"error\": \"Invalid or missing RESULT parameter\"}");
                }
                break;
            }

        case "PUT":
            {
                if (context.Request.Query.TryGetValue("ADD", out var addValue) &&
                    int.TryParse(addValue, out int valueToAdd))
                {
                    var stack = GetStack(context.Session);
                    stack.Push(valueToAdd);
                    SaveStack(context.Session, stack);
                    
                    var currentResult = CalculateCurrentResult(context.Session);
                    await context.Response.WriteAsync($"{{\"RESULT\": {currentResult}, \"status\": \"Value {valueToAdd} pushed to stack\"}}");
                }
                else
                {
                    context.Response.StatusCode = 400;
                    await context.Response.WriteAsync("{\"error\": \"Invalid or missing ADD parameter\"}");
                }
                break;
            }

        case "DELETE":
            {
                var stack = GetStack(context.Session);
                if (stack.Count > 0)
                {
                    var poppedValue = stack.Pop();
                    SaveStack(context.Session, stack);
                    
                    var currentResult = CalculateCurrentResult(context.Session);
                    await context.Response.WriteAsync($"{{\"RESULT\": {currentResult}, \"status\": \"Value {poppedValue} popped from stack\"}}");
                }
                else
                {
                    context.Response.StatusCode = 400;
                    await context.Response.WriteAsync("{\"error\": \"Stack is empty\"}");
                }
                break;
            }

        default:
            context.Response.StatusCode = 405;
            await context.Response.WriteAsync("{\"error\": \"Method not supported\"}");
            break;
    }
});

app.Run();