/*=================================
#
# GameTool_StageCrafter
# Author: Sasao Ibuki
#
=================================*/

//�C���N���[�h
#include "tool.h"
#include "scope.h"

//�ÓI�����o������
CToolPlace* CToolPlace::TP = {};
CTP_img* CTP_img::Place_Img[Place_M] = {};
int CTP_img::TP_INum = NULL;

/*=========================
�R���X�g���N�^�E�f�X�g���N�^
===========================*/

CToolPlace::CToolPlace()
{
	B_Num = NULL;
	B_CurMax = NULL;
	B_pos = {};
	IsFirst = false;
	IsActive = false;
}

CToolPlace::~CToolPlace()
{

}

/*=========================
������
===========================*/

void CToolPlace::Init()
{
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
}

/*=========================
�I��
===========================*/

void CToolPlace::Uninit()
{

}

/*=========================
�X�V
===========================*/

void CToolPlace::Update()
{
	CInputKeyboard* pKeyBoard = CManager::GetKeyboard();
	CTP_img* Img[Place_M] = {};

	//���񏈗�
	if (TP->IsFirst == true)
	{
		CTP_SaveLoad::Load();
		TP->B_pos = D3DXVECTOR3(0, 0, 0);
		CTP_img::Create(D3DXVECTOR3(0, 0, 0), 1);
		TP->B_CurMax = CTP_img::GetImgNum();
		TP->B_Num = CTP_img::GetImgNum();
		TP->IsFirst = false;
	}

	if (TP->B_CurMax <= 0)
	{
		CTP_img::Create(D3DXVECTOR3(0, 0, 0), 1);
		TP->B_pos = D3DXVECTOR3(0,0,0);
		TP->B_CurMax++;
	}

	for (int i = 0; i < Place_M; i++)
	{
		Img[i] = Img[i]->Getimg(i);
	}

	/*===================================�ړ�����==============================*/
	if (pKeyBoard->GetPress(DIK_W) == true) //up
	{
		TP->B_pos.y += 0.5f;
		if (Img[TP->B_Num] != nullptr)
		{
			Img[TP->B_Num]->m_pos.y += 0.5f;
		}
	}

	if (pKeyBoard->GetPress(DIK_S) == true) //down
	{
		TP->B_pos.y -= 0.5f;
		if (Img[TP->B_Num] != nullptr)
		{
			Img[TP->B_Num]->m_pos.y -= 0.5f;
		}
	}

	if (pKeyBoard->GetPress(DIK_A) == true) //left
	{
		TP->B_pos.x -= 0.5f;
		if (Img[TP->B_Num] != nullptr)
		{
			Img[TP->B_Num]->m_pos.x -= 0.5f;
		}
	}

	if (pKeyBoard->GetPress(DIK_D) == true) //right
	{
		TP->B_pos.x += 0.5f;
		if (Img[TP->B_Num] != nullptr)
		{
			Img[TP->B_Num]->m_pos.x += 0.5f;
		}
	}

	/*===================================�ړ�����==============================*/

	/*===================================�����Ǘ�==============================*/
	else if (pKeyBoard->GetTrigger(DIK_RETURN) == true) //Place
	{
		//create
		CTP_img::Create(D3DXVECTOR3(TP->B_pos.x, TP->B_pos.y, TP->B_pos.z), Img[TP->B_Num]->ImgNum);
		TP->B_Num++;
		TP->B_CurMax++;
	}


	/*===================================�����Ǘ�==============================*/

	/*===================================�I������==============================*/
	else if (pKeyBoard->GetTrigger(DIK_Z) == true) //Prev
	{
		TP->B_Num--;
		if (TP->B_Num <= 0)
		{
			TP->B_Num = 0;
		}
		TP->B_pos = Img[TP->B_Num]->m_pos;
	}

	else if (pKeyBoard->GetTrigger(DIK_C) == true) //Next
	{
		TP->B_Num++;
		if (TP->B_Num >= TP->B_CurMax)
		{
			TP->B_Num = 0;
		}
		TP->B_pos = Img[TP->B_Num]->m_pos;
	}

	else if (pKeyBoard->GetTrigger(DIK_Q) == true)	//�O�̃I�u�W�F�N�g��
	{
		Img[TP->B_Num]->ImgNum--;

		if (Img[TP->B_Num]->ImgNum < 1)
		{
			Img[TP->B_Num]->ImgNum = 19;
		}
	}

	else if (pKeyBoard->GetTrigger(DIK_E) == true)	//���̃I�u�W�F�N�g��
	{
		Img[TP->B_Num]->ImgNum++;

		if (Img[TP->B_Num]->ImgNum >= 20)
		{
			Img[TP->B_Num]->ImgNum = 1;
		}
	}
	/*===================================�I������==============================*/

	/*===================================�Z�[�u���[�h==============================*/
	else if (pKeyBoard->GetTrigger(DIK_F1) == true)	//�Z�[�u
	{//�f�[�^���͌��݂̍ő吔
		CTP_SaveLoad::Save();
	}
	/*===================================�Z�[�u���[�h==============================*/
}

