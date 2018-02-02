using UnityEngine;
using UnityEngine.UI;
using System.Collections;



public class buttonSound : MonoBehaviour
{
   

    void Start()
    {
        gameObject.GetComponent<Button>().onClick.AddListener(TaskOnClick);
        gameObject.GetComponent<AudioSource>().playOnAwake = false; ;
                          
    }

    void TaskOnClick()
    {

        gameObject.GetComponent<AudioSource>().Play();
    }
}

    