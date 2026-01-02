using System.Collections;
using UnityEngine;

public class CoroutineExample : MonoBehaviour
{
    private Renderer rend;
    private Color originalColor;

    void Start()
    {
        rend = GetComponent<Renderer>();
        originalColor = rend.material.color; 
        StartCoroutine(ChangeColorWithDelay());
    }

    private IEnumerator ChangeColorWithDelay()
    {
        rend.material.color = new Color(Random.value, Random.value, Random.value);
        yield return new WaitForSeconds(2f);
        rend.material.color = originalColor;
    }
}