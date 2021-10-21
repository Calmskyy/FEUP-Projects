using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Shop : MonoBehaviour
{
    public UI_Shop ui_shop;
    public Texture2D defaultCrosshair;


    private void OnTriggerEnter2D(Collider2D collision){
        PlayerMovement player = collision.GetComponent<PlayerMovement>();

        if(player!=null){
            ui_shop.Show(player);
            Cursor.SetCursor(null, Vector2.zero, CursorMode.Auto); 
        }
    }

    private void OnTriggerExit2D(Collider2D collision) {

        PlayerMovement player = collision.GetComponent<PlayerMovement>();

        if(player!=null){
            ui_shop.Hide();
            Cursor.SetCursor(defaultCrosshair, new Vector2(defaultCrosshair.width / 2, defaultCrosshair.height / 2), CursorMode.ForceSoftware);

        }
    }

}
