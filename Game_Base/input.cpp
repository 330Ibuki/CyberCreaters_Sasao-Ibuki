/*=============================================
//
// C++ポリゴン描画
// Author: Sasao Ibuki
//
==============================================*/

//インクルード
#include "input.h"

//静的メンバ初期化
LPDIRECTINPUT8 CInput::m_pInput = nullptr;

/*===========
//
// 基底クラス
//
============*/

/*============================
//コンストラクタ・デストラクタ
============================*/

CInput::CInput()
{
	m_pDevice = nullptr;
}

CInput::~CInput()
{

}

/*==========================
//初期設定
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
//破棄
=========================*/

void CInput::Uninit()
{
	//入力デバイス（キーボード）の破棄
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = nullptr;
	}

	//DirectInputオブジェクトの破棄
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = nullptr;
	}
}

/*===========
//
// キーボード
//
============*/

/*============================
//コンストラクタ・デストラクタ
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

	//入力デバイスの生成
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	//データフォーマットを設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//協調モードを設定
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//キーボードへのアクセス権の獲得
	m_pDevice->Acquire();
	return S_OK;
}

/*==============
//破棄
===============*/

void CInputKeyboard::Uninit()
{
	CInput::Uninit();
}

/*==============
//更新
==============*/

void CInputKeyboard::Update()
{
	BYTE aKeyState[M_KEY];
	int nCntKey;

	//入力デバイスからデータを取得
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
//各種入力状態の関数
======================*/

bool CInputKeyboard::GetPress(int nKey)
{
	return (m_aKeyState[nKey] & 0x80) != 0;
}

bool CInputKeyboard::GetTrigger(int nKey)
{
	return(m_aKeyStateTrigger[nKey] & 0x80) != 0;
}