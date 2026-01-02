using System.Collections;
using TMPro;
using UnityEngine;

public class textAndCamScript : MonoBehaviour
{
    public TextMeshProUGUI textMeshPro; // Ссылка на компонент TextMeshPro
    public Camera camera; // Ссылка на камеру
    public float distance = -1f; // Расстояние от камеры до объекта
    public float heightOffset = 1.3f; // Смещение по высоте
    public float lateralOffset = -0.4f; // Смещение влево-вправо
    public float speed = 0.3f; // Скорость перемещения камеры

    private Vector3 originalPosition; // Исходная позиция камеры
    private Quaternion originalRotation; // Исходная ориентация камеры
    private bool isAtTarget = false; // Текущее состояние камеры

    void Start()
    {
        // Сохраняем исходные позицию и ориентацию камеры
        originalPosition = camera.transform.position;
        originalRotation = camera.transform.rotation;
    }

    public void ShowMessageAndMoveCamera(Transform target, string message)
    {
        if (isAtTarget)
        {
            // Возвращаем камеру в исходное положение
            StartCoroutine(MoveCamera(originalPosition, originalRotation));
            textMeshPro.text = ""; // Очищаем текст
        }
        else
        {
            // Рассчитываем позицию для камеры с учетом высоты и смещения
            Vector3 targetPosition = target.position - target.forward * distance;
            targetPosition.y += heightOffset; // Поднимаем камеру выше
            targetPosition.x += lateralOffset; // Смещение вправо
            StartCoroutine(MoveCamera(targetPosition, Quaternion.LookRotation(target.position - targetPosition)));
            textMeshPro.text = message; // Устанавливаем текст
        }
        isAtTarget = !isAtTarget; // Переключаем состояние
    }

    private IEnumerator MoveCamera(Vector3 targetPos, Quaternion targetRot)
    {
        float elapsedTime = 0f;
        Vector3 startingPos = camera.transform.position;
        Quaternion startingRot = camera.transform.rotation;

        while (elapsedTime < speed)
        {
            camera.transform.position = Vector3.Lerp(startingPos, targetPos, (elapsedTime / speed));
            //camera.transform.rotation = Quaternion.Slerp(startingRot, targetRot, (elapsedTime / speed));
            elapsedTime += Time.deltaTime;
            yield return null; // Ждем следующего кадра
        }

        // Убедимся, что камера точно нацелена
        camera.transform.position = targetPos;
        //camera.transform.rotation = targetRot;
    }
}