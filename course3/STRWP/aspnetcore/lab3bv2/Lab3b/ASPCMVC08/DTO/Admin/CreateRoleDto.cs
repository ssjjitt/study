using System.ComponentModel.DataAnnotations;

namespace ASPCMVC08.DTO.Admin
{
    public class CreateRoleDto
    {
        [StringLength(20, MinimumLength = 2, ErrorMessage = "Название роли должно содержать от 2 до 20 символов")]
        public string Name { get; set; }
    }
}
