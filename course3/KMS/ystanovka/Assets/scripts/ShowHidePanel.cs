using UnityEngine;
using UnityEngine.UI;

public class ShowHidePanel : MonoBehaviour
{
    public GameObject helpWindow;

    public void Start()
    {
        helpWindow.SetActive(false);
    }

    public void Update()
    {
        // Проверяем, нажата ли клавиша Tab
        if (Input.GetKeyDown(KeyCode.Tab))
        {
            ToggleCursor(); // Показываем или скрываем курсор
        }
    }

    public void ToggleCursor()
    {
        if (Cursor.visible)
        {
            Cursor.lockState = CursorLockMode.Locked; // Блокируем курсор
            Cursor.visible = false; // Скрываем курсор
        }
        else
        {
            Cursor.lockState = CursorLockMode.None; // Разблокируем курсор
            Cursor.visible = true; // Показываем курсор
        }
    }

    public void ToggleHelpWindow()
    {
        // Переключаем состояние окна справки
        helpWindow.SetActive(!helpWindow.activeSelf);
    }
}