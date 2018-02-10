using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EventTestExample : MonoBehaviour {
    //hello friends and my future self which forgets all code, 
    //here's an exmaple of how to subscribe an event! 
 
    public void OnEnable()
    {
        TouchData.OnBoxOneTwoTouched += testFunctionOneTouch;
        TouchData.OnBoxOneTwoReleased += testFunctionOneRelease;

        TouchData.OnBoxOneThreeTouched += testFunctionTwoTouch;
        TouchData.OnBoxOneThreeReleased += testFunctionTwoRelease;

        TouchData.OnBoxTwoThreeTouched += testFunction3Touch;
        TouchData.OnBoxTwoThreeReleased += testFunction3Release;

        TouchData.OnAllBoxesConnected += testFunction4Touch;
        TouchData.OnAllBoxesReleased += testFunction4Release; 
    }

    public void OnDisable() {

        TouchData.OnBoxOneTwoTouched -= testFunctionOneTouch;
        TouchData.OnBoxOneTwoReleased -= testFunctionOneRelease;

        TouchData.OnBoxOneThreeTouched -= testFunctionTwoTouch;
        TouchData.OnBoxOneThreeReleased -= testFunctionTwoRelease;

        TouchData.OnBoxTwoThreeTouched -= testFunction3Touch;
        TouchData.OnBoxTwoThreeReleased -= testFunction3Release;

        TouchData.OnAllBoxesConnected -= testFunction4Touch;
        TouchData.OnAllBoxesReleased -= testFunction4Release;

    }

    void testFunctionOneTouch() {
    Debug.Log("OnBoxOneTwo touch event works!"); 
    }

    void testFunctionOneRelease()
    {
        Debug.Log("OnBoxOneTwo release event works!");
    }

    void testFunctionTwoTouch()
    {
        Debug.Log("OnBoxOneThree touch event works!");
    }

    void testFunctionTwoRelease()
    {
        Debug.Log("OnBoxOneThree release event works!");
    }

    void testFunction3Touch() {
        Debug.Log("Two three touch event works");
    }

    void testFunction3Release() {
        Debug.Log("two three release event works");
    }

    void testFunction4Touch()
    {
        Debug.Log("all touching event works");
    }
     
    void testFunction4Release()
    {
        Debug.Log("all touching release works");
    }


}
