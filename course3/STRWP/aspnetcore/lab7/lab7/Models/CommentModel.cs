using System;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

public class CommentModel
{
    [Key]
    public int Id { get; set; }

    [Required]
    public string Text { get; set; }  // Текст комментария

    [Required]
    public DateTime CreatedAt { get; set; } = DateTime.Now;  // Дата создания

    public string SessionId { get; set; } // Добавили SessionId

    // Внешний ключ для связи с LinkModel
    [ForeignKey("Link")]
    public int LinkId { get; set; }
    public LinkModel Link { get; set; }  // Навигационное свойство
}
