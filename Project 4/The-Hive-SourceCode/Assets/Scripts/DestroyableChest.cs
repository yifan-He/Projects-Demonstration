using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DestroyableChest : MonoBehaviour
{
    [SerializeField] private GameObject objectContained;
    [SerializeField]private GameObject explosionEffect;
    private GameObject player;

    // Start is called before the first frame update
    void Start()
    {
        player = GameObject.Find("Player");
    }

    // Update is called once per frame
    void Update()
    {
        float distance = Vector2.Distance(transform.position, player.transform.position);

        if(Input.GetMouseButtonDown(0) && distance < 1f){
            Destroy(Instantiate(explosionEffect, transform.position, Quaternion.identity), 3);
            Instantiate(objectContained, transform.position, Quaternion.identity).SetActive(true);
            Destroy(this.gameObject);
        }
    }
}
