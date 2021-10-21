using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class HeartScript : MonoBehaviour
{
    void OnTriggerEnter2D(Collider2D collision) {

        PlayerMovement player = collision.GetComponent<PlayerMovement>();
        if(player!=null){
            Destroy(gameObject);
            player.incrementLife();
        }
    }
}
