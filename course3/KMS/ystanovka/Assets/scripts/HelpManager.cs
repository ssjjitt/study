using UnityEngine;
using UnityEngine.UI;

public class HelpManager : MonoBehaviour
{
    public GameObject helpWindow;
    public FirstPersonLook firstPersonLook;

    public void Start()
    {
        helpWindow.SetActive(false);
    }

    public void Update()
    {
        if (Input.GetKeyDown(KeyCode.Tab))
        {
            ToggleCursor(); // Показываем или скрываем курсор
        }
    }

    public void ToggleCursor()
    {
        if (Cursor.visible)
        {
            Cursor.lockState = CursorLockMode.Locked;
            Cursor.visible = false;
            firstPersonLook.SetCursorVisibility(false); // Блокируем движение камеры
        }
        else
        {
            Cursor.lockState = CursorLockMode.None;
            Cursor.visible = true;
            firstPersonLook.SetCursorVisibility(true); // Разрешаем движение камеры
        }
    }

    public void ShowHelp()
    {
        helpWindow.SetActive(true);
    }

    public void HideHelp()
    {
        helpWindow.SetActive(false);
    }
}