/*============================
//�擾�E����
============================*/
CToolPlace* CToolPlace::GetTool()
{
	return TP;
}

CToolPlace* CToolPlace::Active()
{
	if (TP == nullptr)
	{
		TP = new CToolPlace();
		TP->B_Num = 0;
		TP->B_CurMax = 0;
		TP->B_pos.x = 0;
		TP->B_pos.y = 0;
		TP->B_pos.z = -10;
		TP->IsFirst = true;
		TP->IsActive = true;
		TP->Init();
	}
	return TP;
}

/*========================================
//�c�[���̉摜����
=========================================*/

/*==================================
//�R���X�g���N�^�E�f�X�g���N�^
==================================*/
CTP_img::CTP_img() : CB_board(m_Priority = 5)
{
	ImgNum = 0;
	TP_INum++;
}

CTP_img::~CTP_img()
{
	TP_INum--;
}

/*==================================
//������
==================================*/
HRESULT CTP_img::Init()
{
	VERTEX_3D* pVtx;
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0 - B_Width, 0 + B_Height, 0);
	pVtx[1].pos = D3DXVECTOR3(0 + B_Width, 0 + B_Height, 0);
	pVtx[2].pos = D3DXVECTOR3(0 - B_Width, 0, 0);
	pVtx[3].pos = D3DXVECTOR3(0 + B_Width, 0, 0);

	//�@���x�N�g��
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�J���[�ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, .7f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, .7f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, .7f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, .7f);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	m_pVtxBuff->Unlock();

	return S_OK;
}

/*==================================
//�j��
==================================*/
void CTP_img::Uninit()
{
	CB_board::Uninit();
}

