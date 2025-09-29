using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ButtonsActive : MonoBehaviour
{
    public Button button1; // Первая кнопка
    public Button button2; // Вторая кнопка
    public Button button3; // Третья кнопка
    public Button button4; // Четвертая кнопка
    public Button button5; // Пятая кнопка

    void Start()
    {
        // Деактивируем все кнопки, кроме первой
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