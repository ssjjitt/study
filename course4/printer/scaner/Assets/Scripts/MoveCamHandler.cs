using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MoveCamHandler : MonoBehaviour
{
    public MoveCamToObj script; 
    public Transform target; 
    public string message; 
    public void OnButtonClick()
    {
        script.MoveCameraAndShowText(target, message);
    }
}
