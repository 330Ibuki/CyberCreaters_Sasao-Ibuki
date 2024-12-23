/*=============
sound
=============*/

#include "main.h"
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

class CSound
{
public:
	typedef enum
	{
		BGM_TEST = 0,
		BGM_MAX
	}SOUND_BGM;

	typedef enum
	{
		BGM_OPEN = 0,
		BGM_CLOSE,
		BGM_PLAY,
		BGM_STOP,
		BGM_PAUSE,
		BGM_PAUSEPLAY,
		STATE_MAX
	}BGM_STATE;

	typedef enum
	{
		SE_NULL = 0,
		SE_MAX
	}SOUND_SE;
	//çƒê∂
	static void BGM(SOUND_BGM BGM, BGM_STATE State);
	static void SEPlay(SOUND_SE SE);
};