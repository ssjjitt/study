using UnityEngine;
using UnityEngine.EventSystems;

public class UIButtonHover : MonoBehaviour,
    IPointerEnterHandler, IPointerExitHandler
{
    public EmissionOnHover target;

    public void OnPointerEnter(PointerEventData eventData)
    {
        target.Change();
    }

    public void OnPointerExit(PointerEventData eventData)
    {
        target.ChangeBack();
    }
}
