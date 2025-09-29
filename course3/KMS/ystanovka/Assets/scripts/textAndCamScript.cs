using System.Collections;
using TMPro;
using UnityEngine;

public class textAndCamScript : MonoBehaviour
{
    public TextMeshProUGUI textMeshPro; // ������ �� ��������� TextMeshPro
    public Camera camera; // ������ �� ������
    public float distance = -1f; // ���������� �� ������ �� �������
    public float heightOffset = 1.3f; // �������� �� ������
    public float lateralOffset = -0.4f; // �������� �����-������
    public float speed = 0.3f; // �������� ����������� ������

    private Vector3 originalPosition; // �������� ������� ������
    private Quaternion originalRotation; // �������� ���������� ������
    private bool isAtTarget = false; // ������� ��������� ������

    void Start()
    {
        // ��������� �������� ������� � ���������� ������
        originalPosition = camera.transform.position;
        originalRotation = camera.transform.rotation;
    }

    public void ShowMessageAndMoveCamera(Transform target, string message)
    {
        if (isAtTarget)
        {
            // ���������� ������ � �������� ���������
            StartCoroutine(MoveCamera(originalPosition, originalRotation));
            textMeshPro.text = ""; // ������� �����
        }
        else
        {
            // ������������ ������� ��� ������ � ������ ������ � ��������
            Vector3 targetPosition = target.position - target.forward * distance;
            targetPosition.y += heightOffset; // ��������� ������ ����
            targetPosition.x += lateralOffset; // �������� ������
            StartCoroutine(MoveCamera(targetPosition, Quaternion.LookRotation(target.position - targetPosition)));
            textMeshPro.text = message; // ������������� �����
        }
        isAtTarget = !isAtTarget; // ����������� ���������
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
            yield return null; // ���� ���������� �����
        }

        // ��������, ��� ������ ����� ��������
        camera.transform.position = targetPos;
        //camera.transform.rotation = targetRot;
    }
}