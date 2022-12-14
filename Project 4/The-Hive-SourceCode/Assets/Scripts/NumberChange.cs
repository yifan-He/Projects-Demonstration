using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class NumberChange : MonoBehaviour
{
    public Text changeNumber1;
    public Text changeNumber2;
    public Text changeNumber3;
    public Text changeNumber4;
    public Text changeNumber5;
    public Text changeNumber6;
     int number1 = 0;
     int number2 = 0;
     int number3 = 0;
     int number4 = 0;
     int number5 = 0;
     int number6 = 0;
    public GameObject canvas;

    private Transform player;

    public GameObject Capsule;


    private void Start()
    {
        player = GameObject.FindGameObjectWithTag("Player").GetComponent<Transform>();
        
    }

    // Update is called once per frame
    void Update()
    {
        Change1();
        Change2();
        Change3();
        Change4();
        Change5();
        Change6();
        checkPassword();

        if (Input.GetKeyDown(KeyCode.Escape))
        {
            canvas.SetActive(false);
            number1 = 0;
            number2 = 0;
            number3 = 0;
            number4 = 0;
            number5 = 0;
            number6 = 0;
        }
    }



    public void Change1()
    {
        
        changeNumber1.text = number1.ToString();
    }

    public void Change2()
    {

        changeNumber2.text = number2.ToString();
    }
    public void Change3()
    {

        changeNumber3.text = number3.ToString();
    }
    public void Change4()
    {

        changeNumber4.text = number4.ToString();
    }
    public void Change5()
    {

        changeNumber5.text = number5.ToString();
    }
    public void Change6()
    {

        changeNumber6.text = number6.ToString();
    }


    public void Add1()
    {
        number1 += 1;
        if (number1 > 9) number1 = 0;
    }

    public void Add2()
    {
        number2 += 1;
        if (number2 > 9) number2 = 0;
    }

    public void Add3()
    {
        number3 += 1;
        if (number3 > 9) number3 = 0;
    }

    public void Add4()
    {
        number4 += 1;
        if (number4 > 9) number4 = 0;
    }

    public void Add5()
    {
        number5 += 1;
        if (number5 > 9) number5 = 0;
    }

    public void Add6()
    {
        number6 += 1;
        if (number6 > 9) number6 = 0;
    }

    public void Minus1()
    {
        number1 -= 1;
        if (number1 < 0) number1 = 9;
    }
    public void Minus2()
    {
        number2 -= 1;
        if (number2 < 0) number2 = 9;
    }
    public void Minus3()
    {
        number3 -= 1;
        if (number3 < 0) number3 = 9;
    }
    public void Minus4()
    {
        number4 -= 1;
        if (number4 < 0) number4 = 9;
    }
    public void Minus5()
    {
        number5 -= 1;
        if (number5 < 0) number5 = 9;
    }
    public void Minus6()
    {
        number6 -= 1;
        if (number6 < 0) number6 = 9;
    }

    public void checkPassword()
    {
        if (number1 == 2 && number2 == 7 && number3 == 0 && number4 == 5 && number5 == 3 && number6 == 9)
        {
            canvas.SetActive(false);
            Instantiate(Capsule, player.position + new Vector3(0.5f, 0.5f), Quaternion.identity);

        }
            
    }



}
