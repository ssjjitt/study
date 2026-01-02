using System.Collections.Generic;
using UnityEngine;

public class EmissionOnHover : MonoBehaviour
{
    public Material hoverMaterial;
    private Dictionary<Renderer, Material> originals = new Dictionary<Renderer, Material>();

    private void Start()
    {
        // ВАЖНО: GetComponentsInChildren(true) берет рендерер с САМОГО куба + всех детей
        var renderers = GetComponentsInChildren<Renderer>(true);

        foreach (var r in renderers)
        {
            if (!originals.ContainsKey(r))
            {
                originals.Add(r, r.material); // Сохраняем родной материал
            }
        }

        // Для проверки (увидишь в консоли, если сработало)
        Debug.Log($"Найдено частей для покраски: {originals.Count}");
    }

    public void Change()
    {
        // Проходимся по всем сохраненным рендерерам
        foreach (var entry in originals)
        {
            Renderer r = entry.Key;
            if (r != null)
            {
                r.material = hoverMaterial;
                r.material.EnableKeyword("_EMISSION");
                r.material.SetColor("_EmissionColor", new Color(0.6f, 0.8f, 0.6f));
            }
        }
    }

    public void ChangeBack()
    {
        foreach (var entry in originals)
        {
            Renderer r = entry.Key;
            Material originalMat = entry.Value;

            if (r != null)
            {
                r.material = originalMat;
                // Сбрасываем эмиссию, если она была выключена в оригинале
                r.material.DisableKeyword("_EMISSION");
                r.material.SetColor("_EmissionColor", Color.black);
            }
        }
    }
}