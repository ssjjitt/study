using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UIElements;
using UnityEngine.EventSystems;

public class Work : MonoBehaviour, IPointerClickHandler
{
    public float moveX; 
    public float moveY; 
    public float moveZ;

    public void OnPointerClick(PointerEventData eventData)
    {
        Debug.Log("Object clicked!");
        Vector3 moveOffset = new Vector3(moveX, moveY, moveZ);
        transform.position += moveOffset;
    }
}
