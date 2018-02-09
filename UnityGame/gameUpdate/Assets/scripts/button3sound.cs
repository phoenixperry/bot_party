using UnityEngine;
using UnityEngine.UI;
using System.Collections;



public class button3sound : MonoBehaviour
{

    bool m_Play;
    public AudioClip audioclip;
    public AudioSource audio;
    public Button button;

    void Start()
    {
        Button btn = button.GetComponent<Button>();
        btn.onClick.AddListener(TaskOnClick);
        audio = GetComponent<AudioSource>();
        audio.playOnAwake = false;
    }

    void TaskOnClick()
    {
        //m_Play = true;
        audio.Play();
    }
}

