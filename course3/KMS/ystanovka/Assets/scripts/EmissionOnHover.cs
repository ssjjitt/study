using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EmissionOnHover : MonoBehaviour
{
    public Material hoverMaterial;
    private Dictionary<Renderer, Material> originalMaterials = new Dictionary<Renderer, Material>();

    private void Start()
    {
        SaveOriginalMaterials(transform);
    }

    private void SaveOriginalMaterials(Transform parent)
    {
        foreach (Transform child in parent)
        {
            Renderer childRenderer = child.GetComponent<Renderer>();
            if (childRenderer != null)
            {
                originalMaterials[childRenderer] = childRenderer.material;
            }
            SaveOriginalMaterials(child); // рекурсия для дочерних
        }
    }

    public void Change()
    {
        ChangeMaterials(transform, true);
    }

    private void ChangeMaterials(Transform parent, bool isHovering)
    {
        foreach (Transform child in parent)
        {
            Renderer childRenderer = child.GetComponent<Renderer>();
            if (childRenderer != null)
            {
                if (isHovering)
                {
                    childRenderer.material = hoverMaterial;
                    childRenderer.material.SetColor("_EmissionColor", new Color(0.6f, 0.8f, 0.6f));
                    childRenderer.material.EnableKeyword("_EMISSION"); 
                }
                else
                {
                    childRenderer.material.SetColor("_EmissionColor", Color.black);
                    childRenderer.material.DisableKeyword("_EMISSION"); 
                }
            }
            ChangeMaterials(child, isHovering);
        }
    }

    public void ChangeBack()
    {
        RestoreOriginalMaterials(transform);
    }

    private void RestoreOriginalMaterials(Transform parent)
    {
        foreach (Transform child in parent)
        {
            Renderer childRenderer = child.GetComponent<Renderer>();
            if (childRenderer != null && originalMaterials.ContainsKey(childRenderer))
            {
                childRenderer.material = originalMaterials[childRenderer];
                childRenderer.material.SetColor("_EmissionColor", Color.black);
                childRenderer.material.DisableKeyword("_EMISSION");
            }
            RestoreOriginalMaterials(child);
        }
    }
}