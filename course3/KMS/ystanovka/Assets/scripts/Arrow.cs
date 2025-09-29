using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Arrow : MonoBehaviour
{
    // �������
    private Vector3 startPosition = new Vector3(-8.071f, 1.9334f, -0.6911f);
    private Vector3 middlePosition = new Vector3(-8.0984f, 1.932f, -0.6911f);
    private Vector3 endPosition = new Vector3(-8.13086f, 1.9305f, -0.6911f);

    // ���������
    public float moveSpeed = 1.0f; // �������� ��������
    public float positionChangeSpeed = 2.0f; // �������� ��������� �������
    private Quaternion targetRotation; // ������� ��������
    private Vector3 targetPosition; // ������� �������
    private bool isMoving = false; // ���� ��������

    void Start()
    {
        // ������������� ��������� ��������� � ��������
        transform.position = middlePosition;
        transform.rotation = Quaternion.Euler(0f, 0f, 0f); // ��������� ��������
        targetRotation = transform.rotation; // ���������� ���� ����� �������� ��������
        targetPosition = transform.position; // ���������� ���� ����� ������� �������
    }

    void Update()
    {
        // ��������� ������� ������
        if ((Input.GetKeyDown(KeyCode.RightArrow) || Input.GetKeyDown(KeyCode.Keypad7) || Input.GetKeyDown(KeyCode.Keypad8) || Input.GetKeyDown(KeyCode.Keypad9) || Input.GetKeyDown(KeyCode.Keypad4)) && !isMoving)
        {
            float randomAngle = Random.Range(54.32f, 113.5f);
            SetRandomTargetRotation(randomAngle); // ���������� ��������� ���� ��� ������
        }
        else if ((Input.GetKeyDown(KeyCode.LeftArrow) || Input.GetKeyDown(KeyCode.Keypad7) || Input.GetKeyDown(KeyCode.Keypad8) || Input.GetKeyDown(KeyCode.Keypad9) || Input.GetKeyDown(KeyCode.Keypad4)) && !isMoving)
        {
            float randomAngle = Random.Range(0f, 54.32f);
            SetRandomTargetRotation(randomAngle); // ���������� ��������� ���� ��� �����
        }

        // ������� �������� � ��������� �������
        if (isMoving)
        {
            // ������� ��������
            transform.rotation = Quaternion.Lerp(transform.rotation, targetRotation, Time.deltaTime * moveSpeed);
            // ������� ��������� �������
            transform.position = Vector3.Lerp(transform.position, targetPosition, Time.deltaTime * positionChangeSpeed);

            // ���������, �������� �� �� �������� ���� � �������
            if (Quaternion.Angle(transform.rotation, targetRotation) < 1f && Vector3.Distance(transform.position, targetPosition) < 0.01f)
            {
                isMoving = false; // ������������� ��������
            }
        }
    }

    private void SetRandomTargetRotation(float randomAngle)
    {
        // ������������� ������� � �������� � ����������� �� �������� randomAngle
        if (randomAngle <= 22.502f)
        {
            targetPosition = startPosition; // ������������� ������� �������
            targetRotation = Quaternion.Euler(0, 0, randomAngle); // ������������� ������� ��������
        }
        else if (randomAngle >= 91f && randomAngle <= 113.5f)
        {
            targetPosition = endPosition; // ������������� ������� �������
            targetRotation = Quaternion.Euler(0, 0, randomAngle); // ������������� ������� ��������
        }
        else if (randomAngle > 22.502f && randomAngle < 91f)
        {
            targetPosition = middlePosition; // ������������� ������� �������
            targetRotation = Quaternion.Euler(0, 0, randomAngle); // ������������� ������� ��������
        }

        isMoving = true; // �������� ��������
    }
}