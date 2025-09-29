using UnityEngine;

public class FirstPersonLook : MonoBehaviour
{
    [SerializeField]
    Transform character;
    public float sensitivity = 1;
    public float smoothing = 1.5f;

    Vector2 velocity;
    Vector2 frameVelocity;

    private bool isCursorVisible; // Переменная для отслеживания видимости курсора

    void Reset()
    {
        character = GetComponentInParent<FirstPersonMovement>().transform;
    }

    void Start()
    {
        Cursor.lockState = CursorLockMode.Locked;
        isCursorVisible = false; // Изначально курсор скрыт
    }

    void Update()
    {
        // Проверяем, виден ли курсор
        if (isCursorVisible)
            return; // Если курсор виден, пропускаем управление камерой

        // Получаем плавное значение для движения мыши
        Vector2 mouseDelta = new Vector2(Input.GetAxisRaw("Mouse X"), Input.GetAxisRaw("Mouse Y"));
        Vector2 rawFrameVelocity = Vector2.Scale(mouseDelta, Vector2.one * sensitivity);
        frameVelocity = Vector2.Lerp(frameVelocity, rawFrameVelocity, 1 / smoothing);
        velocity += frameVelocity;
        velocity.y = Mathf.Clamp(velocity.y, -90, 90);

        // Вращаем камеру и персонажа
        transform.localRotation = Quaternion.AngleAxis(-velocity.y, Vector3.right);
        character.localRotation = Quaternion.AngleAxis(velocity.x, Vector3.up);
    }

    public void SetCursorVisibility(bool visible)
    {
        isCursorVisible = visible; // Устанавливаем состояние видимости курсора
    }
}