namespace REST_API.Models;

public sealed record SignInModel(
    string Login,
    string Password
);