/*=================================
#
# GameTool_StageCrafter
# Author: Sasao Ibuki
#
=================================*/

//インクルード
#include "tool.h"
#include "scope.h"

//静的メンバ初期化
CToolPlace* CToolPlace::TP = {};
CTP_img* CTP_img::Place_Img[Place_M] = {};
int CTP_img::TP_INum = NULL;

/*=========================
コンストラクタ・デストラクタ
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
初期化
===========================*/

void CToolPlace::Init()
{
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
}

/*=========================
終了
===========================*/

void CToolPlace::Uninit()
{

}

/*=========================
更新
===========================*/

void CToolPlace::Update()
{
	CInputKeyboard* pKeyBoard = CManager::GetKeyboard();
	CTP_img* Img[Place_M] = {};

	//初回処理
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

	/*===================================移動処理==============================*/
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

	/*===================================移動処理==============================*/

	/*===================================生成管理==============================*/
	else if (pKeyBoard->GetTrigger(DIK_RETURN) == true) //Place
	{
		//create
		CTP_img::Create(D3DXVECTOR3(TP->B_pos.x, TP->B_pos.y, TP->B_pos.z), Img[TP->B_Num]->ImgNum);
		TP->B_Num++;
		TP->B_CurMax++;
	}


	/*===================================生成管理==============================*/

	/*===================================選択処理==============================*/
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

	else if (pKeyBoard->GetTrigger(DIK_Q) == true)	//前のオブジェクトへ
	{
		Img[TP->B_Num]->ImgNum--;

		if (Img[TP->B_Num]->ImgNum < 1)
		{
			Img[TP->B_Num]->ImgNum = 19;
		}
	}

	else if (pKeyBoard->GetTrigger(DIK_E) == true)	//次のオブジェクトへ
	{
		Img[TP->B_Num]->ImgNum++;

		if (Img[TP->B_Num]->ImgNum >= 20)
		{
			Img[TP->B_Num]->ImgNum = 1;
		}
	}
	/*===================================選択処理==============================*/

	/*===================================セーブロード==============================*/
	else if (pKeyBoard->GetTrigger(DIK_F1) == true)	//セーブ
	{//データ数は現在の最大数
		CTP_SaveLoad::Save();
	}
	/*===================================セーブロード==============================*/
}

/*============================
//取得・生成
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
//ツールの画像部分
=========================================*/

/*==================================
//コンストラクタ・デストラクタ
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
//初期化
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

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0 - B_Width, 0 + B_Height, 0);
	pVtx[1].pos = D3DXVECTOR3(0 + B_Width, 0 + B_Height, 0);
	pVtx[2].pos = D3DXVECTOR3(0 - B_Width, 0, 0);
	pVtx[3].pos = D3DXVECTOR3(0 + B_Width, 0, 0);

	//法線ベクトル
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//頂点カラー設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, .7f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, .7f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, .7f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, .7f);

	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	m_pVtxBuff->Unlock();

	return S_OK;
}

/*==================================
//破棄
==================================*/
void CTP_img::Uninit()
{
	CB_board::Uninit();
}

