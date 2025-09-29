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
        // ���������, ������ �� ������� Tab
        if (Input.GetKeyDown(KeyCode.Tab))
        {
            ToggleCursor(); // ���������� ��� �������� ������
        }
    }

    public void ToggleCursor()
    {
        if (Cursor.visible)
        {
            Cursor.lockState = CursorLockMode.Locked; // ��������� ������
            Cursor.visible = false; // �������� ������
        }
        else
        {
            Cursor.lockState = CursorLockMode.None; // ������������ ������
            Cursor.visible = true; // ���������� ������
        }
    }

    public void ToggleHelpWindow()
    {
        // ����������� ��������� ���� �������
        helpWindow.SetActive(!helpWindow.activeSelf);
    }
}