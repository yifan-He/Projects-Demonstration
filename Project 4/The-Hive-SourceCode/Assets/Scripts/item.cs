using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
public class item : MonoBehaviour
{
    // Start is called before the first frame update
    private bool collidePlayer;
    // Update is called once per frame
    public BackpackManager backmanager;
    public itemCreate itemData;//each prafab have their own itemCreate 
    [SerializeField] Text fullMessage;
    private float showTime = 3.0f;
    private float showTimer;

    private void Start()
    {
        showTimer = showTime;
        backmanager = GameObject.Find("UI").transform.GetChild(4).gameObject.GetComponent<BackpackManager>();
    }


    void Update()
    {
        if(!backmanager.isFull()&&collidePlayer && Input.GetKeyDown(KeyCode.E))
        {
            Destroy(this.gameObject);
            backmanager.addItem(itemData);//add the item to the backpack
        }//if it is not full and player pick up
        if (backmanager.isFull() && Input.GetKeyDown(KeyCode.Space))
        {
            fullMessage.gameObject.SetActive(true);
            showTimer -= Time.deltaTime;
            if (showTimer < 0)
            {
                fullMessage.gameObject.SetActive(false);
                showTimer = showTime;
            }
        }//if it is full, player want to pick up will display the error message !!!!!!!!!!!not test yet!!!!!!!!!
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        Debug.Log(collision.name);
        if (collision.gameObject.tag == "Player")
            collidePlayer = true;
    }

    private void OnTriggerExit2D(Collider2D collision)
    {
        if (collision.gameObject.tag == "Player")
            collidePlayer = false;
    }

}
