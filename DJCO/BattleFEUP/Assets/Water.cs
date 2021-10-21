using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Water : MonoBehaviour
{
    void OnTriggerEnter2D(Collider2D collision) {

        PlayerMovement player = collision.GetComponent<PlayerMovement>();
        if(player!=null){
            player.slowDown();
        }

    }
    void OnTriggerExit2D(Collider2D collision) {
        PlayerMovement player = collision.GetComponent<PlayerMovement>();
        if(player!=null){
            player.normalizeSpeed();
        }
    }
}
