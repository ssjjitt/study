using UnityEngine;
using TMPro;

public class CyclicTextController : MonoBehaviour
{
    [Header("TextMeshPro компонент")]
    public TMP_Text screenText;
    public float fontSize;

    [Header("Тексты для прокрутки")]
    public string[] texts;

    private int currentIndex = 0;

    void Start()
    {
        if (texts.Length > 0 && screenText != null)
            screenText.text = texts[currentIndex];
        screenText.fontSize = 0.2f;
    }

    // Нажатие кнопки вверх
    public void NextText()
    {
        if (texts.Length == 0) return;

        currentIndex = (currentIndex + 1) % texts.Length; // циклический сдвиг
        screenText.text = texts[currentIndex];
    }

    // Нажатие кнопки вниз
    public void PreviousText()
    {
        if (texts.Length == 0) return;

        currentIndex--;
        if (currentIndex < 0)
            currentIndex = texts.Length - 1; // циклический сдвиг назад

        screenText.text = texts[currentIndex];
    }
}
