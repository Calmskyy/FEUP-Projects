using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

static class Weapons
{
    public const int Pistol = 1;
    public const int Rifle = 2;
    public const int Minigun = 3;
}

public class PlayerMovement : MonoBehaviour
{
    public static float defaultSpeed = 5f;
    public float moveSpeed = defaultSpeed;
    public Animator animator;
    public SpriteRenderer SpriteRenderer;
    public Camera cam;
    public Text coinsDisplay;
    public Text heartsDisplay;
    public Text scoreDisplay;
    public GameObject deathEffect;
    float h;
    float v;
    public int health = 100;
    public int coins;
    public int lifes;
    public int score;
    bool movement=true;
    public bool shooting=true;
    public bool waitingRespawn = false;
    bool dead=false;
    public Rigidbody2D rb;
    Vector2 mousePos;

    public int pistolAmmo = 12;
    public int rifleAmmo = 30;
    public float minigunTime = 15;
    public int totalRifleAmmo = 45;
    public float pistolFireRate = 0.25f;
    public float rifleFireRate = 0.1667f;
    public float minigunFireRate = 0.05f;
    private float lastBulletTime = 0f;
    public int currentWeapon = Weapons.Pistol;
    public Text firstWeaponDisplay;
    public Image firstWeaponIcon;
    public Image minigunIcon;
    public Text firstWeaponKey;
    public Image firstWeaponKeyIcon;
    public Text secondWeaponDisplay;
    public Image secondWeaponIcon;
    public Text secondWeaponKey;
    public Image secondWeaponKeyIcon;
    public Transform firePoint;
    public GameObject bulletPre;
    public UI_Icons coinUI;
    public UI_Icons soldierUI;
    public GameOverScript gameOver;
    public GameObject enemies;

    public float bulletForce = 20f;

    public bool hasCoins(int check){
        if(check<=coins){
            return true;
        }
        return false;
    }

    public bool isInjured(){
        if (health == 100)
            return false;
        else 
            return true;
    }

    public void incrementScore(int ammount){
        score = score + ammount;
        scoreDisplay.text = "Score: " + score.ToString();
    }

    public void incrementCoin(){
        coins = coins + 1;
        coinsDisplay.text = "x" + coins.ToString();
        coinUI.makeAnimation();
    }

    public void decrementCoin(int ammount){
        coins = coins - ammount;
        coinsDisplay.text = "x" + coins.ToString();
    }

    public void incrementLife(){
        lifes = lifes + 1;
        heartsDisplay.text = "x" + lifes.ToString();
        soldierUI.makeAnimation();
    }
    public void decrementLife(){
        lifes = lifes - 1;

        if(lifes<0) {
            dead = true;
            gameOver.gameOver(score, false);
        }
        else
        {
            health=100;
            heartsDisplay.text = "x" + lifes.ToString();
        }
    }

    public void takeDamage(int damage){
        health -= damage;

        if(health<=0){
            decrementLife();
        StartCoroutine(Die());
        }
    }

    IEnumerator Die(){
        GameObject effect = Instantiate(deathEffect,transform.position, Quaternion.identity);

        GetComponent<Renderer>().enabled = false;
        GetComponent<CircleCollider2D>().enabled = false;
        movement = false;
        shooting = false;
        waitingRespawn = true;
        rb.velocity = new Vector2(0, 0);

        Destroy(effect,1f);
        
        if(!dead){
        
        yield return new WaitForSeconds(3f);

        transform.SetPositionAndRotation( new Vector3(-795f,-20f,-1f),Quaternion.identity);
        GetComponent<Renderer>().enabled = true;
        GetComponent<CircleCollider2D>().enabled = true;
        movement = true;
        shooting = true;
        waitingRespawn = false;
        }

    }

    // Start is called before the first frame update
    void Start()
    {
        SpriteRenderer = GetComponent<SpriteRenderer>();
    }

    public void slowDown(){
        moveSpeed = defaultSpeed/4f;
    }

    public void normalizeSpeed(){
        moveSpeed = defaultSpeed;
    }

    // Update is called once per frame
    void Update()
    {
        if (enemies.transform.childCount == 0) {
            gameOver.gameOver(score, true);
            movement = false;
            shooting = false;
            rb.velocity = new Vector2(0, 0);
        }
        if(movement){
        movementaux();
        }
        if(shooting){
        shootaux();
        }
    }
    
