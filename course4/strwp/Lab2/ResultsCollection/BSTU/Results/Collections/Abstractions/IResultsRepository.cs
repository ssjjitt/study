using ResultsCollection.BSTU.Results.Models;

namespace ResultsCollection.BSTU.Results.Collections.Abstractions;

public interface IResultsRepository
{
    Task<List<Result>> ReadAsync(CancellationToken cancellationToken = default);
    Task WriteAsync(List<Result> results, CancellationToken cancellationToken = default);
}
