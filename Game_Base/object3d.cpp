/*=============================================
//
// C++ポリゴン描画
// Author: Sasao Ibuki
//
==============================================*/

//インクルード
#include "object3d.h"
#include "renderer.h"
#include "manager.h"

//静的メンバ初期化
CObject3D* CObject3D::m_apObject3D = nullptr;

/*============================
//コンストラクタ・デストラクタ
============================*/

CObject3D::CObject3D() : CObject(2)
{
	m_ptex = nullptr;
	m_pos = D3DXVECTOR3(NULL, NULL, NULL);
	m_rot = D3DXVECTOR3(NULL, NULL, NULL);
	m_pVtxBuff = nullptr;
}

CObject3D::~CObject3D()
{

}

/*==============================
//初期設定
==============================*/

HRESULT CObject3D::Init()
{
	//デバイス取得
	VERTEX_3D* pVtx;
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	m_rot = D3DXVECTOR3(NULL, NULL, NULL);

	//テクスチャ
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\seamless_55.png",
		&m_ptex);

	//頂点バッファ
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-100.0f, 0.0f, 100.0f);
	pVtx[1].pos = D3DXVECTOR3(100.0f, 0.0f, 100.0f);
	pVtx[2].pos = D3DXVECTOR3(-100.0f, 0.0f, -100.0f);
	pVtx[3].pos = D3DXVECTOR3(100.0f, 0.0f, -100.0f);

	//法線ベクトル
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

/*==============================
//破棄
==============================*/

void CObject3D::Uninit()
{
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	if (m_ptex != nullptr)
	{
		m_ptex->Release();
		m_ptex = nullptr;
	}
}

/*==============================
//更新
==============================*/

void CObject3D::Update()
{

}

/*==============================
//描画
==============================*/

void CObject3D::Draw()
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

	//ワールド変換行列の設定
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点バッファをデータストリームへ設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_ptex);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

/*==============================
//ロード
==============================*/



/*==============================
//アンロード
==============================*/



/*==============================
//生成
==============================*/

CObject3D* CObject3D::Create(D3DXVECTOR3 pos)
{
	if (m_apObject3D == nullptr)
	{
		m_apObject3D = new CObject3D();
		m_apObject3D->m_pos = pos;
		m_apObject3D->Init();
	}

	return m_apObject3D;
}