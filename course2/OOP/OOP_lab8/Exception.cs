using System;
public class InvalidNumberInputException : Exception
{
    public InvalidNumberInputException()
    {
    }

    public InvalidNumberInputException(string message)
        : base(message)
    {
    }

    public InvalidNumberInputException(string message, Exception innerException)
        : base(message, innerException)
    {
    }
}
