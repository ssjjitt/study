using UnityEngine;

public class DragRotateLimited : MonoBehaviour
{
    [Header("Ось вращения (например, (1,0,0) для вращения по X)")]
    public Vector3 rotationAxis = Vector3.right;

    [Header("Ограничение угла в градусах")]
    public float minAngle = 0f;      // закрыто
    public float maxAngle = 90f;     // открыто

    [Header("Чувствительность")]
    public float sensitivity = 0.4f;

    private bool dragging = false;
    private float startMouseY;
    private float startAngle;

    private float currentAngle = 0f;

    private void Start()
    {
        // Устанавливаем начальный угол
        currentAngle = Mathf.Clamp(currentAngle, minAngle, maxAngle);
        ApplyRotation(currentAngle);
    }

    private void OnMouseDown()
    {
        dragging = true;
        startMouseY = Input.mousePosition.y;
        startAngle = currentAngle;
    }

    private void OnMouseUp()
    {
        dragging = false;
    }

    private void Update()
    {
        if (dragging)
        {
            float delta = (Input.mousePosition.y - startMouseY) * sensitivity;

            currentAngle = Mathf.Clamp(startAngle + delta, minAngle, maxAngle);

            ApplyRotation(currentAngle);
        }
    }

    private void ApplyRotation(float angle)
    {
        transform.localRotation =
            Quaternion.AngleAxis(angle, rotationAxis.normalized);
    }
}
