using Microsoft.Extensions.DependencyInjection;

namespace JSONRPCServer.Infrastructure
{
    public static class ServiceLocator
    {
        public static IServiceProvider? Provider { get; set; }

        public static T Get<T>() => (T)Provider!.GetRequiredService(typeof(T));
    }
}
