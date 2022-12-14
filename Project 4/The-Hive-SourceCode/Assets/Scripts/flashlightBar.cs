using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
public class flashlightBar : MonoBehaviour
{
    // Start is called before the first frame update
    public Slider slider;
    public Image fill;

    public void SetMaxVolumn(float Volumn)
    {
        slider.maxValue = Volumn;
        slider.value = Volumn;
        fill.color = Color.blue;
    }

    public void SetVolumn(float Volumn)
    {
        slider.value = Volumn;
        if (Volumn < 50)
            fill.color = Color.yellow;
        if (Volumn < 10 )
            fill.color = Color.red;
        if (Volumn > 50)
        {
            fill.color = Color.blue;
        }
    }
}
