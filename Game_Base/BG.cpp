/*===================================
//
//	UI
//
===================================*/

//インクルード
#include "BG.h"
#include "manager.h"
#include "renderer.h"
#include "player.x.h"

//静的メンバ初期化
CBG* CBG::m_BG = nullptr;
int CBG::BGNum = NULL;

/*=========================
//コンストラクタ・デストラクタ
=========================*/
CBG::CBG() : CB_board(m_Priority = 3)
{
	B_Type = NULL;
	/*IsGame = false;*/
	BGNum++;
}

CBG::~CBG()
{
	BGNum--;
}

/*============================
//初期化
=============================*/
HRESULT CBG::Init()
{
	VERTEX_3D* pVtx;
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	if (B_Type == BG_GAME)
	{
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\seamless_19.png",
			&m_ptex);
	}

	else if (B_Type == BG_TITLE)
	{
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\Title_test.png",
			&m_ptex);
	}

	else if (B_Type == BG_RESULT)
	{
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\seamless_19.png",
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
	if (B_Type == BG_GAME)
	{
		pVtx[0].pos = D3DXVECTOR3(0 - (500), 0 + (500), 100);
		pVtx[1].pos = D3DXVECTOR3(0 + (500), 0 + (500), 100);
		pVtx[2].pos = D3DXVECTOR3(0 - (500), 0 - (500), 100);
		pVtx[3].pos = D3DXVECTOR3(0 + (500), 0 - (500), 100);
	}

	else
	{
		pVtx[0].pos = D3DXVECTOR3(0 - (170), 0 + (170), 30);
		pVtx[1].pos = D3DXVECTOR3(0 + (170), 0 + (170), 30);
		pVtx[2].pos = D3DXVECTOR3(0 - (170), 0 - (170), 30);
		pVtx[3].pos = D3DXVECTOR3(0 + (170), 0 - (170), 30);
	}

	////法線ベクトル
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//頂点カラー設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

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
void CBG::Uninit()
{
	CB_board::Uninit();
	Release();
}

/*=========================
//更新
==========================*/
void CBG::Update()
{
	if (IsUse == false)
	{
	CBG::Uninit();
	}

	else
	{
		if (B_Type == BG_GAME)
		{
			CPlayerX* player = player->GetPlayer();
			m_pos.x = player->m_pos.x;
			m_pos.y = player->m_pos.y;
		}
	}
}

/*============================
//描画
============================*/
void CBG::Draw()
{
	if (IsUse == true)
	{
		//デバイス取得
		CRenderer* pRenderer = CManager::GetRenderer();

		LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

		D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス

		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&m_mtxWorld);

		//ワールド変換行列の作成

		//向きの反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			m_rot.y, m_rot.x, m_rot.z);

		//位置の反映
		D3DXMatrixTranslation(&mtxTrans,
			m_pos.x, m_pos.y, m_pos.z);

		pDevice->GetTransform(D3DTS_VIEW, &B_View);
		D3DXMatrixInverse(&B_View, nullptr, &B_View);
		B_View._11 = 1.0f;
		B_View._12 = 0.0f;
		B_View._13 = 0.0f;
		B_View._41 = 0.0f;
		B_View._42 = 0.0f;
		B_View._43 = 0.0f;

		//ワールド変換行列の設定
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &B_View);

		D3DXMatrixMultiply(&m_mtxWorld, &B_View, &mtxTrans);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

		//頂点バッファをデータストリームへ設定
		pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		//テクスチャの設定
		pDevice->SetTexture(0, m_ptex);

		//ポリゴンの描画
		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
		pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}

/*===========================
//各種取得
===========================*/
CBG* CBG::GetBG()
{
	return m_BG;
}

int CBG::GetBGNum()
{
	return BGNum;
}

/*============================
//生成
=============================*/

CBG* CBG::Create(BG_Type type/*, bool Game*/)
{
	int UI_Num = CBG::GetBGNum();

	if (m_BG != nullptr)
	{
		m_BG = nullptr;
		m_BG = new CBG();
		m_BG->B_Type = type;
		//m_BG->IsGame = Game;
		m_BG->IsUse = true;
		m_BG->Init();
	}

	else if (m_BG == nullptr/* && UI_Num < 2*/)
	{
		m_BG = new CBG();
		m_BG->B_Type = type;
		//m_BG->IsGame = Game;
		m_BG->IsUse = true;
		m_BG->Init();
	}
	return m_BG;
}