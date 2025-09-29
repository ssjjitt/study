using Microsoft.AspNetCore.Identity.EntityFrameworkCore;
using Microsoft.AspNetCore.Identity;
using Microsoft.EntityFrameworkCore;

public class AppDbContext : IdentityDbContext<IdentityUser>
{
    public DbSet<LinkModel> Links { get; set; }
    public DbSet<CommentModel> Comments { get; set; } 

    protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
    {
        // Укажите строку подключения к базе данных
        optionsBuilder.UseSqlServer("Server=DESKTOP-9FDAEQH;Database=LinksDb;Trusted_Connection=True;");
        
    }

    protected override void OnModelCreating(ModelBuilder modelBuilder)
    {
        base.OnModelCreating(modelBuilder);
        // Настройка связи между ссылками и комментариями
        modelBuilder.Entity<CommentModel>()
            .HasOne(c => c.Link)
            .WithMany(l => l.Comments)
            .HasForeignKey(c => c.LinkId)
            .OnDelete(DeleteBehavior.Cascade); // При удалении ссылки удаляются связанные комментарии
    }
}
