/*=======================
//ModelParts
=======================*/

//include
#include"modelparts.h"
#include "renderer.h"
#include "manager.h"

CModelParts* CModelParts::m_pModelParts[PARTLIM] = {};
int CModelParts::PartNum = NULL;

/*========================
//コンストラクタ・デストラクタ
========================*/
CModelParts::CModelParts()
{
	m_pos = {};
	/*m_posOld = {};*/
	m_rot = {};
	m_pVtxBuff = nullptr;
	m_ptex = nullptr;
	m_dwNumMat = {};
	m_pBuffMat = {};
	m_pMesh = {};
	m_pParent = nullptr;
	PartsName[FILENAME] = {};
	PartNum++;
	P_Num = NULL;
}

CModelParts::~CModelParts()
{
	PartNum--;
}

/*==========================
//初期化
===========================*/
HRESULT CModelParts::Init()
{
	//デバイス取得
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//パラメータの初期設定
	m_rot = D3DXVECTOR3(NULL, NULL, NULL);

	//X読み込み
	D3DXLoadMeshFromX(
		(char*)PartsName,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_dwNumMat,
		&m_pMesh);

	//マテリアルデータのポインタ取得
	D3DXMATERIAL* mat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (DWORD i = 0; i < m_dwNumMat; i++)
	{
		if (mat[i].pTextureFilename != NULL)
		{
			char* TexName = mat[i].pTextureFilename;
			D3DXCreateTextureFromFileA(pDevice,
				TexName,
				&m_ptex);
		}

		else
		{
			m_ptex = nullptr;
		}
	}

	return S_OK;
}

/*==========================
//破棄
==========================*/
void CModelParts::Uninit()
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

	
}

/*==========================
//更新
==========================*/
void CModelParts::Update()
{

}

/*==========================
//描画
==========================*/
void CModelParts::Draw()
{
	//デバイス取得
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans, mtxParent;	//計算用マトリックス
	D3DMATERIAL9 matDef;			//マテリアル保存用
	D3DXMATERIAL* pMat;				//マテリアルデータへのポインタ

	pDevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	//ワールドマトリックス初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//ワールド変換行列の作成

	//向きの反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		m_rot.y, m_rot.x, m_rot.z);

	//位置の反映
	D3DXMatrixTranslation(&mtxTrans,
		m_pos.x, m_pos.y, m_pos.z);

	if (m_pParent != nullptr)
	{//親の行列を取得
		mtxParent = m_pParent->m_mtxWorld;
	}

	else
	{//最新のワールド行列を取得
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

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
		m_pModelParts[P_Num]->m_pMesh->DrawSubset(i);

		pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	}

	//マテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

/*==========================
//取得・生成
==========================*/
int CModelParts::GetPartsNum()
{
	return PartNum;
}

CModelParts* CModelParts::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,char* PartsName,int PartsNum)
{
	int Parts = GetPartsNum();

	if (m_pModelParts[Parts] == nullptr)
	{
		m_pModelParts[Parts] = new CModelParts();
		m_pModelParts[Parts]->m_pos = pos;
		m_pModelParts[Parts]->m_rot = rot;
		m_pModelParts[Parts]->m_pBuffMat = nullptr;
		m_pModelParts[Parts]->m_pMesh = nullptr;
		m_pModelParts[Parts]->m_ptex = nullptr;
		m_pModelParts[Parts]->m_pVtxBuff = nullptr;
		m_pModelParts[Parts]->m_pParent = nullptr;
		m_pModelParts[Parts]->P_Num = PartsNum;
		strcpy(m_pModelParts[Parts]->PartsName, (char*)PartsName);
		m_pModelParts[Parts]->Init();
	}

	return m_pModelParts[Parts];
}

/*==========================
//親の設定
==========================*/
void CModelParts::SetParent(CModelParts* pParent)
{
	m_pParent = pParent;
}