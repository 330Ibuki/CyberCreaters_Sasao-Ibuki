/*=================================
#
# GameTool_StageCrafter
# Author: Sasao Ibuki
#
=================================*/

#ifndef _TOOL_H_
#define _TOOL_H_

#include "main.h"
#include "billboard.h"
#include "renderer.h"
#include "input.h"
#include "manager.h"

#define Place_M	(1000)


class CToolPlace
{
public:
	CToolPlace();
	~CToolPlace();
	void Init();
	void Uninit();
	void Update();
	static CToolPlace* GetTool();
	static CToolPlace* Active();
	D3DXVECTOR3 B_pos; //�u���b�N���W
	bool IsActive;	//�N�����Ă邩�ǂ���
	int B_Num;	//�u���b�N�̔ԍ�
	int B_CurMax;	//���ݎ��_�ł̍ő�u���b�N��
	bool IsFirst;	//������菈��
private:
	static CToolPlace* TP;

};

class CTP_img : public CB_board
{
public:
	CTP_img();
	~CTP_img()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static int GetImgNum();
	static CTP_img* Getimg(int Num);
	static CTP_img* Create(D3DXVECTOR3 pos, int Num);
	int ImgNum;

private:
	static CTP_img* Place_Img[Place_M];
	static int TP_INum;
};

class CTP_SaveLoad	//�Z�[�u���[�h+�X�e�[�W�p�̃e�L�X�g�f�[�^�ւ̕ϊ�
{
public:
	CTP_SaveLoad();
	~CTP_SaveLoad();
	static void Save();
	static void Load();
};

#endif // !_TOOL_H_