/*==================================
//�X�V
==================================*/
void CTP_img::Update()
{
	VERTEX_3D* pVtx;
	CInputKeyboard* pKeyBoard = CManager::GetKeyboard();
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	if (IsUse == true)
	{

		switch (ImgNum)
		{
		case 1:
			D3DXCreateTextureFromFile(pDevice, "data\\TOOL\\TEXTURE\\Tool_Ground_Small.png", &m_ptex);	//���i���j
			B_Height = 50;
			B_Width = 45;
			break;

		case 2:
			D3DXCreateTextureFromFile(pDevice, "data\\TOOL\\TEXTURE\\Tool_Ground_Middle.png", &m_ptex);	//���i���j
			B_Height = 50;
			B_Width = 80;
			break;

		case 3:
			D3DXCreateTextureFromFile(pDevice, "data\\TOOL\\TEXTURE\\Tool_Ground_Big.png", &m_ptex);	//���i��j
			B_Height = 50;
			B_Width = 125;
			break;

		case 4:
			D3DXCreateTextureFromFile(pDevice, "data\\TOOL\\TEXTURE\\Tool_Roof.png", &m_ptex);	//�V��
			B_Height = 20;
			B_Width = 125;
			break;

		case 5:
			D3DXCreateTextureFromFile(pDevice, "data\\TOOL\\TEXTURE\\Tool_Wall.png", &m_ptex);	//��
			B_Height = 100;
			B_Width = 15;
			break;

		case 6:
			D3DXCreateTextureFromFile(pDevice, "data\\TOOL\\TEXTURE\\Tool_Block.png", &m_ptex);	//�u���b�N
			B_Height = 20;
			B_Width = 10;
			break;

		case 7:
			D3DXCreateTextureFromFile(pDevice, "data\\TOOL\\TEXTURE\\Tool_Plat_Small.png", &m_ptex);	//����ʂ��i���j
			B_Height = 5;
			B_Width = 20;
			break;

		case 8:
			D3DXCreateTextureFromFile(pDevice, "data\\TOOL\\TEXTURE\\Tool_Plat_Middle.png", &m_ptex);	//����ʂ��i���j
			B_Height = 10;
			B_Width = 5;
			break;

		case 9:
			D3DXCreateTextureFromFile(pDevice, "data\\TOOL\\TEXTURE\\Tool_Item_Score.png", &m_ptex);	//�X�R�A�A�C�e��
			B_Height = 20;
			B_Width = 10;
			break;

		case 10:
			D3DXCreateTextureFromFile(pDevice, "data\\TOOL\\TEXTURE\\Tool_Item_Middle.png", &m_ptex);	//�c�@�A�C�e��
			B_Height = 20;
			B_Width = 10;
			break;

		case 11:
			D3DXCreateTextureFromFile(pDevice, "data\\TOOL\\TEXTURE\\Tool_Start.png", &m_ptex);	//�X�^�[�g
			B_Height = 30;
			B_Width = 10;
			break;

		case 12:
			D3DXCreateTextureFromFile(pDevice, "data\\TOOL\\TEXTURE\\Tool_Goal.png", &m_ptex);	//�S�[��
			B_Height = 30;
			B_Width = 10;
			break;

		case 13:
			D3DXCreateTextureFromFile(pDevice, "data\\TOOL\\TEXTURE\\Tool_Enemy_Normal.png", &m_ptex);	//�G_Normal
			B_Height = 20;
			B_Width = 10;
			break;

		case 14:
			D3DXCreateTextureFromFile(pDevice, "data\\TOOL\\TEXTURE\\Tool_Enemy_Rapid.png", &m_ptex);	//�G_Rapid
			B_Height = 20;
			B_Width = 10;
			break;

		case 15:
			D3DXCreateTextureFromFile(pDevice, "data\\TOOL\\TEXTURE\\Tool_Enemy_Sniper.png", &m_ptex);	//�G_Sniper
			B_Height = 20;
			B_Width = 10;
			break;

		case 16:
			D3DXCreateTextureFromFile(pDevice, "data\\TOOL\\TEXTURE\\Tool_Enemy_3WUp.png", &m_ptex);	//�G_3W_up
			B_Height = 20;
			B_Width = 10;
			break;

		case 17:
			D3DXCreateTextureFromFile(pDevice, "data\\TOOL\\TEXTURE\\Tool_Enemy_3WDown.png", &m_ptex);	//�G_3W_Down
			B_Height = 20;
			B_Width = 10;
			break;

		case 18:
			D3DXCreateTextureFromFile(pDevice, "data\\TOOL\\TEXTURE\\Tool_Enemy_3WLeft.png", &m_ptex);	//�G_3W_Left
			B_Height = 20;
			B_Width = 10;
			break;

		case 19:
			D3DXCreateTextureFromFile(pDevice, "data\\TOOL\\TEXTURE\\Tool_Enemy_3WRight.png", &m_ptex);	//�G_3W_Right
			B_Height = 20;
			B_Width = 10;
			break;

		default:
			break;
		}

		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0 - B_Width, 0 + B_Height, 0);
		pVtx[1].pos = D3DXVECTOR3(0 + B_Width, 0 + B_Height, 0);
		pVtx[2].pos = D3DXVECTOR3(0 - B_Width, 0, 0);
		pVtx[3].pos = D3DXVECTOR3(0 + B_Width, 0, 0);

		//�@���x�N�g��
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//���_�J���[�ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, .7f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, .7f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, .7f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, .7f);

		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		m_pVtxBuff->Unlock();

	}

	else
	{
		CTP_img::Uninit();
	}

}

