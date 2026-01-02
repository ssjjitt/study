using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.AspNetCore.SignalR;
using Microsoft.AspNetCore.SignalR.Client;

namespace lab5_SignalR_Client
{
    internal class Program
    {
        static void Main(string[] args)
        {
            var connection = new HubConnectionBuilder()
                .WithUrl("http://localhost:5000/mathhub")
                .Build();

            await connection.StartAsync();

            double sum = await connection.InvokeAsync<double>("Sum", 2, 3);
            Console.WriteLine($"SUM(2,3) = {sum}");

            double sub = await connection.InvokeAsync<double>("Sub", 2, 3);
            Console.WriteLine($"SUB(2,3) = {sub}");

            double mul = await connection.InvokeAsync<double>("Mul", 2, 3);
            Console.WriteLine($"MUL(2,3) = {mul}");

            try
            {
                double div = await connection.InvokeAsync<double>("Div", 10, 0);
            }
            catch (HubException ex)
            {
                Console.WriteLine($"DIV(10,0) ERROR: {ex.Message}");
            }

            int fact = await connection.InvokeAsync<int>("Fact", 5);
            Console.WriteLine($"FACT(5) = {fact}");
        }
    }
}
