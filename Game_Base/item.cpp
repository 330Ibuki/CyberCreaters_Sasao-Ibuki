/*=============================
item
==============================*/

//include
#include "item.h"

//�ÓI�����o������
CItem* CItem::m_Item[INUM_MAX] = {};
int CItem::ItemNum = NULL;

/*===========================
�R���X�g���N�^�E�f�X�g���N�^
===========================*/
CItem::CItem() : CB_board(m_Priority = 4)
{
	Item_type = NULL;
	ItemNum++;
}

CItem::~CItem()
{
	ItemNum--;
}

/*===========================
������
===========================*/
HRESULT CItem::Init()
{
	VERTEX_3D* pVtx;
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Item_test.png",
		&m_ptex);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0 - B_Width, 0 + B_Height, -50);
	pVtx[1].pos = D3DXVECTOR3(0 + B_Width, 0 + B_Height, -50);
	pVtx[2].pos = D3DXVECTOR3(0 - B_Width, 0 - B_Height, -50);
	pVtx[3].pos = D3DXVECTOR3(0 + B_Width, 0 - B_Height, -50);

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

/*===========================
�j��
===========================*/
void CItem::Uninit()
{
	CB_board::Uninit();
}

/*===========================
�X�V
===========================*/
void CItem::Update()
{
	if (IsUse == false)
	{
		CItem::Uninit();
	}
}

/*===========================
�`��
===========================*/
void CItem::Draw()
{
	//if (IsUse == true)
	//{
		CB_board::Draw();
	//}
}

/*===========================
�擾
===========================*/
CItem* CItem::GetItem(int num)
{
	return m_Item[num];
}

int CItem::GetItemNum()
{
	return ItemNum;
}

/*===========================
����
===========================*/
CItem* CItem::Create(D3DXVECTOR3 pos, ITEM type)
{
	int I_Num = GetItemNum();
	if (m_Item[I_Num] != nullptr)
	{
		m_Item[I_Num] = nullptr;
	}

	if (m_Item[I_Num] == nullptr)
	{
		m_Item[I_Num] = new CItem();
		m_Item[I_Num]->IsUse = true;
		m_Item[I_Num]->m_pos = pos;
		m_Item[I_Num]->Item_type = type;
		m_Item[I_Num]->B_Width = 10.0f;
		m_Item[I_Num]->B_Height = 10.0f;
		m_Item[I_Num]->Init();
	}

	return m_Item[I_Num];
}