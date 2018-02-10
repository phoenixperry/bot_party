using UnityEngine;
using UnityEngine.UI;
using System.Collections;


//#TODO we need to make it so the buttons don't repeat. We will need to get a bit of data about each state passed into this object
public class buttonSound : MonoBehaviour
{

    bool btnOn = false; 
    void Start()
    {
        gameObject.GetComponent<Button>().onClick.AddListener(TaskOnClick);
        gameObject.GetComponent<AudioSource>().playOnAwake = false;
                          
    }


    void TaskOnClick()
    {

        if (!gameObject.GetComponent<AudioSource>().isPlaying && btnOn == false)
        {
            gameObject.GetComponent<AudioSource>().Play();
            btnOn = true;
        } 
       
    }
}

    