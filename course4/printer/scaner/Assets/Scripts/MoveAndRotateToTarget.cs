using UnityEngine;
using System.Collections;

public class MoveAndRotateToTarget : MonoBehaviour
{
    public Transform targetTransform;
    public float duration = 1f;

    private bool isMoving = false;

    public void MoveToTarget()
    {
        Debug.Log("Метод MoveToTarget вызван!");
        if (!isMoving)
            StartCoroutine(MoveRoutine());
    }

    private IEnumerator MoveRoutine()
    {
        isMoving = true;

        Vector3 startPos = transform.position;
        Quaternion startRot = transform.rotation;

        Vector3 targetPos = targetTransform.position;
        Quaternion targetRot = targetTransform.rotation;

        float t = 0f;

        while (t < duration)
        {
            t += Time.deltaTime;
            float progress = t / duration;

            transform.position = Vector3.Lerp(startPos, targetPos, progress);
            transform.rotation = Quaternion.Lerp(startRot, targetRot, progress);

            yield return null;
        }

        transform.position = targetPos;
        transform.rotation = targetRot;

        isMoving = false;
    }
}
