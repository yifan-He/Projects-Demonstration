using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
public class PlayerMovement : MonoBehaviour
{
    [SerializeField] private GameObject dog;
    public float speed = 5f;
    public Rigidbody2D player;
    public Animator animator;
    Vector2 playerMovement;
    Vector2 mousePos;
    public Camera camera;
    
    public int maxHealth = 30;
    public int currentHealth;

    public float maxEnergy = 30.0f;
    public float currentEnergy;

    public float maxVolumn = 100.0f;
    public float currentVolumn;

    public HealthBar healthBar;
    public EnergyBar energyBar;
    public flashlightBar flashlight;
    private bool stayWithMonster;
    private float healthTime = 2.0f;
    private float healthTimer;
    private Vector3 lastPos;
    public float originalSpeed = 5f;

    public static int count;

    public bool ison = true;

    public BackpackManager backpack;
    public List<itemCreate> Allitem = new List<itemCreate>();//all items (new one need to add it to the list in unity)

    public static bool pointCheck;
    public static int currentPointNumber;

    public GameObject swap1;
    public GameObject swap2;
    public GameObject swap3;
    public GameObject swap4;

    private void Awake()
    {
        Cursor.visible = false;


    }

    private void Start()
    {
        currentHealth = maxHealth;
        healthBar.SetMaxHealth(maxHealth);
        healthTimer = healthTime;
        
        currentEnergy = maxEnergy;
        energyBar.SetMaxEnergy(maxEnergy);
 
        
        currentVolumn = maxVolumn;
        flashlight.SetMaxVolumn(maxVolumn);

        lastPos = transform.position;

        if (count != 0)
        {
            Debug.Log(currentPointNumber);
            LoadPlayer();
            if(currentPointNumber == 1)
            {
                transform.position = swap1.transform.position;
            }
            else if (currentPointNumber == 2)
            {
                transform.position = swap2.transform.position;
            }
            else if (currentPointNumber == 3)
            {
                transform.position = swap3.transform.position;
                GameObject newDog = Instantiate(dog, swap3.transform.position, Quaternion.identity);
                newDog.SetActive(true);
                newDog.GetComponent<DogFollow>().isFollowing = true;
            
            }
            else if (currentPointNumber == 4)
            {
                transform.position = swap4.transform.position;
                GameObject newDog = Instantiate(dog, swap3.transform.position, Quaternion.identity);
                newDog.SetActive(true);
                newDog.GetComponent<DogFollow>().isFollowing = true;
                
            }
        }

    }
    void Update()
    {
        playerMovement.x = Input.GetAxisRaw("Horizontal");
        playerMovement.y = Input.GetAxisRaw("Vertical");

        mousePos = camera.ScreenToWorldPoint(Input.mousePosition);

        animator.SetFloat("Horizontal", mousePos.x - player.transform.position.x);
        animator.SetFloat("Vertical", mousePos.y - player.transform.position.y);
        animator.SetFloat("Speed", playerMovement.sqrMagnitude);


        if(lastPos != transform.position)
        {
            currentEnergy -= 0.35f * Time.deltaTime;
            energyBar.SetEnergy(currentEnergy);
            lastPos = transform.position;

            if(!transform.GetComponent<AudioSource>().isPlaying){
                transform.GetComponent<AudioSource>().Play();
            }
        }//if player is move reduce the energy
        else{
            transform.GetComponent<AudioSource>().Stop();
        }
        


        if (DeletButton.eat)
        {
            currentEnergy += 20.0f;
            energyBar.SetEnergy(currentEnergy);
            DeletButton.eat = false;
        }//eatting food, gain energy;

        if (DeletButton.charge)
        {
            currentVolumn = maxVolumn;
            flashlight.SetVolumn(currentVolumn);
            DeletButton.charge = false;
        }//change battery, full vplumn

        if (stayWithMonster)
        {
            healthTimer -= Time.deltaTime;
            if (healthTimer < 0)
            {
                currentHealth -= 1;
                healthBar.SetHealth(currentHealth);
                healthTimer = healthTime;
            }
        }//for every 2 second if it stay with monster, it health --

        if(ison && Input.GetMouseButtonDown(1))
        {
            ison = false;
            transform.GetChild(0).gameObject.SetActive(false);
        }
        else if(ison==false && Input.GetMouseButtonDown(1) && currentVolumn > 0)
        {
            ison = true;
            transform.GetChild(0).gameObject.SetActive(true);
        }
        //if flashlight is on
        if(ison == true)
        {
            currentVolumn -= 1f * Time.deltaTime;
            flashlight.SetVolumn(currentVolumn);
        }
        if(currentVolumn <= 0)
        {
            ison = false;
            transform.GetChild(0).gameObject.SetActive(false);
        }

        //test for load and save
        // if (Input.GetKeyDown(KeyCode.E))
        // {
        //     SavePlayer();
        // }
        // if (Input.GetKeyDown(KeyCode.R))
        // {
        //     LoadPlayer();
        // }

        if (bullet.triggerPlayer)
        {
            currentHealth--;
            healthBar.SetHealth(currentHealth);
            bullet.triggerPlayer = false;
        }

        if (pointCheck)
        {
            SavePlayer();
            pointCheck = false;
        }//if in the checkpoint zone, save the player.

        if (currentHealth <= 0)
        {
            SceneManager.LoadScene(3);
            count = 1;
        }

        if(currentEnergy <= 0){
            speed = 0.5f * originalSpeed;
        }
        else{
            speed = originalSpeed;
        }
    }

    void FixedUpdate()
    {
        player.MovePosition(player.position + playerMovement * speed * Time.fixedDeltaTime);
    }

    private void OnCollisionEnter2D(Collision2D collision)
    {
        if (collision.gameObject.tag == "Monster")
        {
            damage();
        }
    }

    private void OnCollisionStay2D(Collision2D collision)
    {
        if (collision.gameObject.tag == "Monster")
            stayWithMonster = true;
    }

    private void OnCollisionExit2D(Collision2D collision)
    {
        if (collision.gameObject.tag == "Monster")
            stayWithMonster = false;
    }

    public void SavePlayer()
    {
        SaveSystem.SavePlayer(this,backpack);
    }

    public void LoadPlayer()
    {
        PlayerData data = SaveSystem.LoadPlayer();

        currentHealth = data.health;
        healthBar.SetHealth(currentHealth);

        currentEnergy = data.energy;
        energyBar.SetEnergy(currentEnergy);

        currentVolumn = data.volumn;
        flashlight.SetVolumn(currentVolumn);

        backpack.resetSlots();

        for (int i = 0; i < data.itemName.Length; i++)
        {
            itemCreate temp = null;
            for (int k = 0; k < Allitem.Count; k++)
            {
                if (data.itemName[i] == Allitem[k].name)
                {
                    temp = Allitem[k];
                }
            }//find the type of item

           
            for (int j = 0; j < data.itemNumber[i]; j++)
            {
                backpack.addItem(temp);
            }
        }
    }

    public void damage(){
        currentHealth -= 1;
        healthBar.SetHealth(currentHealth);
    }

    public void OnTriggerEnter2D(Collider2D collision)
    {
        if (collision.gameObject.tag == "swappoint")
        {
            currentPointNumber = collision.gameObject.GetComponent<SwapPoint>().swapNumber;
            pointCheck = true;
        }
           
    }

}
