using System.ComponentModel.DataAnnotations;

namespace ASPCMVC08.DTO.Admin
{
    public class ChangePasswordDto
    {
        public string Password { get; set; }

        [StringLength(64, MinimumLength = 6, ErrorMessage = "Пароль должен содержать от 6 до 64 символов")]
        public string NewPassword { get; set; }
    }
}