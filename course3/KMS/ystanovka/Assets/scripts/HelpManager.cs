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
            ToggleCursor(); // ���������� ��� �������� ������
        }
    }

    public void ToggleCursor()
    {
        if (Cursor.visible)
        {
            Cursor.lockState = CursorLockMode.Locked;
            Cursor.visible = false;
            firstPersonLook.SetCursorVisibility(false); // ��������� �������� ������
        }
        else
        {
            Cursor.lockState = CursorLockMode.None;
            Cursor.visible = true;
            firstPersonLook.SetCursorVisibility(true); // ��������� �������� ������
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