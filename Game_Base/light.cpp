/*=============================================
//
// C++�|���S���`��
// Author: Sasao Ibuki
//
==============================================*/

//�C���N���[�h
#include "light.h"
#include "renderer.h"
#include "manager.h"

/*==============================
//�R���X�g���N�^�E�f�X�g���N�^
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
//�����ݒ�
============================*/

HRESULT CLight::Init()
{
	//�f�o�C�X�̎擾
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	D3DXVECTOR3 vecDir[LIGHT] = {};	//�ݒ�p

	//�����ݒ�
	vecDir[0] = D3DXVECTOR3(0.2f, -0.4f, 1.0f);
	vecDir[1] = D3DXVECTOR3(0.2f, 0.6f, 1.0f);
	vecDir[2] = D3DXVECTOR3(0.0f, -0.4f, 0.3f);

	for (int i = 0; i < LIGHT; i++)
	{
		//���
		m_aLight[i].Type = D3DLIGHT_DIRECTIONAL;

		//�g�U��
		m_aLight[i].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�����ݒ�
		D3DXVec3Normalize(&vecDir[i], &vecDir[i]);


		m_aLight[i].Direction = vecDir[i];

		//�ݒ肷��
		pDevice->SetLight(0, &m_aLight[i]);

		pDevice->LightEnable(0, TRUE);
	}

	return S_OK;
}

/*============================
//�I��
============================*/

void CLight::Uninit()
{

}

/*============================
//�X�V
============================*/

void CLight::Update()
{
	//����Ȃ�
}