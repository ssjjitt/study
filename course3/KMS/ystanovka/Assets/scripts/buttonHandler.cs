using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class buttonHandler : MonoBehaviour
{
    public textAndCamScript magazine; // —сылка на ваш скрипт
    public Transform target; // —сылка на целевой объект
    public string message; // —ообщение дл€ отображени€
    public void OnButtonClick()
    {
        magazine.ShowMessageAndMoveCamera(target, message);
    }
}
