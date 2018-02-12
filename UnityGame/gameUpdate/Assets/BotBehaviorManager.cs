using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
public class BotBehaviorManager : MonoBehaviour {


    public Button btn;

    // Use this for initialization

    public GameObject bot1;
    public GameObject bot2;
    public GameObject bot3;


    public void OnEnable()
    {
        TouchData.OnBoxOneTwoTouched += BoxOneTwoConnected;
        TouchData.OnBoxOneTwoReleased += BoxOneTwoReleased;

        TouchData.OnBoxOneThreeTouched += BoxOneThreeConnected;
        TouchData.OnBoxOneThreeReleased += BoxOneThreeReleased;

        TouchData.OnBoxTwoThreeTouched += BoxTwoThreeConnected;
        TouchData.OnBoxTwoThreeReleased += BoxTwoThreeReleased;

        TouchData.OnAllBoxesConnected += AllConnected;
        TouchData.OnAllBoxesReleased += AllReleased;
    }
    //here's how to unsubscibe - if you do one, you must do the other! 
    public void OnDisable()
    {
        TouchData.OnBoxOneTwoTouched -= BoxOneTwoConnected;
        TouchData.OnBoxOneTwoReleased -= BoxOneTwoReleased;

        TouchData.OnBoxOneThreeTouched -= BoxOneThreeConnected;
        TouchData.OnBoxOneThreeReleased -= BoxOneThreeReleased;

        TouchData.OnBoxTwoThreeTouched -= BoxTwoThreeConnected;
        TouchData.OnBoxTwoThreeReleased -= BoxTwoThreeReleased;

        TouchData.OnAllBoxesConnected -= AllConnected;
        TouchData.OnAllBoxesReleased -= AllReleased;

    }

    public void setBtn(UnityEngine.UI.Button _btn)
    {

        btn = _btn;
    }
    public void rotateBot(int xpos, int ypos, int zpos)
    {

        //TODO: make this a reasonable animation in the future 
        Vector3 angles = new Vector3((float)xpos, (float)ypos, (float)zpos);
        transform.Rotate(angles);
    }

    public void triggerSound()
    {

        btn.onClick.Invoke();

    }

    public void AllConnected()
    {
        //all connected actions 
    }

    public void AllReleased()
    {
        //all connected actions 
    }

    public void BoxOneThreeConnected()
    {

    }
    public void BoxOneThreeReleased()
    {

    }
    public void BoxOneTwoConnected()
    {

    }
    public void BoxOneTwoReleased()
    {

    }
    public void BoxTwoThreeConnected()
    {

    }
    public void BoxTwoThreeReleased()
    {

    }
}

