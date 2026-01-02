using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class socketControllerScript : MonoBehaviour
{
    private Animator animator;

    void Start()
    {
        animator = GetComponent<Animator>();
        animator.SetBool("Trigger", false);
    }

    void Update()
    {
        if (Input.GetKeyDown(KeyCode.E))
        {
            AnimatorStateInfo stateInfo = animator.GetCurrentAnimatorStateInfo(0);
            if (!stateInfo.IsName("socket")) 
            {
                animator.SetTrigger("Trigger");
            }
        }
    }
}

