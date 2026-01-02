namespace Results.Authenticate.Services.Abstractions;

public interface IAuthenticateService
{
    Task<bool> UserExistsAsync(string login, CancellationToken cancellationToken = default);
    Task<string?> SignIsAsync(string login, string password, CancellationToken cancellationToken = default);
}
