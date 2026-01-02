using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
using REST_API.Models;
using Results.Authenticate.Services.Abstractions;
using ResultsCollection.BSTU.Results.Collections.Abstractions;
using ResultsCollection.BSTU.Results.Models;

namespace REST_API.Controllers;

[Route("api/results")]
[ApiController]
public class ResultsController : ControllerBase
{
    private readonly IResultsRepository _resultsRepository;
    private readonly IAuthenticateService _authenticateService;

    public ResultsController(IResultsRepository resultsRepository, IAuthenticateService authenticateService)
    {
        _resultsRepository = resultsRepository;
        _authenticateService = authenticateService;
    }

    [HttpGet]
    [Authorize(Roles = "READER")]
    public async Task<ActionResult<IEnumerable<Result>>> GetAllAsync(
        CancellationToken cancellationToken    
    )
    {
        var results = await _resultsRepository.ReadAsync(cancellationToken);

        if (results is not null)
        {
            return results;
        }

        return StatusCode(500);
    }

    [HttpGet("{id:int}")]
    [Authorize(Roles = "READER")]
    public async Task<ActionResult<Result>> GetAllAsync(
        [FromRoute] int id,
        CancellationToken cancellationToken
    )
    {
        var results = await _resultsRepository.ReadAsync(cancellationToken);

        if (results is null)
        {
            return StatusCode(500);
        }

        var result = results?.FirstOrDefault(r => r.Id == id);

        if (result is not null)
        {
            return result;
        }

        return NotFound();
    }

    [HttpPost]
    [Authorize(Roles = "WRITER")]
    public async Task<ActionResult<Result>> CreateAsync(
        [FromBody] CreateResultModel model,
        CancellationToken cancellationToken
    )
    {
        var results = await _resultsRepository.ReadAsync(cancellationToken);

        if (results is null)
        {
            return StatusCode(500);
        }

        var max = results.Count != 0
            ? results.Max(r => r.Id) + 1
            : 1;

        var result = new Result(
            max,
            model.Value
        );

        results.Add(result);

        await _resultsRepository.WriteAsync(results, cancellationToken);

        return result;
    }

    [HttpPut("{id:int}")]
    [Authorize(Roles = "WRITER")]
    public async Task<ActionResult<Result>> UpdateAsync(
        [FromRoute] int id,
        [FromBody] CreateResultModel model,
        CancellationToken cancellationToken
    )
    {
        var results = await _resultsRepository.ReadAsync(cancellationToken);

        if (results is null)
        {
            return StatusCode(500);
        }

        var result = results.FirstOrDefault(r => r.Id == id);
        if (result is null)
        {
            return NotFound();
        }

        result.Value = model.Value;

        await _resultsRepository.WriteAsync(results, cancellationToken);

        return result;
    }

    [HttpDelete("{id:int}")]
    [Authorize(Roles = "WRITER")]
    public async Task<ActionResult<Result>> DeleteAsync(
        [FromRoute] int id,
        CancellationToken cancellationToken
    )
    {
        var results = await _resultsRepository.ReadAsync(cancellationToken);

        if (results is null)
        {
            return StatusCode(500);
        }

        var result = results.FirstOrDefault(r => r.Id == id);
        if (result is null)
        {
            return NotFound();
        }

        results.Remove(result);

        await _resultsRepository.WriteAsync(results, cancellationToken);

        return result;
    }

    [HttpPost("signIn")]
    [AllowAnonymous]
    public async Task<ActionResult<JwtTokenModel>> SignInAsync(
        [FromBody] SignInModel signInModel,
        CancellationToken cancellationToken
    )
    {
        var userExists = await _authenticateService.UserExistsAsync(signInModel.Login, cancellationToken);
        if (!userExists)
        {
            return NotFound("Пользователь не найден");
        }

        var token = await _authenticateService.SignIsAsync(signInModel.Login, signInModel.Password, cancellationToken);
        if (token is null)
        {
            return BadRequest("Неверный пароль");
        }

        return new JwtTokenModel(token);
    }
}
