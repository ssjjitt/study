using System;
using Grpc.Net.Client;
using Grpc.Net.Client.Web;
using Grpc.Core;
using System.Net.Http;
using GrpcServer;

namespace lab6_client
{
    class Program
    {
        private const string ServerAddress = "https://localhost:7158";

        static void Main(string[] args)
        {
            var channel = CreateGrpcChannel();
            var client = new Calculator.CalculatorClient(channel);

            TestSum(client, 5.2, 5.2);
            TestSub(client, 10.0, 5.2);
            TestMul(client, 7.0, 2.5);
            TestDiv(client, 15.0, 3.0);
            TestDiv(client, 10.0, 0.0);

            TestFact(client, 5);
            TestFact(client, 10);
            TestFact(client, 20); 
            TestFact(client, -5); 

            Console.ReadLine();
        }

        private static GrpcChannel CreateGrpcChannel()
        {
            var httpHandler = new HttpClientHandler();
            var grpcWebHandler = new GrpcWebHandler(GrpcWebMode.GrpcWeb, httpHandler);

            return GrpcChannel.ForAddress(ServerAddress, new GrpcChannelOptions
            {
                HttpHandler = grpcWebHandler
            });
        }

        private static void TestSum(Calculator.CalculatorClient client, double x, double y)
        {
            ExecuteDoubleOperation(
                () => client.SUM(new TwoDoubleRequest { X = x, Y = y }),
                $"SUM({x}, {y})"
            );
        }

        private static void TestSub(Calculator.CalculatorClient client, double x, double y)
        {
            ExecuteDoubleOperation(
                () => client.SUB(new TwoDoubleRequest { X = x, Y = y }),
                $"SUB({x}, {y})"
            );
        }

        private static void TestMul(Calculator.CalculatorClient client, double x, double y)
        {
            ExecuteDoubleOperation(
                () => client.MUL(new TwoDoubleRequest { X = x, Y = y }),
                $"MUL({x}, {y})"
            );
        }

        private static void TestDiv(Calculator.CalculatorClient client, double x, double y)
        {
            ExecuteDoubleOperation(
                () => client.DIV(new TwoDoubleRequest { X = x, Y = y }),
                $"DIV({x}, {y})"
            );
        }

        private static void TestFact(Calculator.CalculatorClient client, int x)
        {
            ExecuteIntOperation(
                () => client.FACT(new IntRequest { X = x }),
                $"FACT({x})"
            );
        }

        private static void ExecuteDoubleOperation(
            Func<DoubleResponse> operation,
            string operationName)
        {
            try
            {
                var response = operation();
                Console.WriteLine($"{operationName} = {response.Result}");
            }
            catch (RpcException ex)
            {
                Console.WriteLine($"{operationName}: {ex.Status.Detail}");
            }
            catch (Exception ex)
            {
                Console.WriteLine($"{operationName}: {ex.Message}");
            }
        }

        private static void ExecuteIntOperation(
            Func<IntResponse> operation,
            string operationName)
        {
            try
            {
                var response = operation();
                Console.WriteLine($"{operationName} = {response.Result}");
            }
            catch (RpcException ex)
            {
                Console.WriteLine($"{operationName}: {ex.Status.Detail}");
            }
            catch (Exception ex)
            {
                Console.WriteLine($"{operationName}: {ex.Message}");
            }
        }
    }
}
