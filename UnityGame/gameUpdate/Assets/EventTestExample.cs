using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EventTestExample : MonoBehaviour {
    //hello friends and my future self which forgets all code, 
    //here's an exmaple of how to subscribe an event! 
 
    public void OnEnable()
    {
        TouchData.OnBoxOneTwoTouched += testFunction; 
 
    }

    public void OnDisable() {

        TouchData.OnBoxOneTwoTouched -= testFunction; 
    }  
    void testFunction() {
    Debug.Log("OnBoxOneTwo event works!"); 
    }

}
