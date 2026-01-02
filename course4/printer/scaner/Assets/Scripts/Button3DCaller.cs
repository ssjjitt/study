using UnityEngine;

public class Button3DCaller : MonoBehaviour
{
    public MoveAndRotateToTarget mover;

    private void OnMouseDown()
    {
        Debug.Log(" ÕŒœ ¿ Õ¿∆¿“¿!");
        mover.MoveToTarget();
    }
}
