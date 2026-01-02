using Microsoft.AspNetCore.Identity;
using Microsoft.Extensions.Configuration;
using Microsoft.IdentityModel.Tokens;
using Results.Authenticate.Services.Abstractions;
using System.IdentityModel.Tokens.Jwt;
using System.Security.Claims;
using System.Text;

namespace Results.Authenticate.Services;

public sealed class AuthenticateService : IAuthenticateService
{
    private readonly UserManager<IdentityUser> _userManager;
    private readonly IConfiguration _config;

    public AuthenticateService(UserManager<IdentityUser> userManager, IConfiguration configuration)
    {
        _userManager = userManager;
        _config = configuration;
    }

    public async Task<bool> UserExistsAsync(string login, CancellationToken cancellationToken = default)
    {
        var user = await _userManager.FindByNameAsync(login);

        return user is not null;
    }

    public async Task<string?> SignIsAsync(string login, string password, CancellationToken cancellationToken = default)
    {
        var user = await _userManager.FindByNameAsync(login);
        if (user is null)
        {
            return null;
        }

        var isPasswordValid = await _userManager.CheckPasswordAsync(user, password);

        if (!isPasswordValid)
        {
            return null;
        }

        var claims = new List<Claim>
        {
            new Claim(ClaimTypes.Name, login), // утверждение логина
            new Claim(JwtRegisteredClaimNames.Jti, Guid.NewGuid().ToString())
        };

        var roles = await _userManager.GetRolesAsync(user);
        claims.AddRange(roles.Select(role => new Claim(ClaimTypes.Role, role)));

        var key = new SymmetricSecurityKey(Encoding.UTF8.GetBytes(_config["Jwt:Key"] ?? 
            throw new ArgumentNullException("JWT Key is not defined in configuration")));

        var creds = new SigningCredentials(key, SecurityAlgorithms.HmacSha256); // подпись

        var token = new JwtSecurityToken(
            issuer: _config["Jwt:Issuer"],
            audience: _config["Jwt:Audience"],
            claims: claims,
            expires: DateTime.UtcNow.AddHours(1),
            signingCredentials: creds);

        return new JwtSecurityTokenHandler().WriteToken(token);
    }
}
