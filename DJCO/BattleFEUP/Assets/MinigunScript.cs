using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class MinigunScript : MonoBehaviour
{
   void OnTriggerEnter2D(Collider2D collision) {

        PlayerMovement player = collision.GetComponent<PlayerMovement>();
        if(player!=null){
            Destroy(gameObject);
            //TODO
        }
        PlayerMovement weapons = collision.GetComponent<PlayerMovement>();
        if (weapons != null)
        {
            weapons.currentWeapon = 3;
            weapons.minigunTime = 15;
            weapons.firstWeaponDisplay.GetComponent<Outline>().effectColor = new Color(0.566f, 0.507f, 0.093f, 0.500f);
            weapons.secondWeaponDisplay.GetComponent<Outline>().effectColor = new Color(0f, 0f, 0f, 0.500f);
        }
    }
}
