using UnityEngine;

public class CameraZoomToObj : MonoBehaviour
{
    [Header("Настройки")]
    [Tooltip("На каком расстоянии от куба камера должна остановиться")]
    public float stopDistance = 3f;

    [Tooltip("Скорость полета камеры")]
    public float speed = 5f;

    private Camera mainCam;
    private Vector3 originalPos;
    private Quaternion originalRot;
    private bool isZoomed = false;

    void Start()
    {
        // Находим главную камеру автоматически
        mainCam = Camera.main;

        // Запоминаем, где она стояла в начале игры
        originalPos = mainCam.transform.position;
        originalRot = mainCam.transform.rotation;
    }

    // Эту функцию вызывай из EventTrigger или кнопки
    public void ToggleZoom()
    {
        isZoomed = !isZoomed;
    }

    // А это сработает, если просто кликнуть мышкой по самому кубу (если на нем есть коллайдер)
    private void OnMouseDown()
    {
        ToggleZoom();
    }

    void Update()
    {
        Vector3 targetPosition;
        Quaternion targetRotation;

        if (isZoomed)
        {
            // МАГИЯ МАТЕМАТИКИ:
            // 1. Берем позицию куба (transform.position)
            // 2. Строим вектор в сторону, где была камера изначально
            // 3. Отступаем по этому вектору на stopDistance
            Vector3 directionToCamera = (originalPos - transform.position).normalized;
            targetPosition = transform.position + (directionToCamera * stopDistance);

            // Поворачиваем камеру, чтобы она смотрела точно на куб
            targetRotation = Quaternion.LookRotation(transform.position - targetPosition);
        }
        else
        {
            // Возвращаемся домой
            targetPosition = originalPos;
            targetRotation = originalRot;
        }

        // Плавное движение (Lerp)
        // Time.deltaTime делает движение независимым от FPS
        mainCam.transform.position = Vector3.Lerp(mainCam.transform.position, targetPosition, Time.deltaTime * speed);
        mainCam.transform.rotation = Quaternion.Slerp(mainCam.transform.rotation, targetRotation, Time.deltaTime * speed);
    }
}