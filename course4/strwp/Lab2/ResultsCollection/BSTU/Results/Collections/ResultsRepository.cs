using ResultsCollection.BSTU.Results.Collections.Abstractions;
using ResultsCollection.BSTU.Results.Models;
using System.Text.Json;

namespace ResultsCollection.BSTU.Results.Collections;

public sealed class ResultsRepository : IResultsRepository
{
    private const string FILENAME = "data.json";

    private static readonly SemaphoreSlim _locker = new(1, 1);

    public ResultsRepository()
    {
        if (!File.Exists(FILENAME))
        {
            File.Create(FILENAME);

            File.WriteAllText(FILENAME, "[]");
        }
    }

    public async Task<List<Result>> ReadAsync(CancellationToken cancellationToken = default)
    {
        await _locker.WaitAsync(cancellationToken);

        var data = await File.ReadAllTextAsync(FILENAME, cancellationToken);

        var results = JsonSerializer.Deserialize<List<Result>>(data)!;

        _locker.Release();

        return results;
    }

    public async Task WriteAsync(List<Result> results, CancellationToken cancellationToken = default)
    {
        await _locker.WaitAsync(cancellationToken);

        var json = JsonSerializer.Serialize(results);

        _locker.Release();

        await File.WriteAllTextAsync(FILENAME, json, cancellationToken);
    }
}
