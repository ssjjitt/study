using UnityEngine;

public class SpotlightSwayX : MonoBehaviour
{
    [Header("Ќастройки вращени€")]
    [Tooltip("ћаксимальный угол отклонени€ от центра (в градусах)")]
    public float angleLimit = 30f;

    [Tooltip("—корость колебани€")]
    public float speed = 2.0f;

    private Quaternion initialRotation;

    void Start()
    {
        // «апоминаем начальное положение, чтобы колебатьс€ относительно него
        initialRotation = transform.localRotation;
    }

    void Update()
    {
        // ¬ычисл€ем угол: Sin дает значение от -1 до 1, умножаем на лимит
        float angle = Mathf.Sin(Time.time * speed) * angleLimit;

        // —оздаем вращение только по оси X
        Quaternion targetRotation = Quaternion.AngleAxis(angle, Vector3.right);

        // ѕримен€ем вращение относительно стартовой позиции
        transform.localRotation = initialRotation * targetRotation;
    }
}