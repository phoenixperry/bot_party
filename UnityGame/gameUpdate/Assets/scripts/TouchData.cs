using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TouchData : MonoBehaviour
{


    //    //this class handles all of the touches between boxes 

    public static string touchingBoxes; //what boxes are touching 
    public static int touch = 0; //touch state 
    public GameObject bot1;
    public GameObject bot2;
    public GameObject bot3;
    public AudioClip onetwo;
    public AudioClip twothree;
    public AudioClip onethree;
    public AudioClip allthree;
    public ArrayList touchsound = new ArrayList();
    private bool allOn = false;
    private bool boxOneTwoOn = false;
    private bool boxTwoThreeOn = false;
    private bool boxOneThreeOn = false;

    private void Start()
    {
        gameObject.GetComponent<AudioSource>().playOnAwake = false;
        touchsound.Add(onetwo);
        touchsound.Add(twothree);
        touchsound.Add(onethree);
        touchsound.Add(allthree);

    }


    public void updateData(string value)
    {
        string[] sensors = value.Split(' '); //split the stinrg we got from arduino using a space as the delimiter of the string 
        touchingBoxes = sensors[0]; //the first value indicate which boxes are are testing for being connected 
        int.TryParse(sensors[1], out touch); //get the string value of the touch state and convert it to an int for sanity
       // Debug.Log("Touch Parsed: " + touchingBoxes + " touch state " + touch);


        if (touchingBoxes == "BoxOneTwo" && touch == 1 && allOn == false && boxOneTwoOn == false)
        {
            if (!gameObject.GetComponent<AudioSource>().isPlaying)
            {
                gameObject.GetComponent<AudioSource>().clip = touchsound[0] as AudioClip;
                gameObject.GetComponent<AudioSource>().Play();
            }
            boxOneTwoOn = true;
        }
        else if (touchingBoxes == "BoxOneTwo" && touch == 0)
        {
            boxOneTwoOn = false;
        }
        else if (touchingBoxes == "BoxTwoThree" && touch == 1 && allOn == false && boxTwoThreeOn == false)
        {
            if (!gameObject.GetComponent<AudioSource>().isPlaying)
            {
                gameObject.GetComponent<AudioSource>().clip = touchsound[1] as AudioClip;
                gameObject.GetComponent<AudioSource>().Play();
            }
            boxTwoThreeOn = true;
        }
        else if (touchingBoxes == "BoxTwoThree" && touch == 0)
        {
            boxTwoThreeOn = false;
        }
        else if (touchingBoxes == "BoxOneThree" && touch == 1 && allOn == false && boxOneThreeOn == false)
        {
            if (!gameObject.GetComponent<AudioSource>().isPlaying)
            {
                gameObject.GetComponent<AudioSource>().clip = touchsound[2] as AudioClip;
                gameObject.GetComponent<AudioSource>().Play();
            }
            boxOneThreeOn = true;
        }
        else if (touchingBoxes == "BoxOneThree" && touch == 0)
        {
            boxOneThreeOn = false;
        }
        else if (touchingBoxes == "AllBoxes" && touch == 1 && allOn == false )
        {

           
                Debug.Log("got here");
                gameObject.GetComponent<AudioSource>().clip = touchsound[3] as AudioClip;
                gameObject.GetComponent<AudioSource>().Play();
            
            allOn = true;

        }
        if (touchingBoxes == "AllBoxes" && touch == 0)
        {
            allOn = false;
        }
    }
}