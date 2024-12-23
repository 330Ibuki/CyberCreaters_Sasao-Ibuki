#ifndef _LIGHT_H_
#define _LIGHT_H_

//�C���N���[�h
#include "main.h"

//�}�N��
#define LIGHT	(3)

//���C�g�N���X�̒�`
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
