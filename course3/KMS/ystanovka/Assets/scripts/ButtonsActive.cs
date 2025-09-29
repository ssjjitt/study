using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ButtonsActive : MonoBehaviour
{
    public Button button1; // ������ ������
    public Button button2; // ������ ������
    public Button button3; // ������ ������
    public Button button4; // ��������� ������
    public Button button5; // ����� ������

    void Start()
    {
        // ������������ ��� ������, ����� ������
        button2.interactable = false;
        button3.interactable = false;
        button4.interactable = false;
        button5.interactable = false;

    }

    public void ActivateButton(Button button)
    {
        button.interactable = true;
    }

    public void DeactivateAllButtons()
    {
        button2.interactable = false;
        button3.interactable = false;
        button4.interactable = false;
        button5.interactable = false;
    }
}