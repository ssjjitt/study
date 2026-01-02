using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class QuaternionRotation_task10 : MonoBehaviour
{
    public GameObject gameObject; // префаб

    void Update()
    {
        // вращение через кватернионы + Mouse X + Mouse Y
        var inpMX = Input.GetAxis("Mouse X");
        var inpMY = Input.GetAxis("Mouse Y");
        Quaternion quaternion = Quaternion.Euler(inpMY, inpMX, 0);
        transform.rotation *= quaternion;

        // Horizontal + Vertical + перемещение
        var inpHor = Input.GetAxis("Horizontal");
        var inpVer = Input.GetAxis("Vertical");
        transform.position += new Vector3(inpHor, inpVer, 0);

        // генерация объектов
        if (Input.GetKeyDown(KeyCode.Q))
        {
            GameObject cube = GameObject.CreatePrimitive(PrimitiveType.Cube);
            int random = Random.Range(1,10);
            cube.transform.position = new Vector3(random, random + 3, random);
        }

        if (Input.GetKeyDown(KeyCode.E))
        {
            int random = Random.Range(1,10);
            Instantiate(gameObject, new Vector3(random, random, random),Quaternion.identity);
        }

        // поступательное вращение
        if (Input.GetKey(KeyCode.R))
        {
            transform.Rotate(new Vector3(1,0,0));
        }

        // поступательное движение
        if (Input.GetKey(KeyCode.T))
        {
            transform.Translate(new Vector3(1, 0, 0));
        }
    }
}
