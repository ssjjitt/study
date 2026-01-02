using UnityEngine;

public class LidClickOpener : MonoBehaviour
{
    public Vector3 openPosition;
    public Vector3 openRotation;
    public float duration = 1f;

    private Vector3 startPos;
    private Vector3 startRot;
    private bool isAnimating = false;
    private bool isOpenedAlready = false;

    void Start()
    {
        startPos = transform.localPosition;
        startRot = transform.localEulerAngles;
    }

    void OnMouseDown()
    {
        if (!isAnimating && !isOpenedAlready)
            StartCoroutine(OpenLid());
    }

    private System.Collections.IEnumerator OpenLid()
    {
        isAnimating = true;

        float t = 0f;
        Vector3 initialPos = transform.localPosition;
        Vector3 initialRot = transform.localEulerAngles;

        while (t < duration)
        {
            t += Time.deltaTime;
            float progress = t / duration;

            transform.localPosition = Vector3.Lerp(initialPos, openPosition, progress);
            transform.localEulerAngles = Vector3.Lerp(initialRot, openRotation, progress);

            yield return null;
        }

        transform.localPosition = openPosition;
        transform.localEulerAngles = openRotation;

        isAnimating = false;
        isOpenedAlready = true;   // больше НЕ закрывается
    }
}
