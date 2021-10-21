using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;


public class CameraScript : MonoBehaviour
{
    public Texture2D defaultCrosshair;
    public Text timerText;
    public GameObject gameOver;
    public float secondsCount;
    public int minuteCount;
    public int hourCount;
    private float ZoomAmount = 0f;
    private float MaxToClamp = 1f;
    private float ROTSpeed  = 10f;
    void Start()
    {
        Cursor.SetCursor(defaultCrosshair, new Vector2(defaultCrosshair.width / 2, defaultCrosshair.height / 2), CursorMode.ForceSoftware);
    }
    public Transform player;
    public Vector3 offset;

    public void UpdateTimerUI(){
         if (gameOver.activeSelf)
             return;
         secondsCount += Time.deltaTime;
         timerText.text = hourCount +"H "+ minuteCount +"M "+(int)secondsCount + "S";
         if(secondsCount >= 60){
             minuteCount++;
             secondsCount = 0;
         }else if(minuteCount >= 60){
             hourCount++;
             minuteCount = 0;
         }    
    }
  
    void Update () 
    {
        ZoomAmount += Input.GetAxis("Mouse ScrollWheel");
     ZoomAmount = Mathf.Clamp(ZoomAmount, -MaxToClamp, MaxToClamp);
     var translate = Mathf.Min(Mathf.Abs(Input.GetAxis("Mouse ScrollWheel")), MaxToClamp - Mathf.Abs(ZoomAmount));
     transform.Translate(0,0,translate * ROTSpeed * Mathf.Sign(Input.GetAxis("Mouse ScrollWheel")));

        transform.position = new Vector3 (player.position.x + offset.x, player.position.y + offset.y,Mathf.Min(-10,transform.position.z)); // Camera follows the player with specified offset position 

        //transform.position = new Vector3 (,translate * ROTSpeed * Mathf.Sign(Input.GetAxis("Mouse ScrollWheel"))); // Camera follows the player with specified offset position
        UpdateTimerUI();

    }
}
