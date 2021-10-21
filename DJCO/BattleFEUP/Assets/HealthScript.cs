using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class HealthScript : MonoBehaviour
{
    private Image Health;
    PlayerMovement player;
    public int currentHealth;
    private float maxHealth = 100f;

    // Start is called before the first frame update
    void Start()
    {
        Health = GetComponent<Image>();
        player = FindObjectOfType<PlayerMovement>();
    }

    // Update is called once per frame
    void Update()
    {
        currentHealth = player.health;
        Health.fillAmount = currentHealth / maxHealth;
    }
}
