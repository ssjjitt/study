using UnityEngine;

public class RollerRotate : MonoBehaviour
{
    public float rotateSpeed = 300f;

    void Update()
    {
        transform.Rotate(Vector3.up * rotateSpeed * Time.deltaTime);
    }
}
