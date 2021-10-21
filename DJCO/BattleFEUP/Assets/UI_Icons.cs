using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI; 

public class UI_Icons : MonoBehaviour
{
    int animationFrame;
    float currentTransform;

    public void makeAnimation(){
        animationFrame = 0;
        gameObject.transform.position = gameObject.transform.position + new Vector3(0f, -currentTransform, 0f);
        currentTransform = 0;
    }

    public void Start() {
        animationFrame = 90;
        currentTransform = 0;
    }

    private void Update() {
        switch (animationFrame) {
            case 0:
            gameObject.transform.position = gameObject.transform.position + new Vector3(0f, 3f, 0f);
            currentTransform += 3;
            break;
            case 1:
            gameObject.transform.position = gameObject.transform.position + new Vector3(0f, 3f, 0f);
            currentTransform += 3;
            break;
            case 2:
            gameObject.transform.position = gameObject.transform.position + new Vector3(0f, 3f, 0f);
            currentTransform += 3;
            break;
            case 3:
            gameObject.transform.position = gameObject.transform.position + new Vector3(0f, 3f, 0f);
            currentTransform += 3;
            break;
            case 4:
            gameObject.transform.position = gameObject.transform.position + new Vector3(0f, 3f, 0f);
            currentTransform += 3;
            break;
            case 5:
            gameObject.transform.position = gameObject.transform.position + new Vector3(0f, 3f, 0f);
            currentTransform += 3;
            break;
            case 6:      
            break;
            case 7:
            gameObject.transform.position = gameObject.transform.position + new Vector3(0f, -3f, 0f);
            currentTransform -= 3;
            break;
            case 8:
            gameObject.transform.position = gameObject.transform.position + new Vector3(0f, -3f, 0f);
            currentTransform -= 3;
            break;
            case 9:
            gameObject.transform.position = gameObject.transform.position + new Vector3(0f, -3f, 0f);
            currentTransform -= 3;
            break;
            case 10:
            gameObject.transform.position = gameObject.transform.position + new Vector3(0f, -3f, 0f);
            currentTransform -= 3;
            break;
            case 11:
            gameObject.transform.position = gameObject.transform.position + new Vector3(0f, -3f, 0f);
            currentTransform -= 3;
            break;    
            case 12:
            gameObject.transform.position = gameObject.transform.position + new Vector3(0f, -3f, 0f);
            currentTransform -= 3;
            break;                                                                
            }
            animationFrame++;
    }
}
