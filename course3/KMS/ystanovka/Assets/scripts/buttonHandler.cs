using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class buttonHandler : MonoBehaviour
{
    public textAndCamScript magazine; // ������ �� ��� ������
    public Transform target; // ������ �� ������� ������
    public string message; // ��������� ��� �����������
    public void OnButtonClick()
    {
        magazine.ShowMessageAndMoveCamera(target, message);
    }
}
