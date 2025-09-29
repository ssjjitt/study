using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Racurs : MonoBehaviour
{
    public Camera mainCamera; 
    public Transform target;
    public Vector3 cameraOffset;
    public Vector3 cameraRotation; 

    public void SetCameraView()
    {
        mainCamera.transform.position = target.position + cameraOffset;
        mainCamera.transform.rotation = Quaternion.Euler(cameraRotation);
    }

    public void Hover()
    {
        target.gameObject.GetComponent<Renderer>().material.color = Color.yellow;
    }

    public void UnHover()
    {
        target.gameObject.GetComponent<Renderer>().material.color = Color.blue;
    }
}