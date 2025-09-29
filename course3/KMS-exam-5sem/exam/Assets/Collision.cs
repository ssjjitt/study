using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CollisionScript : MonoBehaviour
{
    private Renderer rend;
    AudioSource audioSource;
    void Start()
    {
        rend = GetComponent<Renderer>();
        audioSource = GetComponent<AudioSource>();
    }

    private void OnCollisionEnter(Collision collision)
    {
        if (gameObject.name == "Push")
        {
            rend.material.color = new Color(Random.value, Random.value, Random.value);
            
            Renderer otherRend = collision.gameObject.GetComponent<Renderer>();
            otherRend.material.color = new Color(Random.value, Random.value, Random.value);
        }
        audioSource.Play();
    }
}
