using System.Collections;
using System.Collections.Generic;
using UnityEngine;
[System.Serializable]
public class PlayerData 
{
    // Start is called before the first frame update
    public int health;
    public float energy;
    public float volumn;
    public string [] itemName;
    public int [] itemNumber;

    public PlayerData(PlayerMovement player, BackpackManager back)
    {
        health = player.currentHealth;
        energy = player.currentEnergy;
        volumn = player.currentVolumn;
        itemName = new string[back.items.Count];
        itemNumber = new int[back.items.Count];
        for (int i = 0; i < back.items.Count; i++)
         {
            itemName[i] = back.items[i].name;
            itemNumber[i] = back.itemNumbers[i];
        }
    }
}
