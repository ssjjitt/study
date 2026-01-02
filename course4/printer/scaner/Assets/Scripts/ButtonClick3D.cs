using UnityEngine;
using System.Collections;

public class ButtonClick3D : MonoBehaviour
{
    [Header("Настройки движения")]
    public float pressDepth = 0.02f;    // на сколько продавливается кнопка
    public float pressDuration = 0.1f;  // время нажатия и возврата

    [Header("Что включать при нажатии")]
    public GameObject targetObject;
    public bool toggle = true;          // включать/выключать

    private Vector3 startPos;
    private bool isOn = false;
    private bool isAnimating = false;

    void Start()
    {
        startPos = transform.localPosition;
    }

    void OnMouseDown()
    {
        if (!isAnimating)
            StartCoroutine(PressButton());
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
        if (targetObject != null)
        {
            if (toggle)
            {
                isOn = !isOn;
                targetObject.SetActive(isOn);
            }
            else
            {
                targetObject.SetActive(true);
            }
        }

        // Возвращаем кнопку назад
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
