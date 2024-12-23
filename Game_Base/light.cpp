/*=============================================
//
// C++ポリゴン描画
// Author: Sasao Ibuki
//
==============================================*/

//インクルード
#include "light.h"
#include "renderer.h"
#include "manager.h"

/*==============================
//コンストラクタ・デストラクタ
==============================*/

CLight::CLight()
{
	for (int i = 0; i < LIGHT; i++)
	{
		ZeroMemory(&m_aLight[i], sizeof(D3DLIGHT9));
	}
}

CLight::~CLight()
{

}

/*============================
//初期設定
============================*/

HRESULT CLight::Init()
{
	//デバイスの取得
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	D3DXVECTOR3 vecDir[LIGHT] = {};	//設定用

	//方向設定
	vecDir[0] = D3DXVECTOR3(0.2f, -0.4f, 1.0f);
	vecDir[1] = D3DXVECTOR3(0.2f, 0.6f, 1.0f);
	vecDir[2] = D3DXVECTOR3(0.0f, -0.4f, 0.3f);

	for (int i = 0; i < LIGHT; i++)
	{
		//種類
		m_aLight[i].Type = D3DLIGHT_DIRECTIONAL;

		//拡散光
		m_aLight[i].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//方向設定
		D3DXVec3Normalize(&vecDir[i], &vecDir[i]);


		m_aLight[i].Direction = vecDir[i];

		//設定する
		pDevice->SetLight(0, &m_aLight[i]);

		pDevice->LightEnable(0, TRUE);
	}

	return S_OK;
}

/*============================
//終了
============================*/

void CLight::Uninit()
{

}

/*============================
//更新
============================*/

void CLight::Update()
{
	//現状なし
}