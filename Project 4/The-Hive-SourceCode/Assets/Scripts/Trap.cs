using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Trap : MonoBehaviour
{
    // private float force = 10f;
    
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    private void OnCollisionEnter2D(Collision2D collision) {
        Vector2 forceDirection = new Vector2(transform.position.x-collision.transform.position.x, transform.position.y-collision.transform.position.y);

        if(collision.gameObject.tag == "Player"){
            collision.gameObject.GetComponent<PlayerMovement>().damage();
            // Debug.Log(forceDirection);
            // Debug.Log(collision.rigidbody.name);
            // collision.rigidbody.velocity = new Vector2(0, 0);
            // collision.rigidbody.AddForce(forceDirection * -force, ForceMode2D.Impulse);
        }
        else if(collision.gameObject.tag == "Monster"){
            collision.gameObject.GetComponent<MonsterMovement>().damage();
            Destroy(this.gameObject);
        }
        else if(collision.gameObject.tag == "Squirrel"){
            collision.gameObject.GetComponent<Monster3>().damage();
            Destroy(this.gameObject);
        }
    }
}
