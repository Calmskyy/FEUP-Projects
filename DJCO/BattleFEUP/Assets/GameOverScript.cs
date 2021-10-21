using System.Collections;
using System.Collections.Generic;
using UnityEngine.SceneManagement;
using UnityEngine;
using UnityEngine.UI;

public class GameOverScript : MonoBehaviour
{
    public CameraScript timer;
    public Text scoreDisplay;
    public Text enemiesDisplay;
    public Text timeBonusDisplay;
    public Text timerDisplay;

    public void gameOver(int score, bool victory)
    {
        gameObject.SetActive(true);
        float seconds = timer.secondsCount;
        int minutes = timer.minuteCount;
        int hours = timer.hourCount;
        int enemiesKilled = score / 10;
        float timerScore = 20000 - (seconds * 10) - (minutes * 600) - (hours * 36000);
        if (!victory)
            timerScore = timerScore / 20;
        scoreDisplay.text = "Score: " + (score + (int)timerScore);
        enemiesDisplay.text = "Enemies Defeated: " + enemiesKilled + " (+" + score + ")";
        timeBonusDisplay.text = "Time Bonus: " + (int)timerScore;
        timerDisplay.text = "Time Elapsed: " + hours +"H "+ minutes +"M "+(int)seconds + "S";
    }

    public void restartScene() {
        SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex);
    }
}
