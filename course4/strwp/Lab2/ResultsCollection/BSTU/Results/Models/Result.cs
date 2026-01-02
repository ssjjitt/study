namespace ResultsCollection.BSTU.Results.Models;

public sealed class Result
{
    public int Id { get; set; }
    public string Value { get; set; }

    private Result()
    {
        Value = null!;
    }

    public Result(int id, string value)
    {
        Id = id;
        Value = value;
    }
}