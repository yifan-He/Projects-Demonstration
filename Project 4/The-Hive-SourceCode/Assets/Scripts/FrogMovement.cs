using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FrogMovement : MonoBehaviour
{
    private Transform target;
    private  Animator animator;
    private float inputX, inputY;
    private float lookDirX, lookDirY;
    private Vector2 movement;
    private float speed = 1f;
    private float fleeDistance = 6f;
    private bool turned;
    private float waitTime;

    // Start is called before the first frame update
    void Start()
    {
        animator = GetComponent<Animator>();
        target = GameObject.FindGameObjectWithTag("Player").GetComponent<Transform>();

        float randomX = Random.Range(-1, 1);
        float randomY = Random.Range(-1, 1);
        animator.SetFloat("inputX", randomX);
        animator.SetFloat("inputY", randomY);
    } 

    // Update is called once per frame
    private void Update()
    {
        if(Vector2.Distance(target.transform.position, transform.position) < fleeDistance){
            inputX = target.position.x;
            // Debug.Log(target.position.x);
            inputY = target.position.y;

            lookDirX = target.position.x - transform.position.x;
            lookDirY = target.position.y - transform.position.y;

            // Debug.Log(target.position.y);
            movement = new Vector2(inputX, inputY).normalized;
            //Debug.Log(movement);

            transform.position = Vector2.MoveTowards(transform.position, target.position, -speed * Time.deltaTime);

            if (movement != Vector2.zero)
            {
                animator.SetBool("isMoving", true);
            }
            else
            {
                animator.SetBool("isMoving", false);//
            }

            animator.SetFloat("inputX", -lookDirX);
            animator.SetFloat("inputY", -lookDirY);
        }
        else
        {
            animator.SetBool("isMoving", false);
            
            if(waitTime <= 0){
                float randomX = Random.Range(-1, 1);
                float randomY = Random.Range(-1, 1);
                animator.SetFloat("inputX", randomX);
                animator.SetFloat("inputY", randomY);
                waitTime = Random.Range(0, 10);
            }
            else{
                waitTime -= Time.deltaTime;
            }
            
        }
    }
}
