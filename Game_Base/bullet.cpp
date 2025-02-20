/*=============================================
//
// C++�|���S���`��
// Author: Sasao Ibuki
//
==============================================*/

//�C���N���[�h
#include "bullet.h"
#include "renderer.h"
#include "player.x.h"
#include "scope.h"
#include "manager.h"

//�ÓI�����o������
CBullet* CBullet::m_pBullets[MBULLET] = {};
int CBullet::BulletNum = NULL;

/*=================================
//�R���X�g���N�^�E�f�X�g���N�^
=================================*/

CBullet::CBullet() : CB_board(m_Priority = 5)
{
	IsPlayer = false;
	IsUse = false;
	IsChase = false;
	Pos = {};
	Dest = {};
	Move = {};
	Life = NULL;
	B_Height = 10.0f;
	B_Width = 10.0f;
	BulletNum++;
	//if (BulletNum > MBULLET)
	//{
	//	BulletNum = 0;
	//}
}

CBullet::~CBullet()
{
	BulletNum--;
}

/*====================
//������
====================*/

HRESULT CBullet::Init()
{
	//�f�o�C�X�擾
	VERTEX_3D* pVtx;
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	if (IsPlayer == true)
	{
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\Bullet_test.png",
			&m_ptex);
	}

	else
	{
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\Bullet_Enemy.png",
			&m_ptex);
	}


	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0 - B_Width, 0 + B_Height, -60);
	pVtx[1].pos = D3DXVECTOR3(0 + B_Width, 0 + B_Height, -60);
	pVtx[2].pos = D3DXVECTOR3(0 - B_Width, 0 - B_Height, -60);
	pVtx[3].pos = D3DXVECTOR3(0 + B_Width, 0 - B_Height, -60);

	//�@���x�N�g��
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�J���[�ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	m_pVtxBuff->Unlock();

	//�v�Z
	

	return S_OK;
}

/*====================
//�I��
====================*/

void CBullet::Uninit()
{
	CB_board::Uninit();

	//Release();

}

/*====================
//�X�V����
====================*/

void CBullet::Update()
{
	if (IsUse == false)
	{
		Uninit();
	}

	if (IsUse == true)
	{
		m_Flame_Count++;
		if (m_Flame_Count % 60 == 0)
		{
			Life--;

			if (Life <= 0)
			{
				IsUse = false;
			}
		}
		m_pos.x += move.x;
		m_pos.y += move.y;
		m_pos.z += move.z;
	}

}

/*====================
//�`�揈��
====================*/

void CBullet::Draw()
{
	if (IsUse == true)
	{
		CB_board::Draw();
	}
	
}

/*====================
//�擾�E����
====================*/

CBullet* CBullet::GetBullet(int Num)
{
	return m_pBullets[Num];
}

int CBullet::GetBulletNum()
{
	return BulletNum;
}

CBullet* CBullet::Create(D3DXVECTOR3 PLpos, D3DXVECTOR3 Dest, D3DXVECTOR3 Move, bool IsPlayer, bool IsChased)
{
	int B_Num = CBullet::GetBulletNum();
	float Cos = NULL, Sin = NULL;
	Cos = Dest.x - PLpos.x;
	Sin = Dest.y - PLpos.y;
	float Radian = atan2f(Sin, Cos);

	if (m_pBullets[B_Num] != nullptr)
	{
		m_pBullets[B_Num] = nullptr;
	}

	if (m_pBullets[B_Num] == nullptr)
	{
		m_pBullets[B_Num] = new CBullet();
 		m_pBullets[B_Num]->m_pos = PLpos;
		m_pBullets[B_Num]->Dest = Dest;
		m_pBullets[B_Num]->IsChase = IsChased;
		if (m_pBullets[B_Num]->IsChase == true)
		{
			m_pBullets[B_Num]->move.x = cosf(Radian);
			m_pBullets[B_Num]->move.y = sinf(Radian);
		}
		else
		{
			m_pBullets[B_Num]->move.x = Move.x;
			m_pBullets[B_Num]->move.y = Move.y;
		}
	
		m_pBullets[B_Num]->move.z = 0;
		m_pBullets[B_Num]->IsPlayer = IsPlayer;
		m_pBullets[B_Num]->IsUse = true;
		m_pBullets[B_Num]->Life = 1;
		m_pBullets[B_Num]->OBJ_ID = B_Num;
		m_pBullets[B_Num]->Init();
	}

	return m_pBullets[B_Num];
}
