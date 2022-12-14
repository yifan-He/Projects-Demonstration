using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AudioManager : MonoBehaviour
{
    public static AudioManager instance { get; private set; }
    // Start is called before the first frame update
    private AudioSource audio;
    void Start()
    {
        instance = this;
        audio = GetComponent<AudioSource>();
    }

    // Update is called once per frame
    public void AudioPlay(AudioClip clip)
    {
        audio.PlayOneShot(clip);
    }

    public void AudioPause()
    {
        audio.Pause();
    }

    public void AudioContinue()
    {
        audio.Play();
    }
}
