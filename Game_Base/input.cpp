/*=============================================
//
// C++�|���S���`��
// Author: Sasao Ibuki
//
==============================================*/

//�C���N���[�h
#include "input.h"

//�ÓI�����o������
LPDIRECTINPUT8 CInput::m_pInput = nullptr;

/*===========
//
// ���N���X
//
============*/

/*============================
//�R���X�g���N�^�E�f�X�g���N�^
============================*/

CInput::CInput()
{
	m_pDevice = nullptr;
}

CInput::~CInput()
{

}

/*==========================
//�����ݒ�
==========================*/

HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	if (m_pInput == nullptr)
	{
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
		{
			return E_FAIL;
		}
	}
	return S_OK;
}

/*=========================
//�j��
=========================*/

void CInput::Uninit()
{
	//���̓f�o�C�X�i�L�[�{�[�h�j�̔j��
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = nullptr;
	}

	//DirectInput�I�u�W�F�N�g�̔j��
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = nullptr;
	}
}

/*===========
//
// �L�[�{�[�h
//
============*/

/*============================
//�R���X�g���N�^�E�f�X�g���N�^
=============================*/

CInputKeyboard::CInputKeyboard()
{
	for (int i = 0; i < M_KEY; i++)
	{
		m_aKeyState[i] = {};
		m_aKeyStateTrigger[i] = {};
	}	
}

CInputKeyboard::~CInputKeyboard()
{

}

HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	if (FAILED(CInput::Init(hInstance, hWnd, bWindow)))
	{
		return E_FAIL;
	}

	//���̓f�o�C�X�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	//�f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//�������[�h��ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//�L�[�{�[�h�ւ̃A�N�Z�X���̊l��
	m_pDevice->Acquire();
	return S_OK;
}

/*==============
//�j��
===============*/

void CInputKeyboard::Uninit()
{
	CInput::Uninit();
}

/*==============
//�X�V
==============*/

void CInputKeyboard::Update()
{
	BYTE aKeyState[M_KEY];
	int nCntKey;

	//���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < M_KEY; nCntKey++)
		{
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];
			m_aKeyState[nCntKey] = aKeyState[nCntKey];
		}
	}

	else
	{
		m_pDevice->Acquire();
	}
}

/*======================
//�e����͏�Ԃ̊֐�
======================*/

bool CInputKeyboard::GetPress(int nKey)
{
	return (m_aKeyState[nKey] & 0x80) != 0;
}

bool CInputKeyboard::GetTrigger(int nKey)
{
	return(m_aKeyStateTrigger[nKey] & 0x80) != 0;
}