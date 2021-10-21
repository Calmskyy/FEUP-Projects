using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;

public class UI_Shop : MonoBehaviour
{
    public PlayerMovement player;
    public Item ammo1;
    public int ammoCoins=10;
    public int ammoAmount=30;
    public int medkitCoins=20;
    public int lifeCoins=30;

    public void Show(PlayerMovement player){
        this.player = player;
        gameObject.SetActive(true);
        player.shooting= false;
    }

    public void Hide(){
        gameObject.SetActive(false);
        player.shooting=true;
    }

    public void TryBuyAmmo(){
        if(player.hasCoins(ammoCoins)){
            player.decrementCoin(ammoCoins);
            player.giveAmmo(ammoAmount);
        }
    }

    public void TryBuyMedkit(){
        if(player.isInjured()) {
            if(player.hasCoins(medkitCoins)){
                player.decrementCoin(medkitCoins);
                player.health=100;
                }
        }
    }

    public void TryBuyLife(){
        if(player.hasCoins(lifeCoins)){
            player.decrementCoin(lifeCoins);
            player.incrementLife();
        }
    }


    public void Start(){
        Hide();
    }

}
