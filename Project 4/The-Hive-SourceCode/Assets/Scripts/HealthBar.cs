using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
public class HealthBar : MonoBehaviour
{
    // Start is called before the first frame update
    public Slider slider;
    public Image fill;

    public void SetMaxHealth(int health)
    {
        slider.maxValue = health;
        slider.value = health;
        fill.color = Color.green;
    }

    public void SetHealth(int health)
    {
        slider.value = health;
        if(health == 2)
            fill.color = Color.yellow;
        if(health == 1)
            fill.color = Color.red;
        if (health > 2)
        {
            fill.color = Color.green;
        }
    }
}