    void shootaux(){
        if (lastBulletTime > 0)
            lastBulletTime -= Time.deltaTime;
        if (currentWeapon == Weapons.Minigun)
        {
            firstWeaponDisplay.enabled = true;
            firstWeaponIcon.enabled = false;
            minigunIcon.enabled = true;
            secondWeaponDisplay.enabled = false;
            secondWeaponIcon.enabled = false;
            firstWeaponKey.enabled = false;
            firstWeaponKeyIcon.enabled = false;
            secondWeaponKey.enabled = false;
            secondWeaponKeyIcon.enabled = false;
            firstWeaponDisplay.text = minigunTime.ToString("F1");
            if (Input.GetMouseButton(0) && lastBulletTime <= 0 && minigunTime > 0)
            {
                ShootMinigun();
                lastBulletTime = minigunFireRate;
            }
            else if (minigunTime <= 0)
            {
                SwapToPistol();
            }
            minigunTime -= Time.deltaTime;
            return;
        }
        else
        {
            firstWeaponDisplay.enabled = true;
            secondWeaponDisplay.enabled = true;
            firstWeaponIcon.enabled = true;
            minigunIcon.enabled = false;
            secondWeaponIcon.enabled = true;
            firstWeaponKey.enabled = true;
            firstWeaponKeyIcon.enabled = true;
            secondWeaponKey.enabled = true;
            secondWeaponKeyIcon.enabled = true;
            firstWeaponDisplay.text = pistolAmmo.ToString() + " / " + "12";
            secondWeaponDisplay.text = rifleAmmo.ToString() + " / " + totalRifleAmmo;
            if (totalRifleAmmo < 10)
                secondWeaponDisplay.text = secondWeaponDisplay.text + " ";
        }
        if (Input.GetKeyDown(KeyCode.Alpha1))
        {
            SwapToPistol();
        }
        if (Input.GetKeyDown(KeyCode.Alpha2))
        {
            SwapToRifle();
        }
        if (Input.GetKeyDown(KeyCode.R))
        {
            Reload();
        }
        if (currentWeapon == Weapons.Rifle && Input.GetMouseButton(0) && lastBulletTime <= 0 && rifleAmmo > 0) {
            ShootRifle();
            lastBulletTime = rifleFireRate;
        }
        if (currentWeapon == Weapons.Pistol && Input.GetMouseButtonDown(0) && lastBulletTime <= 0 && pistolAmmo > 0)
        {
            ShootPistol();
            lastBulletTime = pistolFireRate;
        }
    }

public Vector3 GetWorldPositionOnPlane(Vector3 screenPosition, float z) {
     Ray ray = Camera.main.ScreenPointToRay(screenPosition);
     Plane xy = new Plane(Vector3.forward, new Vector3(0, 0, z));
     float distance;
     xy.Raycast(ray, out distance);
     return ray.GetPoint(distance);
 }


    void movementaux(){
        h=Input.GetAxis("Horizontal");
        v=Input.GetAxis("Vertical");
        animator.SetFloat("Vertical", v);
        animator.SetFloat("Horizontal", h);
        rb.velocity = new Vector2(h*moveSpeed, v*moveSpeed);
        //mousePos = cam.ScreenToWorldPoint(Input.mousePosition);
        mousePos = GetWorldPositionOnPlane(Input.mousePosition,0);
        Vector3 aux = new Vector3(mousePos.x,mousePos.y,0f);
        Vector3 lookDir = aux - transform.position;
        float angle = Mathf.Atan2(lookDir.y, lookDir.x) * Mathf.Rad2Deg - 90f;
        rb.rotation = angle;
        
}


    public void giveAmmo(int ammount){
        totalRifleAmmo = totalRifleAmmo + ammount;
        secondWeaponDisplay.text =rifleAmmo.ToString()+ " / " + totalRifleAmmo.ToString();

    }

    void ShootRifle()
    {
        GameObject bullet = Instantiate(bulletPre, firePoint.position, firePoint.rotation);
        Rigidbody2D rb = bullet.GetComponent<Rigidbody2D>();
        rb.AddForce(firePoint.up * bulletForce, ForceMode2D.Impulse);
        rifleAmmo--;
    }

    void ShootPistol()
    {
        GameObject bullet = Instantiate(bulletPre, firePoint.position, firePoint.rotation);
        Rigidbody2D rb = bullet.GetComponent<Rigidbody2D>();
        rb.AddForce(firePoint.up * bulletForce, ForceMode2D.Impulse);
        pistolAmmo--;
    }

    void ShootMinigun()
    {
        var rotate = Random.value;
        rotate -= 0.5f;
        firePoint.Rotate(0.0f, 0.0f, rotate * 20, Space.Self);
        GameObject bullet = Instantiate(bulletPre, firePoint.position, firePoint.rotation);
        Rigidbody2D rb = bullet.GetComponent<Rigidbody2D>();
        rb.AddForce(firePoint.up * bulletForce, ForceMode2D.Impulse);
        firePoint.Rotate(0.0f, 0.0f, - rotate * 20, Space.Self);
    }

    void Reload()
    {
        if (currentWeapon == Weapons.Pistol)
        {
            pistolAmmo = 12;
        }
        else if (currentWeapon == Weapons.Rifle)
        {
            for (int i = 0; i < 30; i++)
            {
                if (rifleAmmo < 30 && totalRifleAmmo > 0)
                {
                    rifleAmmo++;
                    totalRifleAmmo--;
                }
                else
                    break;
            }
        }
    }

    void SwapToPistol()
    {
        currentWeapon = Weapons.Pistol;
        firstWeaponDisplay.GetComponent<Outline>().effectColor = new Color(0.566f, 0.507f, 0.093f, 0.500f);
        firstWeaponIcon.GetComponent<Outline>().effectColor = new Color(0.566f, 0.507f, 0.093f, 0.500f);
        secondWeaponDisplay.GetComponent<Outline>().effectColor = new Color(0f, 0f, 0f, 0.500f);
        secondWeaponIcon.GetComponent<Outline>().effectColor = new Color(0f, 0f, 0f, 0.500f);
    }

    void SwapToRifle()
    {
        currentWeapon = Weapons.Rifle;
        secondWeaponDisplay.GetComponent<Outline>().effectColor = new Color(0.566f, 0.507f, 0.093f, 0.500f);
        secondWeaponIcon.GetComponent<Outline>().effectColor = new Color(0.566f, 0.507f, 0.093f, 0.500f);
        firstWeaponDisplay.GetComponent<Outline>().effectColor = new Color(0f, 0f, 0f, 0.500f);
        firstWeaponIcon.GetComponent<Outline>().effectColor = new Color(0f, 0f, 0f, 0.500f);
    }

}
