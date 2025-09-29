using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Arrow : MonoBehaviour
{
    // Позиции
    private Vector3 startPosition = new Vector3(-8.071f, 1.9334f, -0.6911f);
    private Vector3 middlePosition = new Vector3(-8.0984f, 1.932f, -0.6911f);
    private Vector3 endPosition = new Vector3(-8.13086f, 1.9305f, -0.6911f);

    // Параметры
    public float moveSpeed = 1.0f; // Скорость вращения
    public float positionChangeSpeed = 2.0f; // Скорость изменения позиции
    private Quaternion targetRotation; // Целевое вращение
    private Vector3 targetPosition; // Целевая позиция
    private bool isMoving = false; // Флаг движения

    void Start()
    {
        // Устанавливаем начальное положение и вращение
        transform.position = middlePosition;
        transform.rotation = Quaternion.Euler(0f, 0f, 0f); // Начальное вращение
        targetRotation = transform.rotation; // Изначально цель равна текущему вращению
        targetPosition = transform.position; // Изначально цель равна текущей позиции
    }

    void Update()
    {
        // Проверяем нажатие клавиш
        if ((Input.GetKeyDown(KeyCode.RightArrow) || Input.GetKeyDown(KeyCode.Keypad7) || Input.GetKeyDown(KeyCode.Keypad8) || Input.GetKeyDown(KeyCode.Keypad9) || Input.GetKeyDown(KeyCode.Keypad4)) && !isMoving)
        {
            float randomAngle = Random.Range(54.32f, 113.5f);
            SetRandomTargetRotation(randomAngle); // Генерируем случайный угол для вправо
        }
        else if ((Input.GetKeyDown(KeyCode.LeftArrow) || Input.GetKeyDown(KeyCode.Keypad7) || Input.GetKeyDown(KeyCode.Keypad8) || Input.GetKeyDown(KeyCode.Keypad9) || Input.GetKeyDown(KeyCode.Keypad4)) && !isMoving)
        {
            float randomAngle = Random.Range(0f, 54.32f);
            SetRandomTargetRotation(randomAngle); // Генерируем случайный угол для влево
        }

        // Плавное вращение и изменение позиции
        if (isMoving)
        {
            // Плавное вращение
            transform.rotation = Quaternion.Lerp(transform.rotation, targetRotation, Time.deltaTime * moveSpeed);
            // Плавное изменение позиции
            transform.position = Vector3.Lerp(transform.position, targetPosition, Time.deltaTime * positionChangeSpeed);

            // Проверяем, достигли ли мы целевого угла и позиции
            if (Quaternion.Angle(transform.rotation, targetRotation) < 1f && Vector3.Distance(transform.position, targetPosition) < 0.01f)
            {
                isMoving = false; // Останавливаем движение
            }
        }
    }

    private void SetRandomTargetRotation(float randomAngle)
    {
        // Устанавливаем позицию и вращение в зависимости от значения randomAngle
        if (randomAngle <= 22.502f)
        {
            targetPosition = startPosition; // Устанавливаем целевую позицию
            targetRotation = Quaternion.Euler(0, 0, randomAngle); // Устанавливаем целевое вращение
        }
        else if (randomAngle >= 91f && randomAngle <= 113.5f)
        {
            targetPosition = endPosition; // Устанавливаем целевую позицию
            targetRotation = Quaternion.Euler(0, 0, randomAngle); // Устанавливаем целевое вращение
        }
        else if (randomAngle > 22.502f && randomAngle < 91f)
        {
            targetPosition = middlePosition; // Устанавливаем целевую позицию
            targetRotation = Quaternion.Euler(0, 0, randomAngle); // Устанавливаем целевое вращение
        }

        isMoving = true; // Начинаем движение
    }
}