using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using System.Linq;

public class HomeController : Controller
{
    private const string AccessKey = "12345";
    private const string SessionKey = "Mode";

    private readonly AppDbContext _dbContext;

    public HomeController(AppDbContext dbContext)
    {
        _dbContext = dbContext;
    }

    // Главная страница с фильтрацией и ссылками
    public IActionResult Index(string filterKeyword)
    {
        if (User.IsInRole("Owner"))
        {
            ViewBag.Mode = "owner";
        }
        else
        {
            ViewBag.Mode = "guest";
        }
        var mode = HttpContext.Session.GetString(SessionKey) ?? "guest";  // Определение режима пользователя. меняет в пределах сессии
        ViewBag.Mode = mode;

        // Получаем ссылки с возможностью фильтрации
        var links = string.IsNullOrEmpty(filterKeyword)
            ? _dbContext.Links.Include(l => l.Comments).ToList()
            : _dbContext.Links.Include(l => l.Comments).Where(l => l.Keywords.Contains(filterKeyword)).ToList();

        ViewBag.Links = links;
        ViewBag.FilterKeyword = filterKeyword;  // Передаем текущее значение фильтра в представление
        return View();
    }

    // Переключение режима (гость / владелец)
    [HttpPost]
    public IActionResult SwitchMode(string accessKey)
    {
        if (accessKey == AccessKey)
        {
            HttpContext.Session.SetString(SessionKey, "owner");
        }
        else
        {
            HttpContext.Session.SetString(SessionKey, "guest");
        }

        return RedirectToAction("Index");
    }

    // Добавление новой ссылки (только для владельца)
    [HttpPost]
    public IActionResult AddLink(string url, string keywords)
    {
        if (HttpContext.Session.GetString(SessionKey) == "owner")
        {
            var link = new LinkModel { Url = url, Keywords = keywords };
            _dbContext.Links.Add(link);
            _dbContext.SaveChanges();
        }

        return RedirectToAction("Index");
    }

    // Удаление ссылки (только для владельца)
    [HttpPost]
    public IActionResult DeleteLink(int id)
    {
        if (HttpContext.Session.GetString(SessionKey) == "owner")
        {
            var link = _dbContext.Links.Find(id);
            if (link != null)
            {
                _dbContext.Links.Remove(link);
                _dbContext.SaveChanges();
            }
        }

        return RedirectToAction("Index");
    }

    // Редактирование ссылки (только для владельца)
    [HttpPost]
    public IActionResult EditLink(int id, string url, string keywords)
    {
        if (HttpContext.Session.GetString(SessionKey) == "owner" && !string.IsNullOrEmpty(url) && !string.IsNullOrEmpty(keywords))
        {
            var link = _dbContext.Links.FirstOrDefault(l => l.Id == id);
            if (link != null)
            {
                link.Url = url;
                link.Keywords = keywords;
                _dbContext.SaveChanges();
            }
        }
        return RedirectToAction("Index");
    }

    // Добавление комментария (доступно для всех, но только владельцам — редактировать и удалять)
    [HttpPost]
    public IActionResult AddComment(int linkId, string commentText)
    {
        if (string.IsNullOrEmpty(commentText))
        {
            // Возвращаем ошибку или сообщение о том, что комментарий не может быть пустым
            return RedirectToAction("Index");
        }

        // Проверяем, существует ли ссылка с данным LinkId
        var link = _dbContext.Links.FirstOrDefault(l => l.Id == linkId);
        if (link == null)
        {
            // Если ссылка не найдена, возвращаем ошибку или редирект
            return RedirectToAction("Index");
        }

        var newComment = new CommentModel
        {
            Text = commentText,
            CreatedAt = DateTime.Now,
            SessionId = HttpContext.Session.GetString(SessionKey), // Сохраняем SessionId
            LinkId = linkId // Присваиваем существующий LinkId
        };

        _dbContext.Comments.Add(newComment);
        _dbContext.SaveChanges();

        return RedirectToAction("Index");
    }


    // Редактирование комментария (только для владельца)
    [HttpPost]
    public IActionResult EditComment(int commentId, string newText)
    {
        if (!string.IsNullOrEmpty(newText))
        {
            var comment = _dbContext.Comments.FirstOrDefault(c => c.Id == commentId);
            if (comment != null)
            {
                // Проверка для владельца: владелец может редактировать любые комментарии
                if (HttpContext.Session.GetString(SessionKey) == "owner")
                {
                    comment.Text = newText;
                    _dbContext.SaveChanges();
                }
                // Проверка для гостя: гость может редактировать только свои комментарии
                else
                {
                    var userSessionId = HttpContext.Session.GetString(SessionKey);
                    if (comment.SessionId == userSessionId)
                    {
                        comment.Text = newText;
                        _dbContext.SaveChanges();
                    }
                }
            }
        }
        return RedirectToAction("Index");
    }


    // Удаление комментария (только для владельца)
    [HttpPost]
    public IActionResult DeleteComment(int commentId)
    {
        var comment = _dbContext.Comments.FirstOrDefault(c => c.Id == commentId);

        if (comment != null)
        {
            // Проверка, что удаляет тот же самый пользователь (по SessionId)
            var currentSessionId = HttpContext.Session.GetString(SessionKey);

            // Если это гость или владельца, проверяем SessionId
            if (comment.SessionId == currentSessionId || HttpContext.Session.GetString(SessionKey) == "owner")
            {
                _dbContext.Comments.Remove(comment);
                _dbContext.SaveChanges();
            }
            else
            {
                // Можно вернуть сообщение или просто игнорировать
        
                TempData["ErrorMessage"] = "Вы не можете удалить комментарий другого пользователя.";
            }
        }

        return RedirectToAction("Index");
    }


    // Голосование за полезность ссылки (только для владельца)
    [HttpPost]
    public IActionResult Vote(int id, bool isUseful)
    {
        if (HttpContext.Session.GetString(SessionKey) == "owner")
        {
            var link = _dbContext.Links.Find(id);
            if (link != null)
            {
                if (isUseful)
                {
                    link.UsefulCount++;
                }
                else
                {
                    link.UselessCount++;
                }
                _dbContext.SaveChanges();
            }
        }
        return RedirectToAction("Index");
    }
}
