﻿using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
public class botBehavior : MonoBehaviour {


    public Button btn;

    // Use this for initialization

  

    public void setBtn(UnityEngine.UI.Button _btn) {

        btn = _btn;  
    } 
    public void rotateBot(int xpos, int ypos, int zpos) {

        //TODO: make this a reasonable animation in the future 
        Vector3 angles = new Vector3((float)xpos, (float)ypos, (float)zpos);
        transform.Rotate(angles);     
    }

    public void triggerSound() {

        btn.onClick.Invoke();

      }

}
