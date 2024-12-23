#ifndef _LIGHT_H_
#define _LIGHT_H_

//インクルード
#include "main.h"

//マクロ
#define LIGHT	(3)

//ライトクラスの定義
class CLight
{
public:
	CLight();
	~CLight();
	HRESULT Init();
	void Uninit();
	void Update();

private:
	D3DLIGHT9 m_aLight[LIGHT];
};

#endif // !_LIGHT_H_
