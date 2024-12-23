/*=============================================
//
// C++ポリゴン描画
// Author: Sasao Ibuki
//
==============================================*/

//インクルード
#include "objectx.h"
#include "renderer.h"
#include "manager.h"
#include "collision.h"

//静的メンバ初期化
CObjectX* CObjectX::m_apObjectX[MOBJ] = {};

/*=====================================
//コンストラクタ・デストラクタ
=====================================*/

CObjectX::CObjectX(int nPriority) : CObject(m_Priority)
{
	m_pos = {};
	m_posOld = {};
	m_rot = {};
	m_pVtxBuff = nullptr;
	m_ptex = nullptr;
	m_dwNumMat = {};
	m_pBuffMat = {};
	m_pMesh = {};
	OnCol = false;
	m_bDeath = false;
	m_Priority = nPriority;
	m_Flame_Count = NULL;
	OBJ_ID = NULL;
}

CObjectX::~CObjectX()
{

}

/*====================================
//初期設定
====================================*/

HRESULT CObjectX::Init()
{
	//デバイス取得
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//パラメータの初期設定
	m_rot = D3DXVECTOR3(NULL,NULL,NULL);

	//X読み込み
	D3DXLoadMeshFromX(
		"data\\MODEL\\box_test.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_dwNumMat,
		&m_pMesh);


	//マテリアルデータのポインタ取得


	return S_OK;
}

/*====================================
//破棄
====================================*/

void CObjectX::Uninit()
{
	if (m_pMesh != nullptr)
	{
		m_pMesh->Release();
		m_pMesh = nullptr;
	}

	if (m_pBuffMat != nullptr)
	{
		m_pBuffMat->Release();
		m_pBuffMat = nullptr;
	}

	if (m_ptex != nullptr)
	{
		m_ptex->Release();
		m_ptex = nullptr;
	}

	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
	this->Release();
}

/*====================================
//更新
====================================*/

void CObjectX::Update()
{

}

/*====================================
//描画
====================================*/

void CObjectX::Draw()
{
	//デバイス取得
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	D3DMATERIAL9 matDef;			//マテリアル保存用
	D3DXMATERIAL* pMat;				//マテリアルデータへのポインタ

	//pDevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
	//	D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	//ワールドマトリックス初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//ワールド変換行列の作成

	//向きの反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		m_rot.y, m_rot.x, m_rot.z);

	//位置の反映
	D3DXMatrixTranslation(&mtxTrans,
		m_pos.x, m_pos.y, m_pos.z);

	//ワールド変換行列の設定
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックス設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//マテリアル取得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタ取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();


	for (int i = 0; i < (int)m_dwNumMat; i++)
	{
		//マテリアル設定
		pDevice->SetMaterial(&pMat[i].MatD3D);

		//テクスチャ設定
		pDevice->SetTexture(0, m_ptex);

		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
		pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
		//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

		//モデル描画
		m_pMesh->DrawSubset(i);

		pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	}

	//マテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

/*====================================
//生成
====================================*/

//CObjectX* CObjectX::Create(D3DXVECTOR3 pos)
//{
//	int BCnt = CObjectX::GetNumBlock();
//
//	if (m_apObjectX[BCnt] == nullptr)
//	{
//		m_apObjectX[BCnt] = new CObjectX();
//		m_apObjectX[BCnt]->m_pos = pos;
//		m_apObjectX[BCnt]->Init();
//	}
//
//	return m_apObjectX[BCnt];
//}

/*====================================
//取得
====================================*/



CObjectX* CObjectX::Getobj(int B_Num)
{
	
	return m_apObjectX[B_Num];
}

/*====================================
//
====================================*/



/*====================================
//
====================================*/