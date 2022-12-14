using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;

public class DeletButton : MonoBehaviour, IPointerEnterHandler,IPointerExitHandler
{
    [SerializeField] int buttonID;
    public BackpackManager backmanager;
    // Start is called before the first frame update
    public Description description;
    private Vector2 position;
    public static bool eat;
    public static bool charge;
    public static bool read;
    private bool inzone;
        public GameObject password;
    public GameObject dog;

    public void delete()
    {
        backmanager.DeleteThisItem(buttonID);
        if (backmanager.getThisItem(buttonID) != null)
        {
            description.show();
            description.updateString("<color=red>Name: </color>" + "<color=yellow>" + backmanager.getThisItem(buttonID).itemName + "</color>\n" + "Description: " + "<color=grey>" + backmanager.getThisItem(buttonID).itemDes + "</color>\n");

            RectTransformUtility.ScreenPointToLocalPointInRectangle(GameObject.Find("UI").transform as RectTransform, Input.mousePosition, null, out position);
            description.setPosition(position);
        }
        else
        {
            description.hide();
            description.updateString("");
        }
    }

    public void Update()
    {
        if (Input.GetKeyDown(KeyCode.Q) && inzone)
        {
            if (backmanager.getThisItem(buttonID).itemName == "Food")
            {
                eat = true;
                //backmanager.DeleteThisItem(buttonID);
                delete();
            }
            else if (backmanager.getThisItem(buttonID).itemName == "Battery")
            {
                charge = true;
                //backmanager.DeleteThisItem(buttonID);
                delete();
            }
            else if (backmanager.getThisItem(buttonID).itemName == "Paper")
            {
                read = true;
            }

            else if (backmanager.getThisItem(buttonID).itemName == "Treasure")
            {
                NumberChange p = password.GetComponent<NumberChange>();
                p.canvas.SetActive(true);
            }
            else if (backmanager.getThisItem(buttonID).itemName == "Capsule")
            {
                DogFollow df = dog.GetComponent<DogFollow>();
                df.isBoosted = true;
                delete();
            }

        }

    }

    public void OnPointerEnter(PointerEventData eventData)
    {
        if (backmanager.getThisItem(buttonID) != null)
        {
            description.show();
            description.updateString("<color=red>Name: </color>" + "<color=yellow>" + backmanager.getThisItem(buttonID).itemName + "</color>\n" + "Description: " + "<color=grey>" + backmanager.getThisItem(buttonID).itemDes + "</color>\n");
            RectTransformUtility.ScreenPointToLocalPointInRectangle(GameObject.Find("UI").transform as RectTransform, Input.mousePosition, null, out position);
            description.setPosition(position);

            inzone = true;
        }
        else if (backmanager.getThisItem(buttonID) == null)
        {
            description.hide();
            inzone = false;
            description.updateString("");
        }

    }

    public void OnPointerExit(PointerEventData eventData)
    {
        if (backmanager.getThisItem(buttonID) != null)
        {
            description.hide();
            description.updateString("");
            inzone = false;
        }
    }
}
