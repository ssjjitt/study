using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class reohord : MonoBehaviour
{
    public float moveSpeed = 0.1f;
    private float minX = -7.628501f; // ����������� �������� �� ��� X
    private float maxX = -6.236348f;  // ������������ �������� �� ��� X

    void Update()
    {
        float horizontalInput = 0f;

        // �������� ������� ������ ��� ��������
        if (Input.GetKey(KeyCode.RightArrow) && transform.position.x > minX)
        {
            horizontalInput = -1f; // �������� �����
        }
        if (Input.GetKey(KeyCode.LeftArrow) && transform.position.x < maxX)
        {
            horizontalInput = 1f; // �������� ������
        }

        // ������������ ��������
        Vector3 movement = new Vector3(horizontalInput, 0f, 0f) * moveSpeed * Time.deltaTime;
        transform.Translate(movement);

        // ������������ ������� �������
        Vector3 newPosition = transform.position;
        newPosition.x = Mathf.Clamp(newPosition.x, minX, maxX);
        transform.position = newPosition;

        // ��� �������: ����� ������� ������� � �������
        // Debug.Log("Current Position: " + transform.position.x);
    }
}