#ifndef _COLLISION_H_
#define _COLLISION_H_

//�C���N���[�h
#include "main.h"

//�}�N����`
#define M_COL	(1024)
#define C_PRI	(6)

//�����蔻��̒�`
class CCollision
{
public:
	/*
	* �O�u���b�N
	* �P�v���C���[
	* �Q�G
	* �R�_���[�W���Ȃ��M�~�b�N
	* �S�_���[�W����������M�~�b�N
	* �T�擾�ł������
	*/
	typedef enum
	{
		NONE = 0,
		PLAYER,
		ENEMY,
		GIMIC,
		TRAP,
		ITEM,
		C_MAX
	}C_TYPE;

	CCollision(int C_pri = 0,int C_ID = 0);
	~CCollision();
	HRESULT Init();
	void Uninit();
	void Update();

private:
};

#endif // !_COLLISION_H_
