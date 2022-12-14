using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class BackpackManager : MonoBehaviour
{
    public List<itemCreate> items = new List<itemCreate>(); //what kinds of items we have
    public List<int> itemNumbers = new List<int>(); //how many this kinds of items we have
    public GameObject[] slots;

    // Start is called before the first frame update


    //To de to delete
/*    public itemCreate add;
    public itemCreate remove;*/

    void Start()
    {
        DisplayItems();
    }

    private void DisplayItems()
    {
/*        for(int i = 0; i < items.Count; i++)
        {
            //set itemimage
            slots[i].transform.GetChild(0).GetComponent<Image>().color = new Color(1, 1, 1, 1);//set alpha to 1
            slots[i].transform.GetChild(0).GetComponent<Image>().sprite = items[i].itemSprite;//change sprite

            //set count text
            slots[i].transform.GetChild(1).GetComponent<Text>().color = new Color(1, 1, 1, 1);//set alpha to 1
            slots[i].transform.GetChild(1).GetComponent<Text>().text = itemNumbers[i].ToString();

            //set remove button to true
            slots[i].transform.GetChild(2).gameObject.SetActive(true);
        }*/

        for (int i = 0; i < slots.Length; i++)
        {
            if (i < items.Count)
            {
                //set itemimage
                slots[i].transform.GetChild(0).GetComponent<Image>().color = new Color(1, 1, 1, 1);//set alpha to 1
                slots[i].transform.GetChild(0).GetComponent<Image>().sprite = items[i].itemSprite;//change sprite

                //set count text
                slots[i].transform.GetChild(1).GetComponent<Text>().color = new Color(1, 1, 1, 1);//set alpha to 1
                slots[i].transform.GetChild(1).GetComponent<Text>().text = itemNumbers[i].ToString();

                //set remove button to true
                slots[i].transform.GetChild(2).gameObject.SetActive(true);
            }//if have item, display
            else
            {
                //set itemimage
                slots[i].transform.GetChild(0).GetComponent<Image>().color = new Color(1, 1, 1, 0);//set alpha to 1
                slots[i].transform.GetChild(0).GetComponent<Image>().sprite = null;//change sprite

                //set count text
                slots[i].transform.GetChild(1).GetComponent<Text>().color = new Color(1, 1, 1, 0);//set alpha to 1
                slots[i].transform.GetChild(1).GetComponent<Text>().text = null;

                //set remove button to true
                slots[i].transform.GetChild(2).gameObject.SetActive(false);
            }// if we do not have it anymore, delete
            
        }
    }

    // Update is called once per frame

    public void addItem(itemCreate _item)
    {
        if (!items.Contains(_item))
        {
            items.Add(_item);
            itemNumbers.Add(1);//do not a have same one, add a new one
        }
        else
        {
            for(int i = 0; i < items.Count; i++)
            {
                if(_item == items[i])
                {
                    itemNumbers[i]++;
                }
            }//have a same one, increase the number
        }
        DisplayItems();
    }

    public void removeItem(itemCreate _item)
    {
        if (items.Contains(_item))
        {
            for (int i = 0; i < items.Count; i++)
            {
                if (_item == items[i])
                {
                    if (itemNumbers[i] > 1)
                    {
                        itemNumbers[i]--;
                    }//if number >1 decrease number 
                    else
                    {
                        items.Remove(items[i]);
                        itemNumbers.Remove(itemNumbers[i]);
                    }//if number <= 1 remove the item
                }
            }
        }
        DisplayItems();
    }

    public void resetSlots()
    {
        items.Clear();
        itemNumbers.Clear();
        DisplayItems();
    }//clear the slots

    public void DeleteThisItem(int buttonId)
    {
        itemCreate thisItem = null;
        for(int i = 0; i < items.Count; i++)
        {
            if(i == buttonId)
            {
                thisItem = items[i];
            }
        }
        removeItem(thisItem);
        
    }//use x to delete the item 

    public itemCreate getThisItem(int buttonId)
    {
        itemCreate thisItem = null;
        for (int i = 0; i < items.Count; i++)
        {
            if (i == buttonId)
            {
                thisItem = items[i];
            }
        }
        return thisItem;

    }//use x to delete the item 

    void Update()
    {
        /*        if (Input.GetKeyDown(KeyCode.Q))
                    addItem(add);
                if(Input.GetKeyDown(KeyCode.E))
                    removeItem(remove);*/

    }

    public bool isFull()
    {
        if (items.Count < slots.Length)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

}
