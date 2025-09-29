using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;

public class Wire2 : MonoBehaviour, IPointerClickHandler
{
    private Animator animator;

    void Start()
    {
        animator = GetComponent<Animator>();
        animator.SetBool("Trigger", false);
    }

    void Update()
    {
        if (Input.GetKeyDown(KeyCode.G))
        {
            AnimatorStateInfo stateInfo = animator.GetCurrentAnimatorStateInfo(0);
            if (!stateInfo.IsName("wire2"))
            {
                animator.SetTrigger("Trigger");
            }
        }
    }

    public void OnPointerClick(PointerEventData eventData)
    {
        Debug.Log("Object clicked!");
        animator.SetTrigger("Trigger");
    }
}
