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
#include "player.x.h"

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
	CPlayerX* pPlayerX = pPlayerX->GetPlayer();
	if (pPlayerX != nullptr)
	{
		m_PosR.x = pPlayerX->m_pos.x + 5;
		m_PosR.y = pPlayerX->m_pos.y + 0;
		m_PosR.z = pPlayerX->m_pos.z;

		m_PosV.x = pPlayerX->m_pos.x - 0;
		m_PosV.y = pPlayerX->m_pos.y + 40;
		m_PosV.z = pPlayerX->m_pos.z - 200;
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