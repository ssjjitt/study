using UnityEngine;

public class cameras : MonoBehaviour
{
    public Transform target;
    public Camera Camera_People;
    public Camera Camera_Orbit;
    public float distance = 2.0f;
    public float speed = 1.0f;

    private float currentAngle = 0.6f;

    public void Start()
    {
        Camera_People.gameObject.SetActive(true);
        Camera_Orbit.gameObject.SetActive(false);
    }

    public void Update()
    {
        if (Input.GetKeyDown(KeyCode.Z))
        {
            SwitchToPeopleCamera();
        }

        if (Input.GetKeyDown(KeyCode.X))
        {
            SwitchToOrbitCamera();
        }

        if (Input.GetKey(KeyCode.Q))
        {
            if (target != null)
            {
                currentAngle += speed * Time.deltaTime;

                Vector3 offset = new Vector3(Mathf.Sin(currentAngle), 1.0f, Mathf.Cos(currentAngle)) * distance;
                transform.position = target.position + offset;

                transform.LookAt(target);
            }
        }
    }

    public void SwitchToPeopleCamera()
    {
        Camera_People.gameObject.SetActive(true);
        Camera_Orbit.gameObject.SetActive(false);
    }

    public void SwitchToOrbitCamera()
    {
        Camera_People.gameObject.SetActive(false);
        Camera_Orbit.gameObject.SetActive(true);
    }
}