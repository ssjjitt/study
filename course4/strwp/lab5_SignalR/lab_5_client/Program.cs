using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.AspNetCore.SignalR.Client;

namespace lab_5_client
{
    internal class Program
    {
        static async Task Main(string[] args)
        {
            var url = "http://localhost:5215/calculatorHub";

            var connection = new HubConnectionBuilder()
                .WithUrl(url)
                .Build();

            try
            {
                Console.WriteLine($"Connecting to {url}...");
                await connection.StartAsync();
                Console.WriteLine("Connected.");

                double x = 10, y = 20;
                double sum = await connection.InvokeAsync<double>("SUM", x, y);
                Console.WriteLine($"SUM({x}, {y}) = {sum}");

                double sub = await connection.InvokeAsync<double>("SUB", x, y);
                Console.WriteLine($"SUB({x}, {y}) = {sub}");

                double mul = await connection.InvokeAsync<double>("MUL", x, y);
                Console.WriteLine($"MUL({x}, {y}) = {mul}");

                try
                {
                    double div = await connection.InvokeAsync<double>("DIV", x, y);
                    Console.WriteLine($"DIV({x}, {y}) = {div}");

                    Console.WriteLine("Testing Division by Zero...");
                    await connection.InvokeAsync<double>("DIV", x, 0);
                }
                catch (Exception ex)
                {
                    Console.WriteLine($"DIV Error (expected): {ex.Message}");
                }

                int n = 5;
                int fact = await connection.InvokeAsync<int>("FACT", n);
                Console.WriteLine($"FACT({n}) = {fact}");

            }
            catch (Exception ex)
            {
                Console.WriteLine($"Error: {ex.Message}");
            }
            finally
            {
                if (connection.State == HubConnectionState.Connected)
                {
                    await connection.StopAsync();
                }
            }

            Console.WriteLine("Press any key to exit...");
            Console.ReadKey();
        }
    }
}
