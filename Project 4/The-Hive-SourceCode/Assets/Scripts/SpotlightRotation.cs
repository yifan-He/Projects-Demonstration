// Reference: https://forum.unity.com/threads/rotate-flashlight-in-2d.401733/
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SpotlightRotation : MonoBehaviour
{
    public GameObject spotlight;
    float rayDist = 5;
    int layer = 1<<6;
    ArrayList freezed;
    GameObject currentObj;

    // Start is called before the first frame update
    void Start() {
        freezed = new ArrayList();
    }

    // Update is called once per frame
    void Update() {
    }

    private void LateUpdate () {
        // get the mouse position in world space
        Vector3 mousePos = Camera.main.ScreenToWorldPoint(Input.mousePosition);
        // change mouse Z position equal to this object's
        mousePos.z = transform.position.z;
 
        // get a rotation that points Z axis forward, and the Y axis towards the target
        Quaternion targetRotation = Quaternion.LookRotation(Vector3.forward, (mousePos - transform.position));
 
        // apply new rotation
        transform.rotation = targetRotation;

        GameObject[] Monsters = GameObject.FindGameObjectsWithTag("Monster");
        RaycastHit2D[] hit = Physics2D.RaycastAll(transform.position, new Vector2(transform.up.x, transform.up.y) * transform.localScale, rayDist, layer);

        if (hit.Length > 0)
        {
            for (int i = 0; i < hit.Length; i++)
            {
                if (hit[i].collider != null)
                {
                    //get freezed monster array
                    currentObj = hit[i].collider.gameObject;
                    // freezedMonster[i] = currentObj;
                    // freeze the monster
                    currentObj.GetComponent<Rigidbody2D>().bodyType = RigidbodyType2D.Static;
                    currentObj.GetComponent<MonsterMovement>().freeze = true;
                }

            }
        }
        else
        {// release monster
            for (int i= 0;i< Monsters.Length; i++)
            {
                Monsters[i].GetComponent<Rigidbody2D>().bodyType = RigidbodyType2D.Dynamic;
                Monsters[i].GetComponent<MonsterMovement>().freeze = false;
            }
        }
    }
}
