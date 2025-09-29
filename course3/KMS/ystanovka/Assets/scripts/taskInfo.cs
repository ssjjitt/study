using System.Collections;
using TMPro;
using UnityEngine;

public class taskInfo : MonoBehaviour
{
    public TextMeshProUGUI textMeshPro; 
    public string message;

    public void ShowMessage()
    {
        textMeshPro.text = message; 
    }
}