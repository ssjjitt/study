using Microsoft.AspNetCore.SignalR;

namespace lab5_SignalR.Hubs;

public class CalculatorHub : Hub
{
    public Task<double> SUM(double x, double y) =>
        Task.FromResult(x + y);

    public Task<double> SUB(double x, double y) =>
        Task.FromResult(x - y);

    public Task<double> MUL(double x, double y) =>
        Task.FromResult(x * y);

    public Task<double> DIV(double x, double y)
    {
        if (y == 0)
            throw new HubException("Division by zero is not allowed.");

        return Task.FromResult(x / y);
    }

    public Task<int> FACT(int x)
    {
        if (x < 0)
            throw new HubException("Factorial is not defined for negative numbers.");

        try
        {
            checked
            {
                int result = 1;
                for (int i = 2; i <= x; i++)
                    result *= i;

                return Task.FromResult(result);
            }
        }
        catch (OverflowException)
        {
            throw new HubException("Factorial result exceeds int range.");
        }
    }
}
