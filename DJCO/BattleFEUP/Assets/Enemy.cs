using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Enemy : MonoBehaviour
{
    public Transform firePoint;
    public GameObject bulletPre;
    public GameObject deathEffect;
    public float bulletForce = 20f;
    public Texture2D defaultCrosshair;
    public Texture2D hoverCrosshair;
    Random rnd = new Random();
    public PlayerMovement player;
    public Rigidbody2D rb;

    public int health = 100;
    public float moveSpeed = 1f;
    public int score = 10;
    public int distance = 8;

    public void takeDamage(int damage){
        health -= damage;

        if(health<=0)
            Die();
    }

    // Update is called once per frame
    void Update()
    {
        if (player.waitingRespawn == false)
            moveAndShoot();
        else
            rb.velocity = new Vector2(0, 0);
    }

    void moveAndShoot(){
        Vector3 aux = new Vector3(player.transform.position.x,player.transform.position.y,0f);
        Vector3 lookDir = aux -transform.position;

        if(lookDir.magnitude<distance){
            rb.velocity = Vector2.ClampMagnitude(new Vector2(lookDir.x, lookDir.y),moveSpeed);

            float angle = Mathf.Atan2(lookDir.y, lookDir.x) * Mathf.Rad2Deg - 90f;
            rb.rotation = angle;

            Shoot();
        }else{
            rb.velocity = new Vector2(0, 0);
        }




    }

    void Shoot(){
        if(Random.Range(0,100) ==0){
            GameObject bullet = Instantiate(bulletPre, firePoint.position, firePoint.rotation);
            Rigidbody2D rb = bullet.GetComponent<Rigidbody2D>();
            rb.AddForce(firePoint.up * bulletForce, ForceMode2D.Impulse);
        }
    }

    void Die(){
        Cursor.SetCursor(defaultCrosshair, new Vector2(defaultCrosshair.width / 2, defaultCrosshair.height / 2), CursorMode.ForceSoftware);
        GameObject effect = Instantiate(deathEffect,transform.position, Quaternion.identity);
        Destroy(gameObject);
        Destroy(effect,1f);
        player.incrementScore(score);
    }

    void OnMouseEnter()
    {
        Cursor.SetCursor(hoverCrosshair, new Vector2(hoverCrosshair.width / 2, hoverCrosshair.height / 2), CursorMode.ForceSoftware);
    }

    void OnMouseExit()
    {
        Cursor.SetCursor(defaultCrosshair, new Vector2(defaultCrosshair.width / 2, defaultCrosshair.height / 2), CursorMode.ForceSoftware);
    }
}
