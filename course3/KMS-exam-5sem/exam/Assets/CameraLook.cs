using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

// камеру подчинить кубу -> на камеру навесить скрипт

public class CameraLook : MonoBehaviour
{
    public Transform target;
    private float currentAngle, currentYAngle;

    void Update()
    {
        currentAngle += Input.GetAxis("Mouse X") * 10.0f;
        currentYAngle -= Input.GetAxis("Mouse Y") * 10.0f;
        Quaternion rotation = Quaternion.Euler(currentYAngle, currentAngle, 0);
        Vector3 offset = new Vector3(0, 0, -5f);
        transform.position = target.position + rotation * offset;
        transform.LookAt(target);
    }
}
