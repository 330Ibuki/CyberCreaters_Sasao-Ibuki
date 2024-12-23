#ifndef _GIMIC_H_
#define _GIMIC_H_

//�C���N���[�h
#include "main.h"
#include "objectx.h"

//�}�N����`
#define MGIMC	(1024)

//�X�e�[�W�\���p�u���b�N�N���X�i���N���X�FCObjectX�j
class CGimic : public CObjectX
{
public:
	typedef enum
	{
		NORMAL = 0,	//���E����
		REVERSE,	//���E�����i���]�j
		G_MAX
	}G_TYPE;

	CGimic();
	~CGimic();
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static CGimic* Create(D3DXVECTOR3 pos, D3DXVECTOR3 mov, G_TYPE type);
	static CGimic* GetGimic(int Num);
	static int GetGimNum();

	G_TYPE m_Rift;
	D3DXVECTOR3 m_move;
private:
	static CGimic* m_apGimic[MGIMC];
	static int GimNum;
	int m_Rift_timer;
	int m_Rift_Set;
	int m_Rift_Count;
	int m_Rift_BCount;

};
#endif // !_BLOCK_H_
