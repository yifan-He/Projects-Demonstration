using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;

public class DialogSystem : MonoBehaviour
{
    public TextAsset textfile;
    public string [] textList;
    public GameObject dialogBox;
    public GameObject Button;
    public int index = 0;
    public TextMeshProUGUI dialogText;

    // Start is called before the first frame update
    void Start()
    {
        if (textfile != null) 
        {
            textList = (textfile.text.Split('\n'));
        }
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKeyDown(KeyCode.R) && Button.activeSelf)
        {   
            dialogBox.SetActive(true);
            if (Input.GetKeyDown(KeyCode.R) && index == textList.Length)
            {
                dialogBox.SetActive(false);
                index = 0;
                return;
            }
            if (Input.GetKeyDown(KeyCode.R))
            {
              
                dialogText.text = textList[index];
                index++;
            }
        }
    }
    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (collision.tag == "Player")
        {
            Button.SetActive(true);
        }
    }
    private void OnTriggerExit2D(Collider2D collision)
    {
        if (collision.tag == "Player")
        {
            Button.SetActive(false);
            dialogBox.SetActive(false);
            index = 0;
        }
    }
}
