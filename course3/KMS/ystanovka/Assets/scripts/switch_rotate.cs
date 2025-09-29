using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class switch_rotate : MonoBehaviour
{
    private float currentRotationX = 90f;
    private float targetRotationX;
    public float rotationSpeed = 360f; 

    void Start()
    {
        targetRotationX = currentRotationX;
    }

    void Update()
    {
        if (Input.GetKeyDown(KeyCode.Keypad7))
        {
            ChangeRotation();
        }

        float step = rotationSpeed * Time.deltaTime * 25;
        currentRotationX = Mathf.MoveTowards(currentRotationX, targetRotationX, step);
        transform.rotation = Quaternion.Euler(currentRotationX, 90f, 90f);
    }

    void ChangeRotation()
    {
        targetRotationX -= 30f; 

        /*// ограничение если нужно будет
        if (targetRotationX >= 360f)
        {
        }*/
    }
}
