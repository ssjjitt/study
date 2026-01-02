using System.Collections.Generic;
using UnityEngine;

public class FirstPersonMovement : MonoBehaviour
{
    public float speed = 5;

    [Header("Running")]
    public bool canRun = true;
    public bool IsRunning { get; private set; }
    public float runSpeed = 9;
    public KeyCode runningKey = KeyCode.LeftShift;

    Rigidbody rigidbody;
    public List<System.Func<float>> speedOverrides = new List<System.Func<float>>();

    void Awake()
    {
        // Получаем Rigidbody на этом объекте.
        rigidbody = GetComponent<Rigidbody>();
    }

    void FixedUpdate()
    {
        // Обновляем состояние бега на основе ввода.
        IsRunning = canRun && Input.GetKey(runningKey);

        // Определяем целевую скорость движения.
        float targetMovingSpeed = IsRunning ? runSpeed : speed;
        if (speedOverrides.Count > 0)
        {
            targetMovingSpeed = speedOverrides[speedOverrides.Count - 1]();
        }

        // Определяем целевую скорость на основе ввода с клавиш WASD.
        Vector2 targetVelocity = new Vector2(0, 0);

        if (Input.GetKey(KeyCode.A)) // Влево
        {
            targetVelocity.x = -targetMovingSpeed;
        }
        if (Input.GetKey(KeyCode.D)) // Вправо
        {
            targetVelocity.x = targetMovingSpeed;
        }
        if (Input.GetKey(KeyCode.W)) // Вперед
        {
            targetVelocity.y = targetMovingSpeed;
        }
        if (Input.GetKey(KeyCode.S)) // Назад
        {
            targetVelocity.y = -targetMovingSpeed;
        }

        // Применяем движение.
        rigidbody.velocity = transform.rotation * new Vector3(targetVelocity.x, rigidbody.velocity.y, targetVelocity.y);
    }
}