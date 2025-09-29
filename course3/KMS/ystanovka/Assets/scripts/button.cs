using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;

public class button : MonoBehaviour, IPointerClickHandler
{
    private Animator animator;

    void Start()
    {
        animator = GetComponent<Animator>();
        animator.SetBool("Trigger", false);
    }

    public void OnPointerClick(PointerEventData eventData)
    {
        Debug.Log("Object clicked!");
        animator.SetTrigger("Trigger");
    }
}
