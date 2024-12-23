/*===================================
//
//	UI
//
===================================*/

//インクルード
#include "UI.h"
#include "manager.h"
#include "renderer.h"
#include "player.x.h"

//静的メンバ初期化
CUI* CUI::m_UI[2] = {};
int CUI::UINum = NULL;

/*=========================
//コンストラクタ・デストラクタ
=========================*/
CUI::CUI() : CB_board(m_Priority = 4)
{
	UI_type = NULL;
	UI_A = 1.0f;
	UINum++;
	A_Reduction = true;
}

CUI::~CUI()
{
	UINum--;
}

/*============================
//初期化
=============================*/
HRESULT CUI::Init()
{
	VERTEX_3D* pVtx;
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	if (UI_type == UI_LIFE)
	{
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\UI_LIFE.png",
			&m_ptex);
	}

	else if (UI_type == UI_SCORE)
	{
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\UI_SCORE.png",
			&m_ptex);
	}

	else if (UI_type == UI_S_GUIDE)
	{
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\UI_S_GUIDE.png",
			&m_ptex);
	}

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0 - B_Width, 0 + B_Height, -50);
	pVtx[1].pos = D3DXVECTOR3(0 + B_Width, 0 + B_Height, -50);
	pVtx[2].pos = D3DXVECTOR3(0 - B_Width, 0 - B_Height, -50);
	pVtx[3].pos = D3DXVECTOR3(0 + B_Width, 0 - B_Height, -50);


	//法線ベクトル
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//頂点カラー設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, UI_A);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, UI_A);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, UI_A);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, UI_A);

	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	m_pVtxBuff->Unlock();
	return S_OK;
}

/*==========================
//破棄
==========================*/
void CUI::Uninit()
{
	CB_board::Uninit();
}

/*=========================
//更新
==========================*/
void CUI::Update()
{
	if (IsUse == true)
	{
		VERTEX_3D* pVtx;
		CPlayerX* pPlayerX = pPlayerX->GetPlayer();

		if (UI_type == UI_LIFE)
		{
			m_pos.x = pPlayerX->m_pos.x - 90;
			m_pos.y = pPlayerX->m_pos.y - 60;
		}

		else if (UI_type == UI_SCORE)
		{
			m_pos.x = pPlayerX->m_pos.x + 100;
			m_pos.y = pPlayerX->m_pos.y - 60;
		}

		else if(UI_type == UI_S_GUIDE)
		{
			m_Flame_Count++;
			if (m_Flame_Count % 5 == 0)
			{
				if (A_Reduction == true)
				{
					UI_A -= 0.1;
					if (UI_A <= 0.0f)
					{
						UI_A = 0.0f;
						A_Reduction = false;
					}
				}

				else
				{
					UI_A += 0.1;
					if (UI_A >= 1.0f)
					{
						UI_A = 1.0f;
						A_Reduction = true;
					}
				}
			}

			m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, UI_A);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, UI_A);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, UI_A);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, UI_A);
			m_pVtxBuff->Unlock();
		}
	}

	else
	{
		CUI::Uninit();
	}
}

/*============================
//描画
============================*/
void CUI::Draw()
{
	if (IsUse == true)
	{
		CB_board::Draw();
	}
}

/*===========================
//各種取得
===========================*/
CUI* CUI::GetUI(int num)
{
	return m_UI[num];
}

int CUI::GetUINum()
{
	return UINum;
}

/*============================
//生成
=============================*/

CUI* CUI::Create(D3DXVECTOR3 pos, UType type)
{
	int UI_Num = CUI::GetUINum();
	if (m_UI[UI_Num] != nullptr)
	{
		m_UI[UI_Num] = nullptr;
	}

	if (m_UI[UI_Num] == nullptr/* && UI_Num < 2*/)
	{
		m_UI[UI_Num] = new CUI();
		m_UI[UI_Num]->m_pos = pos;
		m_UI[UI_Num]->UI_type = type;
		m_UI[UI_Num]->IsUse = true;
		m_UI[UI_Num]->B_Width = 60;
		m_UI[UI_Num]->B_Height = 25;

		m_UI[UI_Num]->Init();
	}
	return m_UI[UI_Num];
}