using UnityEngine;
using System.Collections;

public class StartAndTextController : MonoBehaviour
{
    [Header("Настройки движения")]
    public float pressDepth = 0.01f;      // насколько кнопка вдавливается
    public float pressDuration = 0.1f;    // время нажатия и возврата

    [Header("Действие при нажатии")]
    public CyclicTextController textController; // контроллер текста
    public bool isNextButton = true;             // вверх или вниз для текста

    public MoveAndRotateToTarget mover;

    private Vector3 startPos;
    private bool isAnimating = false;

    void Start()
    {
        startPos = transform.localPosition;
    }

    private void OnMouseDown()
    {
        if (!isAnimating)
        {
            StartCoroutine(PressButton());
        }
        mover.MoveToTarget();
    }

    private IEnumerator PressButton()
    {
        isAnimating = true;

        Vector3 pressedPos = startPos - new Vector3(0, pressDepth, 0);

        // Опускаем кнопку
        float t = 0f;
        while (t < pressDuration)
        {
            t += Time.deltaTime;
            float progress = t / pressDuration;
            transform.localPosition = Vector3.Lerp(startPos, pressedPos, progress);
            yield return null;
        }
        transform.localPosition = pressedPos;

        // Выполняем действие
        if (textController != null)
        {
            if (isNextButton)
                textController.NextText();
            else
                textController.PreviousText();
        }

        // Возвращаем кнопку обратно
        t = 0f;
        while (t < pressDuration)
        {
            t += Time.deltaTime;
            float progress = t / pressDuration;
            transform.localPosition = Vector3.Lerp(pressedPos, startPos, progress);
            yield return null;
        }
        transform.localPosition = startPos;

        isAnimating = false;
    }
}
