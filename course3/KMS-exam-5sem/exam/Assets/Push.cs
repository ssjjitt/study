using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;

public class PushScript : MonoBehaviour, IPointerClickHandler
{
    private Rigidbody rb; // рэспублика беларусь
    void Start()
    {
        rb = GetComponent<Rigidbody>();
    }

    public void OnPointerClick(PointerEventData eventData)
    {
        Vector3 direction = (transform.position - Camera.main.ScreenToWorldPoint(Input.mousePosition)).normalized; // ебать строку в рот
        rb.AddForce(direction * 100f);
    }
}