/*==================================
//更新
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
			D3DXCreateTextureFromFile(pDevice, "data\\TOOL\\TEXTURE\\Tool_Ground_Small.png", &m_ptex);	//床（小）
			B_Height = 50;
			B_Width = 45;
			break;

		case 2:
			D3DXCreateTextureFromFile(pDevice, "data\\TOOL\\TEXTURE\\Tool_Ground_Middle.png", &m_ptex);	//床（中）
			B_Height = 50;
			B_Width = 80;
			break;

		case 3:
			D3DXCreateTextureFromFile(pDevice, "data\\TOOL\\TEXTURE\\Tool_Ground_Big.png", &m_ptex);	//床（大）
			B_Height = 50;
			B_Width = 125;
			break;

		case 4:
			D3DXCreateTextureFromFile(pDevice, "data\\TOOL\\TEXTURE\\Tool_Roof.png", &m_ptex);	//天井
			B_Height = 20;
			B_Width = 125;
			break;

		case 5:
			D3DXCreateTextureFromFile(pDevice, "data\\TOOL\\TEXTURE\\Tool_Wall.png", &m_ptex);	//壁
			B_Height = 100;
			B_Width = 15;
			break;

		case 6:
			D3DXCreateTextureFromFile(pDevice, "data\\TOOL\\TEXTURE\\Tool_Block.png", &m_ptex);	//ブロック
			B_Height = 20;
			B_Width = 10;
			break;

		case 7:
			D3DXCreateTextureFromFile(pDevice, "data\\TOOL\\TEXTURE\\Tool_Plat_Small.png", &m_ptex);	//すりぬけ（小）
			B_Height = 5;
			B_Width = 20;
			break;

		case 8:
			D3DXCreateTextureFromFile(pDevice, "data\\TOOL\\TEXTURE\\Tool_Plat_Middle.png", &m_ptex);	//すりぬけ（中）
			B_Height = 10;
			B_Width = 5;
			break;

		case 9:
			D3DXCreateTextureFromFile(pDevice, "data\\TOOL\\TEXTURE\\Tool_Item_Score.png", &m_ptex);	//スコアアイテム
			B_Height = 20;
			B_Width = 10;
			break;

		case 10:
			D3DXCreateTextureFromFile(pDevice, "data\\TOOL\\TEXTURE\\Tool_Item_Middle.png", &m_ptex);	//残機アイテム
			B_Height = 20;
			B_Width = 10;
			break;

		case 11:
			D3DXCreateTextureFromFile(pDevice, "data\\TOOL\\TEXTURE\\Tool_Start.png", &m_ptex);	//スタート
			B_Height = 30;
			B_Width = 10;
			break;

		case 12:
			D3DXCreateTextureFromFile(pDevice, "data\\TOOL\\TEXTURE\\Tool_Goal.png", &m_ptex);	//ゴール
			B_Height = 30;
			B_Width = 10;
			break;

		case 13:
			D3DXCreateTextureFromFile(pDevice, "data\\TOOL\\TEXTURE\\Tool_Enemy_Normal.png", &m_ptex);	//敵_Normal
			B_Height = 20;
			B_Width = 10;
			break;

		case 14:
			D3DXCreateTextureFromFile(pDevice, "data\\TOOL\\TEXTURE\\Tool_Enemy_Rapid.png", &m_ptex);	//敵_Rapid
			B_Height = 20;
			B_Width = 10;
			break;

		case 15:
			D3DXCreateTextureFromFile(pDevice, "data\\TOOL\\TEXTURE\\Tool_Enemy_Sniper.png", &m_ptex);	//敵_Sniper
			B_Height = 20;
			B_Width = 10;
			break;

		case 16:
			D3DXCreateTextureFromFile(pDevice, "data\\TOOL\\TEXTURE\\Tool_Enemy_3WUp.png", &m_ptex);	//敵_3W_up
			B_Height = 20;
			B_Width = 10;
			break;

		case 17:
			D3DXCreateTextureFromFile(pDevice, "data\\TOOL\\TEXTURE\\Tool_Enemy_3WDown.png", &m_ptex);	//敵_3W_Down
			B_Height = 20;
			B_Width = 10;
			break;

		case 18:
			D3DXCreateTextureFromFile(pDevice, "data\\TOOL\\TEXTURE\\Tool_Enemy_3WLeft.png", &m_ptex);	//敵_3W_Left
			B_Height = 20;
			B_Width = 10;
			break;

		case 19:
			D3DXCreateTextureFromFile(pDevice, "data\\TOOL\\TEXTURE\\Tool_Enemy_3WRight.png", &m_ptex);	//敵_3W_Right
			B_Height = 20;
			B_Width = 10;
			break;

		default:
			break;
		}

		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0 - B_Width, 0 + B_Height, 0);
		pVtx[1].pos = D3DXVECTOR3(0 + B_Width, 0 + B_Height, 0);
		pVtx[2].pos = D3DXVECTOR3(0 - B_Width, 0, 0);
		pVtx[3].pos = D3DXVECTOR3(0 + B_Width, 0, 0);

		//法線ベクトル
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//頂点カラー設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, .7f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, .7f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, .7f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, .7f);

		//テクスチャ座標
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
//描画
==================================*/
void CTP_img::Draw()
{
	if (IsUse == true)
	{
		CB_board::Draw();
	}
}

/*==================================
//生成・取得
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
//セーブロード
=================================================*/

/*======================================
//コンストラクタ・デストラクタ
=======================================*/
CTP_SaveLoad::CTP_SaveLoad()
{

}

CTP_SaveLoad::~CTP_SaveLoad()
{

}

/*=====================================
//セーブ
=====================================*/
void CTP_SaveLoad::Save()
{
	int DataNum = CTP_img::GetImgNum() - 1;
	CTP_img* Img[Place_M] = {};
	for (int i = 0; i < Place_M; i++)
	{
		Img[i] = Img[i]->Getimg(i);
	}
	//画像番号、位置を外部ファイルに記録
	ofstream SaveData("data\\TOOL\\SAVE\\Stage_XX.txt");
	if (SaveData.is_open())
	{
		SaveData << DataNum << endl;	//データ数
		for (int Data = 0; Data < DataNum; Data++)
		{
			SaveData << Img[Data]->ImgNum << endl;	//画像番号
			SaveData << Img[Data]->m_pos.x << endl;	//位置X
			SaveData << Img[Data]->m_pos.y << endl;	//位置Y
			SaveData << Img[Data]->m_pos.z << endl;	//位置Z
		}
		SaveData.close();
	}

}

/*=====================================
//ロード
=====================================*/
void CTP_SaveLoad::Load()
{
	int DataNum = 0,ImgNum = 0;
	float PosX = 0, PosY = 0, PosZ = 0;
	
	//記録したものを種類ごとにロード
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

