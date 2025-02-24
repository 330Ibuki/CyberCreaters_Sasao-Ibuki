/*=============================================
//
// C++ポリゴン描画
// Author: Sasao Ibuki
//
==============================================*/

//インクルード
#include "camera.h"
#include "manager.h"
#include "renderer.h"
#include "tool.h"
#include "player.x.h"
#include "BG.h"

/*=============================
//コンストラクタ・デストラクタ
=============================*/

CCamera::CCamera()
{
	m_PosR = D3DXVECTOR3(NULL, NULL, NULL);
	m_PosV = D3DXVECTOR3(NULL, NULL, NULL);
	m_PosU = D3DXVECTOR3(NULL, NULL, NULL);
	m_Length = 0.0f;
}

CCamera::~CCamera()
{

}

/*============================
//初期設定
============================*/

HRESULT CCamera::Init()
{

	m_PosV = D3DXVECTOR3(0.0f, 00.0f, -200.0f);		//視点
	m_PosR = D3DXVECTOR3(0.0f, 10.0f, 0.0f);		//注視点
	m_PosU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);			//上方向ベクトル
	m_Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	return S_OK;
}

/*===========================
//終了
===========================*/

void CCamera::Uninit()
{

}

/*===========================
//更新
===========================*/

void CCamera::Update()
{
	CBG* pBG = pBG->GetBG();
	
		if (pBG->B_Type == CBG::BG_Type::BG_GAME)
		{
			CPlayerX* pPlayerX = pPlayerX->GetPlayer();
			m_PosR.x = pPlayerX->m_pos.x + 5;
			m_PosR.y = pPlayerX->m_pos.y + 0;
			m_PosR.z = pPlayerX->m_pos.z;

			m_PosV.x = pPlayerX->m_pos.x - 0;
			m_PosV.y = pPlayerX->m_pos.y + 40;
			m_PosV.z = pPlayerX->m_pos.z - 200;
		}

		else if (pBG->B_Type == CBG::BG_Type::BG_TITLE || pBG->B_Type == CBG::BG_Type::BG_RESULT)
		{
			m_PosR.x = 0;
			m_PosR.y = 0;
			m_PosR.z = 0;

			m_PosV.x = 0;
			m_PosV.y = 0;
			m_PosV.z = -100;
		}

	else
	{	
			CToolPlace* Tool = Tool->GetTool();
			m_PosR.x = Tool->B_pos.x;
			m_PosR.y = Tool->B_pos.y + 50;
			m_PosR.z = Tool->B_pos.z;

			m_PosV.x = Tool->B_pos.x;
			m_PosV.y = Tool->B_pos.y + 50;
			m_PosV.z = Tool->B_pos.z - 200;
	}
}

/*===========================
//設定
===========================*/

void CCamera::SetCamera()
{
	//デバイスの取得
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//プロジェクションの初期化、生成、設定

	//初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	//生成
	D3DXMatrixOrthoLH(
		&m_mtxProjection,
		(float)SCREEN_WIDTH / 4,
		(float)SCREEN_HEIGHT / 4,
		1.0f,
		1000.0f
	);

	//設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	//ビューの初期化、生成、設定

	//初期化
	D3DXMatrixIdentity(&m_mtxView);

	//生成
	D3DXMatrixMultiply(&m_mtxProjection, &m_mtxProjection, &m_mtxView);

	D3DXMatrixLookAtLH(
		&m_mtxView,
		&m_PosV,	//視点
		&m_PosR,	//注視点
		&m_PosU		//上方向ベクトル
	);

	//設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

}