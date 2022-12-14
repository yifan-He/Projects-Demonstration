using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MonsterMovement : MonoBehaviour
{
    public bool freeze;
    [SerializeField]private float chaseDistance = 15f;
    [SerializeField]private GameObject explosionEffect;
    [SerializeField]private GameObject key;
    [SerializeField]public int health = 20;

    private Transform target;
    private Animator animator;
    private AudioSource sound;
    private float inputX, inputY;
    private float lookDirX, lookDirY;
    private Vector3 lastPos;
    private Vector3 originalPos;

    // Start is called before the first frame update
    void Start()
    {
        animator = GetComponent<Animator>();
        target = GameObject.FindGameObjectWithTag("Player").GetComponent<Transform>();
        sound = GetComponent<AudioSource>();
        originalPos = transform.position;
        lastPos = transform.position;
        freeze = false;
    }

    // Update is called once per frame
    private void Update()
    {
        if(Vector2.Distance(target.transform.position, transform.position) < chaseDistance){
            gameObject.GetComponent<Pathfinding.AIDestinationSetter>().target = target;
            if(!freeze){
                gameObject.GetComponent<Pathfinding.AIDestinationSetter>().enabled = true;
                if(!sound.isPlaying){
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
            }
            else{
                gameObject.GetComponent<Pathfinding.AIDestinationSetter>().enabled = false;
                animator.SetBool("isMoving", false);
                if(!target.GetComponent<PlayerMovement>().ison){
                    freeze = false;
                    GetComponent<Rigidbody2D>().bodyType = RigidbodyType2D.Dynamic;
                }
            }
        }else{
            gameObject.GetComponent<Pathfinding.AIDestinationSetter>().target = transform.parent.GetChild(1);
            gameObject.GetComponent<Pathfinding.AIDestinationSetter>().enabled = true;
            sound.Stop();

            inputX = originalPos.x;
            inputY = originalPos.y;
            lookDirX = transform.position.x - lastPos.x;
            lookDirY = transform.position.y - lastPos.y;

            if (new Vector2(inputX, inputY).normalized != Vector2.zero)
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

        if(health < 1 && transform.parent.tag =="KeyMonster") {
            Destroy(Instantiate(explosionEffect, transform.position, Quaternion.identity), 3);
            Instantiate(key, transform.position, Quaternion.identity).SetActive(true);
            Destroy(this.gameObject);
        }
    }

    public void damage(){
        health --;
    }
}
