using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LockDoorOnSave : MonoBehaviour
{
    [SerializeField] private SwapPoint savePoint;

    private float timer = 5f;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        if(PlayerMovement.currentPointNumber == savePoint.swapNumber){
            if(timer > 0){
                timer -= Time.deltaTime;
            }else{
                this.GetComponent<Rigidbody2D>().constraints = RigidbodyConstraints2D.FreezeAll;
            }
        }
    }
}
