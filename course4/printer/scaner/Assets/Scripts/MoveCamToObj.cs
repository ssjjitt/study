using TMPro;
using UnityEngine;
using System.Collections;

public class MoveCamToObj : MonoBehaviour
{
    public TextMeshProUGUI textMeshPro;
    public Camera camera;
    public float distance = -0f;
    public float heightOffset = 0f;
    public float lateralOffset = 0f;
    public float speed = 0f;

    public float xOffset = 0f;  
    public float yOffset = 0f;  
    public float zOffset = 0f;  

    private Vector3 originalPosition;
    private Quaternion originalRotation;
    private bool isAtTarget = false;

    void Start()
    {
        originalPosition = camera.transform.position;
        originalRotation = camera.transform.rotation;
    }

    public void MoveCameraAndShowText(Transform target, string message)
    {
        if (camera.isActiveAndEnabled)
        {
            if (isAtTarget)
            {
                StartCoroutine(MoveCamera(originalPosition, originalRotation));
                textMeshPro.text = "";
            }
            else
            {
                Vector3 targetPosition = target.position - target.forward * distance;
                targetPosition.y += heightOffset;
                targetPosition.z += lateralOffset;

                targetPosition.x += xOffset;
                targetPosition.y += yOffset;
                targetPosition.z += zOffset;

                StartCoroutine(MoveCamera(targetPosition, Quaternion.LookRotation(target.position - targetPosition)));
                textMeshPro.text = message;
            }
            isAtTarget = !isAtTarget;
        }
        else
        {
            Debug.Log("Смените камеру, нажав X, пожалуйста.");
        }
    }

    public IEnumerator MoveCamera(Vector3 targetPos, Quaternion targetRot)
    {
        float elapsedTime = 0f;
        Vector3 startingPos = camera.transform.position;
        Quaternion startingRot = camera.transform.rotation;

        while (elapsedTime < speed)
        {
            camera.transform.position = Vector3.Lerp(startingPos, targetPos, (elapsedTime / speed));
            //camera.transform.rotation = Quaternion.Slerp(startingRot, targetRot, (elapsedTime / speed));
            elapsedTime += Time.deltaTime;
            yield return null;
        }

        camera.transform.position = targetPos;
        //camera.transform.rotation = targetRot;
    }
}
