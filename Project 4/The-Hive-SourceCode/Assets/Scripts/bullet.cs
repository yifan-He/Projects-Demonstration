using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class bullet : MonoBehaviour
{
    [SerializeField] private float speed = 3f;
    Rigidbody2D rb;
    private Transform target;
    public static bool triggerPlayer;
    // Start is called before the first frame update
    void Start()
    {
        target = GameObject.FindGameObjectWithTag("Player").GetComponent<Transform>();
        rb = GetComponent<Rigidbody2D>();
        rb.velocity = (target.position - transform.position) * speed;
    }



    private void OnTriggerEnter2D(Collider2D collision)
    {
        /*if(collision.gameObject.tag == "Player"|| collision.gameObject.tag == "Map")*/
        //{
        if(collision.gameObject.tag != "Squirrel")
        {
            if (collision.gameObject.tag == "Player")
                triggerPlayer = true;
            Destroy(gameObject);
        }
            
        //}
       
    }
}
