using System.ComponentModel.DataAnnotations;

namespace ASPCMVC08.DTO.Admin
{
    public class RegisterDto
    {
        [StringLength(20, MinimumLength = 2, ErrorMessage = "Имя пользователя должно содержать от 2 до 20 символов")]
        public string Username { get; set; }

        [StringLength(64, MinimumLength = 6, ErrorMessage = "Пароль должен содержать от 6 до 64 символов")]
        public string Password { get; set; }

        public override string ToString() => $"Username: {Username} | Password: {Password}";
    }
}
