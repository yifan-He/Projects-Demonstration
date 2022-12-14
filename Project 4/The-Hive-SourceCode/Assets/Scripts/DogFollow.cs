using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DogFollow : MonoBehaviour
{
    [SerializeField]private GameObject Player;
    [SerializeField]private float dogSpeed;
    [SerializeField]private Animator animator;
    [SerializeField]private GameObject key;

    public bool isBoosted;
    public GameObject Boss;
    public bool isFollowing = false;

    private BackpackManager pack;

    // Start is called before the first frame update
    void Start()
    {
        Player = GameObject.Find("Player");
        dogSpeed = 0f;
        animator = gameObject.GetComponent<Animator>();
        isBoosted = false;
        Boss = GameObject.Find("Boss");
        pack = GameObject.Find("BackpackManager").GetComponent<BackpackManager>();
    }

    // Update is called once per frame
    void Update()
    {
        if(isFollowing){
            float tempDis = Vector2.Distance(transform.position, Player.transform.position);
            transform.GetChild(1).gameObject.SetActive(false);
            transform.GetChild(2).gameObject.SetActive(true);

            if (!isBoosted)
            {
                if (tempDis > 2)
                {
                    dogSpeed = 5f;
                    animator.SetFloat("Speed", dogSpeed);
                    transform.position = Vector2.MoveTowards(transform.position, Player.transform.position, dogSpeed * Time.deltaTime);
                    animator.SetFloat("Horizontal", Player.transform.position.x - transform.position.x);
                    //Debug.Log(Player.transform.position.x - transform.position.x);
                    animator.SetFloat("Vertical", Player.transform.position.y - transform.position.y);
                }
                else
                {
                    dogSpeed = 0f;
                    animator.SetFloat("Speed", dogSpeed);
                }
            }

            else
            {
                
                float monsterDis = Vector2.Distance(transform.position, Boss.transform.position);
                transform.localScale = new Vector3(2, 2);
                dogSpeed = 4f;
                if (monsterDis >= 1)
                {
                    animator.SetFloat("Speed", dogSpeed);
                    transform.position = Vector2.MoveTowards(transform.position, Boss.transform.position, dogSpeed * Time.deltaTime);
                    animator.SetFloat("Horizontal", Boss.transform.position.x - transform.position.x);
                    
                    animator.SetFloat("Vertical", Boss.transform.position.y - transform.position.y);
                }
            }
        }
        else{
            if(Input.GetKeyDown(KeyCode.Q) || Input.GetMouseButtonDown(0)){
                for (int i = 0; i < 15; i++)
                {
                    if (pack.getThisItem(i) != null && pack.getThisItem(i).name == "Food")
                    {
                        pack.DeleteThisItem(i);
                        isFollowing = true;
                        GameObject newKey = Instantiate(key, transform.position, Quaternion.identity);
                        newKey.SetActive(true);
                    }
                }
            }
        }
    }

    public void OnTriggerEnter2D(Collider2D collision)
    {
        if (isBoosted)
        {
            if (collision.name == "Boss")
            {
                Boss.GetComponent<Pathfinding.AIPath>().maxSpeed = 1.5f;
                Destroy(gameObject, 8f);
            }
        }

    }
}
