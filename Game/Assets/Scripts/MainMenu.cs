using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class MainMenu : MonoBehaviour {

	public void PlayGame () {
		SceneManager.LoadScene("GameScene"); //load the game scene if PLAY chosen
	}

	public void QuitGame () {
		Application.Quit(); //if QUIT button chosen
	}
}
