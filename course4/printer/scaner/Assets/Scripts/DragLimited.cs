using UnityEngine;

public class DragLimited : MonoBehaviour
{
    [Header("Ось движения (например, Vector3.forward)")]
    public Vector3 moveAxis = Vector3.back;

    [Header("Ограничения по расстоянию (в метрах)")]
    public float minDistance = 0f;   // закрыто
    public float maxDistance = 0.15f; // полностью открыт

    private float currentDistance = 0f;
    private bool dragging = false;
    private float startMousePos;
    private float startDistance;

    private void OnMouseDown()
    {
        dragging = true;

        // фиксируем позицию мыши и текущее расстояние
        startMousePos = Input.mousePosition.y;
        startDistance = currentDistance;
    }

    private void OnMouseUp()
    {
        dragging = false;
    }

    private void Update()
    {
        if (dragging)
        {
            float delta = (Input.mousePosition.y - startMousePos) * 0.001f;
            currentDistance = Mathf.Clamp(startDistance + delta, minDistance, maxDistance);

            transform.localPosition = moveAxis.normalized * currentDistance;
        }
    }
}
