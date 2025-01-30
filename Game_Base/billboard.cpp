/*==========================
#
# 
#
#
============================*/

//�C���N���[�h
#include "billboard.h"
#include "input.h"



//�ÓI�����o������
CB_board* CB_board::ItemBase[MITEM] = {};
int CB_board::ItemAll = NULL;

/*=============================
#�R���X�g���N�^�E�f�X�g���N�^
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
#������
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

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0 - B_Width, 0 + B_Height, 0);
	pVtx[1].pos = D3DXVECTOR3(0 + B_Width, 0 + B_Height, 0);
	pVtx[2].pos = D3DXVECTOR3(0 - B_Width, 0 - B_Height, 0);
	pVtx[3].pos = D3DXVECTOR3(0 + B_Width, 0 - B_Height, 0);

	//�@���x�N�g��
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�J���[�ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, .7f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, .7f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, .7f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, .7f);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	m_pVtxBuff->Unlock();
	return S_OK;
}

/*=============================
#�I��
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
#�X�V
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
#�`��
==============================*/

void CB_board::Draw()
{
	//�f�o�C�X�擾
	CRenderer* pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	//pDevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
	//	D3DCOLOR_XRGB(0, 0, 0), 0.9f, 0);

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//���[���h�ϊ��s��̍쐬

	//�����̔��f
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		m_rot.y, m_rot.x, m_rot.z);

	//�ʒu�̔��f
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

	//���[���h�ϊ��s��̐ݒ�
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &B_View);

	D3DXMatrixMultiply(&m_mtxWorld, &B_View, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���֐ݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_ptex);

	//�|���S���̕`��
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	//pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	/*pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);*/
}

/*=============================
#�擾
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
#����
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