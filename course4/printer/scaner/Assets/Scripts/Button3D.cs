using UnityEngine;

public class Button3D : MonoBehaviour
{
    [Header("Контроллер текста")]
    public CyclicTextController textController;

    [Header("Тип кнопки")]
    public bool isNextButton = true; // true = вверх, false = вниз

    private void OnMouseDown()
    {
        if (textController == null) return;

        if (isNextButton)
            textController.NextText();
        else
            textController.PreviousText();
    }
}
