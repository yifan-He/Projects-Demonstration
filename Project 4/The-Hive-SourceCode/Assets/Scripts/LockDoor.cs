using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LockDoor : MonoBehaviour
{
    [SerializeField]private GameObject player;
    [SerializeField]private BackpackManager pack;
    [SerializeField]private GameObject hint;

    private GameObject doorUnlockSound;
    private Rigidbody2D myRig;

    // Start is called before the first frame update
    void Start()
    {
        doorUnlockSound = GameObject.Find("DoorUnlock");
        myRig = GetComponent<Rigidbody2D>();
        player = GameObject.Find("Player");
        if (player == null)
            Debug.Log("Didn't find player object");
    }

    // Update is called once per frame
    void Update()
    {
        float tempDis = Vector2.Distance(transform.position, player.transform.position);
        if (tempDis < 2)
        {
            for (int i = 0; i < 15; i++)
            {
                if (pack.getThisItem(i) != null)
                {
                    if (pack.getThisItem(i).name == "Key")
                    {
                        myRig.constraints = RigidbodyConstraints2D.None;
                        pack.DeleteThisItem(i);
                        Destroy(hint);
                        doorUnlockSound.GetComponent<AudioSource>().Play();
                    }
                }
            }
        }
    }
}
