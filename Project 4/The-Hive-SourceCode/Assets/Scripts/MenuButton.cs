using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.EventSystems;
public class MenuButton : MonoBehaviour, IPointerEnterHandler
{
    [SerializeField] MenuButtonController menuC;
    [SerializeField] Animator ani;
    [SerializeField] int thisIndex;
    [SerializeField] string changeScene;
    private float delayTime = 1.2f;
    private float delayTimer;
    public AudioSource press;
    public AudioSource audio;
    private bool pressed;
    void Start()
    {
        delayTimer = delayTime;
    }    
    
    
    public void OnPointerEnter(PointerEventData pointerEventData)
    {
        menuC.index = thisIndex;
    }


    // Update is called once per frame
    void FixedUpdate()
    {   
        if(menuC.index == thisIndex)
        {
            //AudioManager.instance.AudioPlay(audio);
            audio.Play();
            ani.SetBool("selected", true);
            if (Input.GetAxis("Submit") == 1|| Input.GetMouseButton(0))
            {
                press.Play();
                ani.SetBool("pressed", true);
                if (changeScene == "Quit")
                {
                    Application.Quit();
                }
                else
                {
                    pressed = true;
/*                  delayTimer -= Time.fixedDeltaTime*5;
                    Debug.Log(delayTimer);
                    if (delayTimer <= 0)
                    {
                        SceneManager.LoadScene(changeScene);
                        delayTimer = delayTime;
                    }*/
                }
                
            }
            else if (ani.GetBool("pressed"))
            {
                ani.SetBool("pressed", false);
            }
            if (pressed)
            {
                delayTimer -= Time.fixedDeltaTime ;
                //Debug.Log(delayTimer);
                if (delayTimer <= 0)
                {
                    pressed = false;
                    delayTimer = delayTime;
                    SceneManager.LoadScene(changeScene); 
                }
            }
        }
        else
            ani.SetBool("selected", false);
        
    }



}
