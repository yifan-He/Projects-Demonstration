using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DoorMusic : MonoBehaviour
{

    AudioSource au;
    Rigidbody2D rig;
    // Start is called before the first frame update
    void Start()
    {
        au = GetComponent<AudioSource>();
        rig = GetComponent<Rigidbody2D>();
    }



    private void OnCollisionEnter2D(Collision2D collision)
    {
        //Debug.Log(rig.constraints == RigidbodyConstraints2D.None);
        if ((collision.gameObject.tag == "Player" || collision.gameObject.tag == "Monster") && rig.constraints == RigidbodyConstraints2D.None)
            au.Play();
    }
}
