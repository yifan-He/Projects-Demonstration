using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DoorMark : MonoBehaviour
{
    [SerializeField] private GameObject mark;

    private BackpackManager pack;
    private bool collided;

    // Start is called before the first frame update
    void Start()
    {
        pack = GameObject.Find("BackpackManager").GetComponent<BackpackManager>();
    }

    // Update is called once per frame
    void Update()
    {
        if (collided && (Input.GetMouseButtonDown(0) || Input.GetKeyDown(KeyCode.Q))){
            Debug.Log("1");
            for (int i = 0; i < 15; i++)
            {
                if (pack.getThisItem(i) != null && pack.getThisItem(i).name == "HighLighter")
                {
                    // Debug.Log("mark");
                    if(mark.activeSelf){
                        mark.SetActive(false);
                    }else{
                        mark.SetActive(true);
                    }
                }
            }
        }
    }

    private void OnCollisionEnter2D(Collision2D collision)
    {
        if (collision.gameObject.tag == "Player"){
            // Debug.Log("collision");
            collided = true;
        }
    }

    private void OnCollisionExit2D(Collision2D collision){
        if (collision.gameObject.tag == "Player"){
            // Debug.Log("exit");
            collided = false;
        }
    }
}
