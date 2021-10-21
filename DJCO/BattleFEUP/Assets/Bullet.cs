using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Bullet : MonoBehaviour
{
   public GameObject hitEffect;
   public int damage;
   float timeAlive = 0f;

    void OnTriggerEnter2D(Collider2D collision) {

        Enemy enemy = collision.GetComponent<Enemy>();
        PlayerMovement player = collision.GetComponent<PlayerMovement>();
        Water water = collision.GetComponent<Water>();
        CoinScript coin = collision.GetComponent<CoinScript>();
        HeartScript heart = collision.GetComponent<HeartScript>();
        Bullet bullet = collision.GetComponent<Bullet>();
        MineScript mine = collision.GetComponent<MineScript>();
        HiddenMineScript hiddenMine = collision.GetComponent<HiddenMineScript>();

        if (enemy!=null){
            enemy.takeDamage(damage);

            GameObject effect = Instantiate(hitEffect , transform.position , Quaternion.identity);
            Destroy(effect,0.3f);
            Destroy(gameObject);
        }
        else if(player!=null){
            player.takeDamage(damage/5);
            
            GameObject effect = Instantiate(hitEffect , transform.position , Quaternion.identity);
            Destroy(effect,0.3f);
            Destroy(gameObject);
        }
        else if(water!=null){
            Physics2D.IgnoreCollision(water.GetComponent<Collider2D>(), GetComponent<Collider2D>());
        }
        else if(coin!=null){
            Physics2D.IgnoreCollision(coin.GetComponent<Collider2D>(), GetComponent<Collider2D>());
        }
        else if(heart!=null){
            Physics2D.IgnoreCollision(heart.GetComponent<Collider2D>(), GetComponent<Collider2D>());
        }
        else if(bullet!=null){
            Physics2D.IgnoreCollision(bullet.GetComponent<Collider2D>(), GetComponent<Collider2D>());
        }
        else if(mine!=null){
            Physics2D.IgnoreCollision(mine.GetComponent<Collider2D>(), GetComponent<Collider2D>());
        }
        else if(hiddenMine!=null){
            Physics2D.IgnoreCollision(hiddenMine.GetComponent<Collider2D>(), GetComponent<Collider2D>());
        }
        else
        {
            GameObject effect = Instantiate(hitEffect , transform.position , Quaternion.identity);
            Destroy(effect,0.3f);
            Destroy(gameObject);
        }

    }

   void OnCollisionEnter2D(Collision2D collision) {
        GameObject effect = Instantiate(hitEffect , transform.position , Quaternion.identity);
        Destroy(effect,0.3f);
        Destroy(gameObject);
   }

   void Update() {
       timeAlive += Time.deltaTime;
       if (timeAlive >= 1.1f)
           Destroy(gameObject);
   }
}
