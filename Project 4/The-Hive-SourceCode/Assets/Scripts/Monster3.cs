using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Monster3 : MonoBehaviour
{

    [SerializeField] private float chaseDistance = 10f;
    //[SerializeField] private AudioSource sound;
    [SerializeField] private int health = 2;
    [SerializeField]private GameObject explosionEffect;

    private Transform target;
    private Animator animator;
    private AudioSource sound;

    private float inputX, inputY;
    private float lookDirX, lookDirY;
    private Vector3 lastPos;
    private Vector3 originalPos;
    
    public GameObject bullet;
    private float shootTimer;
    private float shootTime = 0.75f;
    // Start is called before the first frame update
    void Start()
    {
        animator = GetComponent<Animator>();
        target = GameObject.FindGameObjectWithTag("Player").GetComponent<Transform>();
        sound = GetComponent<AudioSource>();
        originalPos = transform.position;
        lastPos = transform.position;
        shootTimer = shootTime;
    }

    // Update is called once per frame
    private void Update()
    {
        if (Vector2.Distance(target.transform.position, transform.position) < chaseDistance)
        {
            gameObject.GetComponent<Pathfinding.AIDestinationSetter>().target = target;

            gameObject.GetComponent<Pathfinding.AIDestinationSetter>().enabled = true;
            if (!sound.isPlaying)
            {
                sound.Play();
            }

            inputX = target.position.x;
            inputY = target.position.y;
            lookDirX = transform.position.x - lastPos.x;
            lookDirY = transform.position.y - lastPos.y;

            if (Vector2.Distance(lastPos, transform.position) > 0)
            {
                animator.SetBool("isMoving", true);
            }
            else
            {
                animator.SetBool("isMoving", false);
            }

            animator.SetFloat("inputX", lookDirX);
            animator.SetFloat("inputY", lookDirY);

            shootTimer -= Time.deltaTime;
            if (shootTimer < 0)
            {
                shoot();
                shootTimer = shootTime;
            }

    }
        else
        {
            gameObject.GetComponent<Pathfinding.AIDestinationSetter>().target = transform.parent.GetChild(1);
            gameObject.GetComponent<Pathfinding.AIDestinationSetter>().enabled = true;
            sound.Stop();

            inputX = originalPos.x;
            inputY = originalPos.y;
            lookDirX = transform.position.x - lastPos.x;
            lookDirY = transform.position.y - lastPos.y;

            if (Vector2.Distance(lastPos, transform.position) > 0)
            {
                animator.SetBool("isMoving", true);
            }
            else
            {
                animator.SetBool("isMoving", false);
            }

            animator.SetFloat("inputX", lookDirX);
            animator.SetFloat("inputY", lookDirY);
        
    }

        lastPos = transform.position;

        if(health < 1 && transform.parent.tag == "Squirrel") {
            Destroy(Instantiate(explosionEffect, transform.position, Quaternion.identity), 3);
            Destroy(this.gameObject);
        }
    }

    public void damage()
    {
        health--;
    }

    public void shoot()
    {
        Instantiate(bullet, transform.position, Quaternion.identity);
    }
}
