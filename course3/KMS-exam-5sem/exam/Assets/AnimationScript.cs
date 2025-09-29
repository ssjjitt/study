using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AnimationScript : MonoBehaviour
{
    public Animator anim;
    void Start()
    {
        anim = GetComponent<Animator>();
        anim.SetBool("Boool", false);
        // anim.enabled = false;
    }

    public void PlayAnimation()
    {
        // anim.enabled = true;
        // anim.Play();
        anim.SetBool("Boool", true);
    }
}
