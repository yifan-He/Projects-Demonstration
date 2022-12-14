using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class UIManager : MonoBehaviour
{
    // Start is called before the first frame update
    public GameObject backpack;
    private bool showBackPack;
    // AudioSource au;
    void Start()
    {
        backpack.SetActive(false);
        showBackPack = false;
        // au = GetComponent<AudioSource>();
    }

    // Update is called once per frame
    void Update()
    {
        if (!showBackPack)
        {
            if (Input.GetKeyDown(KeyCode.B))
            {
                Cursor.visible = true;
                // au.Play();
                backpack.SetActive(true);
                showBackPack = true;
                Time.timeScale = 0.0f;

            }
        }// if not showing backpack, show it, stop time
        else   
        {
            if (Input.GetKeyDown(KeyCode.B))
            {
                Cursor.visible = false;
                backpack.SetActive(false);
                showBackPack = false;
                Time.timeScale = 1.0f;
            }
        }// if showing backpack, hidde it,resume time
    }
}
