using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class HiddenMineScript : MonoBehaviour
{
    public GameObject mine;
    private float distanceToReveal;
    SpriteRenderer spriteRenderer;

    void Start() {
        spriteRenderer = mine.GetComponent<SpriteRenderer>();
        var tempColor = spriteRenderer.color;
        tempColor.a = 0;
        spriteRenderer.color = tempColor;
    }

    void OnTriggerEnter2D(Collider2D collision)
    {
        PlayerMovement player = collision.GetComponent<PlayerMovement>();
        if (player != null)
        {
            float dist = Vector3.Distance(player.transform.position, transform.position);
            distanceToReveal = dist - 1.5f;
        }
    }

    void OnTriggerStay2D(Collider2D collision)
    {
        PlayerMovement player = collision.GetComponent<PlayerMovement>();
        if (player == null)
            return;
        float dist = Vector3.Distance(player.transform.position, transform.position);
        float colorFactor = (distanceToReveal + 1.5f - dist) / distanceToReveal;
        var tempColor = spriteRenderer.color;
        tempColor.a = colorFactor;
        spriteRenderer.color = tempColor;
    }
}
