using Grpc.Core;
using GrpcServer;
using lab6_gRPC;
using System.Numerics;

namespace lab6_gRPC.Services
{
    public class CalculatorService : Calculator.CalculatorBase
    {
        public override Task<DoubleResponse> SUM(TwoDoubleRequest request, ServerCallContext context)
        {
            return Task.FromResult(new DoubleResponse
            {
                Result = request.X + request.Y
            });
        }

        public override Task<DoubleResponse> SUB(TwoDoubleRequest request, ServerCallContext context)
        {
            return Task.FromResult(new DoubleResponse
            {
                Result = request.X - request.Y
            });
        }

        public override Task<DoubleResponse> MUL(TwoDoubleRequest request, ServerCallContext context)
        {
            return Task.FromResult(new DoubleResponse
            {
                Result = request.X * request.Y
            });
        }

        public override Task<DoubleResponse> DIV(TwoDoubleRequest request, ServerCallContext context)
        {
            if (request.Y == 0)
            {
                throw new RpcException(
                    new Status(StatusCode.InvalidArgument, "деление на ноль"));
            }

            return Task.FromResult(new DoubleResponse
            {
                Result = request.X / request.Y
            });
        }

        public override Task<IntResponse> FACT(IntRequest request, ServerCallContext context)
        {
            if (request.X < 0)
            {
                throw new RpcException(
                    new Status(StatusCode.InvalidArgument, "отриц число"));
            }

            BigInteger fact = 1;
            for (int i = 1; i <= request.X; i++)
                fact *= i;

            if (fact > int.MaxValue)
            {
                throw new RpcException(
                    new Status(StatusCode.OutOfRange, "превышена размерность int"));
            }

            return Task.FromResult(new IntResponse
            {
                Result = (int)fact
            });
        }
    }
}