/*==================================
//�`��
==================================*/
void CTP_img::Draw()
{
	if (IsUse == true)
	{
		CB_board::Draw();
	}
}

/*==================================
//�����E�擾
==================================*/
int CTP_img::GetImgNum()
{
	return TP_INum;
}

CTP_img* CTP_img::Getimg(int Num)
{
	return Place_Img[Num];
}

CTP_img* CTP_img::Create(D3DXVECTOR3 pos, int Num)
{
	int PlaceNum = CTP_img::GetImgNum();
	if (Place_Img[PlaceNum] != nullptr)
	{
		Place_Img[PlaceNum] = nullptr;
	}

	if (Place_Img[PlaceNum] == nullptr)
	{
		Place_Img[PlaceNum] = new CTP_img();
		Place_Img[PlaceNum]->m_pos = pos;
		Place_Img[PlaceNum]->ImgNum = Num;
		Place_Img[PlaceNum]->IsUse = true;
		Place_Img[PlaceNum]->Init();
	}
	return Place_Img[PlaceNum];
}

/*=================================================
//�Z�[�u���[�h
=================================================*/

/*======================================
//�R���X�g���N�^�E�f�X�g���N�^
=======================================*/
CTP_SaveLoad::CTP_SaveLoad()
{

}

CTP_SaveLoad::~CTP_SaveLoad()
{

}

/*=====================================
//�Z�[�u
=====================================*/
void CTP_SaveLoad::Save()
{
	int DataNum = CTP_img::GetImgNum() - 1;
	CTP_img* Img[Place_M] = {};
	for (int i = 0; i < Place_M; i++)
	{
		Img[i] = Img[i]->Getimg(i);
	}
	//�摜�ԍ��A�ʒu���O���t�@�C���ɋL�^
	ofstream SaveData("data\\TOOL\\SAVE\\Stage_XX.txt");
	if (SaveData.is_open())
	{
		SaveData << DataNum << endl;	//�f�[�^��
		for (int Data = 0; Data < DataNum; Data++)
		{
			SaveData << Img[Data]->ImgNum << endl;	//�摜�ԍ�
			SaveData << Img[Data]->m_pos.x << endl;	//�ʒuX
			SaveData << Img[Data]->m_pos.y << endl;	//�ʒuY
			SaveData << Img[Data]->m_pos.z << endl;	//�ʒuZ
		}
		SaveData.close();
	}

}

/*=====================================
//���[�h
=====================================*/
void CTP_SaveLoad::Load()
{
	int DataNum = 0,ImgNum = 0;
	float PosX = 0, PosY = 0, PosZ = 0;
	
	//�L�^�������̂���ނ��ƂɃ��[�h
	ifstream SaveData("data\\TOOL\\SAVE\\Stage_XX.txt");
	if (SaveData.is_open())
	{
		string line;
		getline(SaveData, line);
		DataNum = stoi(line);

		for (int Data = 0; Data < DataNum; Data++)
		{
			getline(SaveData, line);
			ImgNum = stoi(line);
			getline(SaveData, line);
			PosX = stof(line);
			getline(SaveData, line);
			PosY = stof(line);
			getline(SaveData, line);
			PosZ = stof(line);

			CTP_img::Create(D3DXVECTOR3(PosX, PosY, PosZ), ImgNum);
		}
		SaveData.close();
	}
}

