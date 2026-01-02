using System.Collections.Concurrent;
using System.Text.Json;
using System.Threading.Channels;

namespace JSONRPCServer.Services
{
    public class SseService
    {
        private readonly ConcurrentDictionary<Guid, Channel<string>> _clients = new();

        public SseService()
        {
        }

        public (Guid id, ChannelReader<string> reader) Subscribe()
        {
            var id = Guid.NewGuid();
            var channel = Channel.CreateUnbounded<string>(new UnboundedChannelOptions
            {
                SingleReader = true,
                SingleWriter = false
            });
            _clients[id] = channel;
            return (id, channel.Reader);
        }

        public void Unsubscribe(Guid id)
        {
            if (_clients.TryRemove(id, out var channel))
            {
                channel.Writer.TryComplete(); // закрытие канала
            }
        }
        public async Task BroadcastAsync(string eventName, object data)
        {
            var payload = JsonSerializer.Serialize(data);
            var sseMessage = $"event: {eventName}\n" + $"data: {payload}\n\n";

            var tasks = new List<Task>();
            foreach (var kv in _clients)
            {
                var writer = kv.Value.Writer;
                try
                {
                    writer.TryWrite(sseMessage);
                }
                catch
                {
                }
            }
            await Task.CompletedTask;
        }
    }
}
