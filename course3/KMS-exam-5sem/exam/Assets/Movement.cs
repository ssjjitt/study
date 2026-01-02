using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Movement : MonoBehaviour
{
    AudioSource audioSource;

    private void Start()
    {
        audioSource = GetComponent<AudioSource>();
    }

    void Update()
    {
        float Hz = Input.GetAxis("Horizontal");
        float Vt = Input.GetAxis("Vertical");
        Vector3 movement = new Vector3(Hz, 0.0f, Vt);
        transform.Translate(movement * 1.5f * Time.deltaTime, Space.World);
        if (Input.GetKey(KeyCode.W))
        {
            audioSource.Play();
        }
    }
}
