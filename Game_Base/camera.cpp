/*=============================================
//
// C++�|���S���`��
// Author: Sasao Ibuki
//
==============================================*/

//�C���N���[�h
#include "camera.h"
#include "manager.h"
#include "renderer.h"
#include "player.x.h"

/*=============================
//�R���X�g���N�^�E�f�X�g���N�^
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
//�����ݒ�
============================*/

HRESULT CCamera::Init()
{

	m_PosV = D3DXVECTOR3(0.0f, 00.0f, -200.0f);		//���_
	m_PosR = D3DXVECTOR3(0.0f, 10.0f, 0.0f);		//�����_
	m_PosU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);			//������x�N�g��
	m_Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	return S_OK;
}

/*===========================
//�I��
===========================*/

void CCamera::Uninit()
{

}

/*===========================
//�X�V
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
//�ݒ�
===========================*/

void CCamera::SetCamera()
{
	//�f�o�C�X�̎擾
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�v���W�F�N�V�����̏������A�����A�ݒ�

	//������
	D3DXMatrixIdentity(&m_mtxProjection);

	//����
	D3DXMatrixOrthoLH(
		&m_mtxProjection,
		(float)SCREEN_WIDTH / 4,
		(float)SCREEN_HEIGHT / 4,
		1.0f,
		1000.0f
	);

	//�ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	//�r���[�̏������A�����A�ݒ�

	//������
	D3DXMatrixIdentity(&m_mtxView);

	//����
	D3DXMatrixMultiply(&m_mtxProjection, &m_mtxProjection, &m_mtxView);

	D3DXMatrixLookAtLH(
		&m_mtxView,
		&m_PosV,	//���_
		&m_PosR,	//�����_
		&m_PosU		//������x�N�g��
	);

	//�ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

}