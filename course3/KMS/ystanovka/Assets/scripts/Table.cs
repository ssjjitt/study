using System;
using TMPro;
using UnityEngine;
using UnityEngine.UI;

public class TableScript : MonoBehaviour
{
    [SerializeField]
    TMP_InputField textInput; // главный инпут
    [SerializeField]
    TMP_InputField l11, // !
        l21,
        l31,
        l1l1, // !
        l1l2,
        l1l3;
    [SerializeField]
    TMP_InputField c01, // !
        c02,
        c03,
        cx1, // !
        cx2,
        cx3;
    [SerializeField]
    TMP_InputField cxsr;

    public GameObject tablePanel;

    private const float L = 1.0f;
    private float L1 = 0f;
    private float L2 = 0f;
    private float L3 = 0f;
    private float C1 = 0f;
    private float C2 = 0f;
    private float C3 = 0f;
    private float C1x = 0f;
    private float C2x = 0f;
    private float C3x = 0f;
    private float Cxsr = 0f;

    public void Start()
    {
        tablePanel.SetActive(false);
    }

    public void WriteValue()
    {
        if (string.IsNullOrWhiteSpace(textInput.text))
        {
            Debug.LogWarning("¬ведите значение!");
            return;
        }
        if (l11.text == "-")
        {
            l11.text = textInput.text.ToString();
            L1 = float.Parse(l11.text);
        }
        else if (l21.text == "-")
        {
            l21.text = textInput.text.ToString();
            L2 = float.Parse(l21.text);
        }
        else if (l31.text == "-")
        {
            l31.text = textInput.text.ToString();
            L3 = float.Parse(l31.text);
            l1l1.text = (L - L1).ToString();
            l1l2.text = (L - L2).ToString();
            l1l3.text = (L - L3).ToString();
        }
        else if (c01.text == "-")
        {
            c01.text = textInput.text.ToString();
            C1 = float.Parse(c01.text);
        }
        else if (c02.text == "-")
        {
            c02.text = textInput.text.ToString();
            C2 = float.Parse(c02.text);
        }
        else if (c03.text == "-")
        {
            c03.text = textInput.text.ToString();
            C3 = float.Parse(c03.text);
            C1x = C1 * (L - L1) / L1;
            cx1.text = C1x.ToString();
            C2x = C2 * (L - L2) / L2;
            cx2.text = C2x.ToString();
            C3x = C3 * (L - L3) / L3;
            cx3.text = C3x.ToString();
            Cxsr = C1x + C2x + C3x;
            cxsr.text = Cxsr.ToString();
        }
        textInput.text = "";
    }

    public void Clean()
    {
        l11.text = "-";
        l21.text = "-";
        l31.text = "-";
        l1l1.text = "-";
        l1l2.text = "-";
        l1l3.text = "-";
        c01.text = "-";
        c02.text = "-";
        c03.text = "-";
        cx1.text = "-";
        cx2.text = "-";
        cx3.text = "-";
        cxsr.text = "-";
    }

    private bool isTableInitialized = false;

    public void ToggleHelpWindow()
    {
        tablePanel.SetActive(!tablePanel.activeSelf);
        if (!isTableInitialized)
        {
            l11.text = "-";
            l21.text = "-";
            l31.text = "-";
            l1l1.text = "-";
            l1l2.text = "-";
            l1l3.text = "-";
            c01.text = "-";
            c02.text = "-";
            c03.text = "-";
            cx1.text = "-";
            cx2.text = "-";
            cx3.text = "-";
            cxsr.text = "-";
            isTableInitialized = true;
        }
    }
}