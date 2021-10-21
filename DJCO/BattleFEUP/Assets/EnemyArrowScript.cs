using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyArrowScript : MonoBehaviour
{
    public GameObject enemies;
    public Transform soldier;
    private RectTransform pointerRectTransform;

    private void Awake() {
        pointerRectTransform = transform.Find("Pointer").GetComponent<RectTransform>();
    }

    private void Update() {
        if (enemies.transform.childCount == 0)
            return;
        Vector3 toPosition = GetClosestEnemy().position;
        Vector3 fromPosition = Camera.main.transform.position;
        fromPosition.z = 0f;
        Vector3 dir = (toPosition - fromPosition).normalized;
        float angle = Mathf.Atan2(dir.y, dir.x) * Mathf.Rad2Deg;
        if (angle < 0) angle += 360;
        pointerRectTransform.localEulerAngles = new Vector3(0, 0, angle);
    }

    Transform GetClosestEnemy()
    {
        Transform bestTarget = null;
        float closestDistanceSqr = Mathf.Infinity;
        Vector3 currentPosition = soldier.position;
        foreach(Transform potentialTarget in enemies.transform)
        {
            Vector3 directionToTarget = potentialTarget.position - currentPosition;
            float dSqrToTarget = directionToTarget.sqrMagnitude;
            if(dSqrToTarget < closestDistanceSqr)
            {
                closestDistanceSqr = dSqrToTarget;
                bestTarget = potentialTarget;
            }
        }
     
        return bestTarget;
    }
}
