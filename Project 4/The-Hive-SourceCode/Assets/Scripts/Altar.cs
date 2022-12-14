using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Altar : MonoBehaviour
{
    [SerializeField]private Rigidbody2D rbDoor;
    [SerializeField]private GameObject player;
    [SerializeField]private BackpackManager pack;
    [SerializeField]private Transform frogContainer;
    [SerializeField]private GameObject explosionEffect;
    [SerializeField]private Transform center;
    [SerializeField]private GameObject hint1;
    [SerializeField]private GameObject hint2;

    private GameObject doorUnlockSound;
    private int count = 0;
    private bool open = false;

    // Start is called before the first frame update
    void Start()
    {
        doorUnlockSound = GameObject.Find("DoorUnlock");
        player = GameObject.Find("Player");
        if (player == null)
            Debug.Log("Didn't find player object");
    }

    // Update is called once per frame
    void Update()
    {
        float tempDis = Vector2.Distance(center.position, player.transform.position);
        if (Input.GetMouseButtonDown(0) && tempDis < 2)
        {
            for (int i = 0; i < 15; i++)
            {
                if (pack.getThisItem(i) != null && pack.getThisItem(i).name == "Frog")
                {
                    pack.DeleteThisItem(i);
                    frogContainer.GetChild(count).gameObject.SetActive(true);
                    count ++;
                    if(count == 10 && !open){
                        rbDoor.constraints = RigidbodyConstraints2D.None;
                        open = true;
                        Destroy(hint1);
                        Destroy(hint2);
                        doorUnlockSound.GetComponent<AudioSource>().Play();
                        for(int j = 0; j < count; j++){
                            Destroy(frogContainer.GetChild(j).gameObject);
                            Instantiate(explosionEffect, center.position, Quaternion.identity);
                        }
                    }
                }
            }
        }
    }
}
