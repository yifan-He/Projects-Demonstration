using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(menuName = "Item", fileName = "New Item")]
public class itemCreate : ScriptableObject
{
    public string itemName;
    public string itemDes;//item description

    public Sprite itemSprite;
}
