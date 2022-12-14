using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
public class Description : MonoBehaviour
{
    // Start is called before the first frame update
    public Text description;
    void Start()
    {
        gameObject.SetActive(false);
    }

    public void show()
    {
        gameObject.SetActive(true);
    }

    public void hide()
    {
        gameObject.SetActive(false) ;
    }

    public void updateString(string newDes)
    {
        description.text = newDes;
    }
    // Update is called once per frame

    public void setPosition(Vector2 pos)
    {
        transform.localPosition = pos;
    }

}
