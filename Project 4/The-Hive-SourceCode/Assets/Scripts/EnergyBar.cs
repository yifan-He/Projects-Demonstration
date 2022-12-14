using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
public class EnergyBar : MonoBehaviour
{
    public Slider slider;
    public Image fill;
    public void SetMaxEnergy(float energy)
    {
        slider.maxValue = energy;
        slider.value = energy;
        fill.color = Color.grey;
    }

    public void SetEnergy(float energy)
    {
        slider.value = energy;
        if (energy < 20)
            fill.color = Color.yellow;
        if (energy < 10)
            fill.color = Color.red;
        if (energy > 20)
        {
            fill.color = Color.grey;
        }
    }
}
