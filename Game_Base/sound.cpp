/*======================
Sound
=======================*/

//インクルード
#include "sound.h"

/*========================
BGM操作
=========================*/
void CSound::BGM(SOUND_BGM BGM, BGM_STATE State)
{
	if (State == BGM_OPEN)
	{
		if (BGM == BGM_TEST)
		{
			mciSendStringA("open \"data\\BGM\\m-art_ZoeOfAeon.mp3\" alias BGM", NULL, 0, NULL);//mp3でないとループで再生できない?
		}
	}

	else if (State == BGM_CLOSE)
	{
		mciSendStringA("close BGM", NULL, 0, NULL);
	}
	else if (State == BGM_PLAY)
	{
		mciSendStringA("play BGM repeat", NULL, 0, NULL);
	}
	else if (State == BGM_STOP)
	{
		mciSendStringA("stop BGM", NULL, 0, NULL);
		mciSendStringA("seek BGM to start", NULL, 0, NULL);
	}
	//使用用途不明
	//else if (State == BGM_PAUSE)
	//{

	//}

	//else if (State == BGM_PAUSEPLAY)
	//{

	//}
}

 /*==================
 //SE
 ==================*/
void CSound::SEPlay(SOUND_SE SE)
{
	//open
	//play
	//close
}