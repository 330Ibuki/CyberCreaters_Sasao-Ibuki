/*==========================
#
# 
#
#
============================*/

//インクルード
#include "billboard.h"
#include "input.h"



//静的メンバ初期化
CB_board* CB_board::ItemBase[MITEM] = {};
int CB_board::ItemAll = NULL;

/*=============================
#コンストラクタ・デストラクタ
==============================*/

CB_board::CB_board(int nPriority):CObjectX(m_Priority)
{
	IsUse = true;

	B_Height = NULL;
	B_Width = NULL;
	m_pVtxBuff = nullptr;
	m_ptex = nullptr;
	ItemAll++;
}

CB_board::~CB_board()
{
	ItemAll--;
}

/*=============================
#初期化
==============================*/
HRESULT CB_board::Init()
{

	VERTEX_3D* pVtx;
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\scope_test_3.png",
		&m_ptex);

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
	pVtx[2].pos = D3DXVECTOR3(0 - B_Width, 0 - B_Height, 0);
	pVtx[3].pos = D3DXVECTOR3(0 + B_Width, 0 - B_Height, 0);

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

/*=============================
#終了
==============================*/

void CB_board::Uninit()
{
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

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

	//CObjectX::Uninit();

}

/*=============================
#更新
==============================*/

void CB_board::Update()
{
	CInputKeyboard* pKeyBoard = CManager::GetKeyboard();
	CPlayerX* pPlayerX = CPlayerX::GetPlayer();
	if (pKeyBoard->GetPress(DIK_W) == true)
	{
		m_pos.y += 2.5;
	}

	if (pKeyBoard->GetPress(DIK_S) == true)
	{
		m_pos.y += -2.5;
	}

	if (pKeyBoard->GetPress(DIK_A) == true)
	{
		m_pos.x += -2.5;
	}

	if (pKeyBoard->GetPress(DIK_D) == true)
	{
		m_pos.x += 2.5;
	}
}

/*=============================
#描画
==============================*/

void CB_board::Draw()
{
	//デバイス取得
	CRenderer* pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス

	//pDevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
	//	D3DCOLOR_XRGB(0, 0, 0), 0.9f, 0);

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
	//pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	/*pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);*/
}

/*=============================
#取得
==============================*/

//CB_board* CB_board::GetItem(int I_Num)
//{
//	return ItemBase[I_Num];
//}

int CB_board::GetItemAll()
{
	return ItemAll;
}

/*=============================
#生成
==============================*/

//CB_board* CB_board::Create(D3DXVECTOR3 pos)
//{
//	int INum = CB_board::GetItemAll();
//
//	if (ItemBase[INum] == nullptr)
//	{
//		ItemBase[INum] = new CB_board();
//
//		ItemBase[INum]->IsUse = true;
//		ItemBase[INum]->B_Height = 10.0f;
//		ItemBase[INum]->B_Width = 10.0f;
//		ItemBase[INum]->m_pos = pos;
//
//		ItemBase[INum]->Init();
//
//	}
//
//	return ItemBase[INum];
//}

/*=============================
#
==============================*/