/*============================================
//
// ��ʑJ��
//Author Sasao Ibjki
//
============================================*/

//�C���N���[�h
#include "renderer.h"
#include "manager.h"
#include "scene.h"
#include "camera.h"
#include "light.h"
#include "input.h"
#include "stage.h"
#include "scope.h"
#include "objectx.h"
#include "player.x.h"
#include "collision.h"
#include "UI.h"
#include "BG.h"
#include "item.h"
#include "sound.h"
#include "number.h"


//�ÓI�����o������
CScene* CScene::m_apScene = nullptr;
//CRenderer* CScene::m_pRenderer = nullptr;
CCamera* CScene::m_pCamera = nullptr;
CLight* CScene::m_pLight = nullptr;
CInputKeyboard* CScene::m_pKeyboard = nullptr;
CCollision* CScene::m_pCol = nullptr;

/*=======================
���N���X:CScene
=======================*/

/*============================
//�R���X�g���N�^�E�f�X�g���N�^
============================*/

CScene::CScene()
{
	m_Mode = M_NONE;
	IsUse = true;
	GMode = NULL;
}

CScene::~CScene()
{

}

/*============================
//������
=============================*/

HRESULT CScene::Init()
{
	CRenderer* m_pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = m_pRenderer->GetDevice();
	m_pKeyboard = CManager::GetKeyboard();
	//�J��������
	m_pCamera = new CCamera();
	m_pCamera = CManager::GetCamera();

	//���C�g����
	m_pLight = new CLight();
	m_pLight = CManager::GetLight();

	return S_OK;
}

/*============================
//�I��
=============================*/

void CScene::Uninit()
{
	CObject::ReleaseAll();
}

/*============================
//�X�V
=============================*/

void CScene::Update()
{
	CRenderer* m_pRenderer = new CRenderer();
	m_pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = m_pRenderer->GetDevice();
	CN_Stock* Stock = Stock->GetStock();
	m_pRenderer->Update();
	m_pKeyboard->Update();
	m_pCamera->Update();

	if (m_Mode == M_TITLE)
	{
		if (IsUse == false)
		{
			CScene::Uninit();
			CManager::SetMode(M_DEBUG);
		}

		if (IsUse == true)
		{
			if (m_pKeyboard->GetTrigger(DIK_RETURN) == true)
			{
				IsUse = false;
			}
		}
	}

	else if (m_Mode == M_GAME)
	{
		if (IsUse == false)
		{
			CScene::Uninit();
			CManager::SetMode(M_TITLE);
		}

		if (IsUse == true)
		{
			m_pCol->Update();
			if (m_pKeyboard->GetTrigger(DIK_RETURN) == true)
			{
				IsUse = false;
			}
		}
	}

	else if (m_Mode == M_RESULT)
	{
		if (IsUse == false)
		{
			CScene::Uninit();
			CManager::SetMode(M_TITLE);
		}

		if (IsUse == true)
		{
			if (m_pKeyboard->GetTrigger(DIK_RETURN) == true)
			{
				IsUse = false;
			}
		}
	}

	else if (m_Mode == M_DEBUG)
	{
		if (IsUse == false)
		{
			CScene::Uninit();
			CManager::SetMode(M_TITLE);
		}

		if (IsUse == true)
		{
			m_pCol->Update();
			if (Stock->StockNum < 0)
			{
				IsUse = false;
			}
		}
	}
}

/*============================
//�`��
=============================*/

void CScene::Draw()
{
	if (IsUse == true)
	{
		CRenderer* m_pRenderer = CManager::GetRenderer();
		LPDIRECT3DDEVICE9 pDevice = m_pRenderer->GetDevice();
		m_pRenderer->Draw();
	}
}

/*===========================
//����
===========================*/

CScene* CScene::Create(MODE mode)
{
		switch (mode)
		{
		case M_TITLE:	
			m_apScene = new CTitle();
			m_apScene->m_Mode = M_TITLE;
			m_apScene->Init();
			break;

		case M_GAME:
			m_apScene = new CGame();
			m_apScene->m_Mode = M_GAME;
			m_apScene->Init();
			break;

		case M_RESULT:	//�܂�
			m_apScene = new CResult();
			m_apScene->m_Mode = M_RESULT;
			m_apScene->Init();
			break;

		case M_DEBUG:
			m_apScene = new CDebug();
			m_apScene->m_Mode = M_DEBUG;
			m_apScene->Init();
			break;

		default:
			break;
		}
		return m_apScene;
}


/*=======================
�h���N���X:CTitle
=======================*/

/*============================
//�R���X�g���N�^�E�f�X�g���N�^
============================*/

CTitle::CTitle()
{

}

CTitle::~CTitle()
{

}

/*============================
//������
=============================*/
HRESULT CTitle::Init()
{
	CScene::Init();
	CBG::Create(CBG::BG_Type::BG_TITLE);
	CUI::Create(D3DXVECTOR3(0,-55,0), CUI::CUI::UType::UI_S_GUIDE);
	return S_OK;
}

/*============================
//�j��
=============================*/
void CTitle::Uninit()
{
	CScene::Uninit();
}

/*============================
//�X�V
=============================*/
void CTitle::Update()
{
	CScene::Update();
}

/*============================
//�`��
=============================*/
void CTitle::Draw()
{
	CScene::Draw();
}

/*=======================
�h���N���X:CGame
=======================*/

/*============================
//�R���X�g���N�^�E�f�X�g���N�^
============================*/

CGame::CGame()
{

}

CGame::~CGame()
{

}

/*============================
//������
=============================*/

HRESULT CGame::Init()
{
	CScene::Init();
	m_pCol->Init();
	//����
	CSound::BGM(CSound::SOUND_BGM::BGM_TEST, CSound::BGM_STATE::BGM_OPEN);
	CSound::BGM(CSound::SOUND_BGM::BGM_TEST, CSound::BGM_STATE::BGM_PLAY);
	CStage::LoadStage(1);//Priority1.2
	CBG::Create(CBG::BG_Type::BG_GAME);//Priority3
	CUI::Create(D3DXVECTOR3(-70, -50, 0), CUI::UType::UI_LIFE);//Priority4
	CUI::Create(D3DXVECTOR3(120, -50, 0), CUI::UType::UI_SCORE);//Priority4
	CN_Stock::Create(D3DXVECTOR3(-70, -50, 0));//Priority4
	CN_Score::Create(D3DXVECTOR3(165, -50, 0));//Priority4
	CScope::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));//Priority4
	return S_OK;
}

/*============================
//�I��
=============================*/

void CGame::Uninit()
{
	CSound::BGM(CSound::SOUND_BGM::BGM_TEST, CSound::BGM_STATE::BGM_CLOSE);
	CScene::Uninit();
}

/*============================
//�X�V
=============================*/

void CGame::Update()
{
	CScene::Update();
}

/*============================
//�`��
=============================*/

void CGame::Draw()
{
	CScene::Draw();
}

/*=======================
�h���N���X:CResult
=======================*/

/*============================
//�R���X�g���N�^�E�f�X�g���N�^
============================*/
CResult::CResult()
{

}

CResult::~CResult()
{

}

/*============================
//������
=============================*/
HRESULT CResult::Init()
{
	CScene::Init();
	CBG::Create(CBG::BG_Type::BG_RESULT);
	//Score
	return S_OK;
}

/*============================
//�j��
=============================*/
void CResult::Uninit()
{
	CScene::Uninit();
}

/*============================
//�X�V
=============================*/
void CResult::Update()
{
	CScene::Update();
}

/*============================
//�`��
=============================*/
void CResult::Draw()
{
	CScene::Draw();
}

/*=======================
�h���N���X:CDebug
=======================*/

/*============================
//�R���X�g���N�^�E�f�X�g���N�^
============================*/

CDebug::CDebug()
{

}

CDebug::~CDebug()
{

}

/*============================
//������
=============================*/

HRESULT CDebug::Init()
{
	CScene::Init();
	m_pCol->Init();

	//����
	CSound::BGM(CSound::SOUND_BGM::BGM_TEST, CSound::BGM_STATE::BGM_OPEN);
	CSound::BGM(CSound::SOUND_BGM::BGM_TEST, CSound::BGM_STATE::BGM_PLAY);
	CBG::Create(CBG::BG_Type::BG_GAME);
	CUI::Create(D3DXVECTOR3(-70, -50, 0), CUI::UType::UI_LIFE);
	CUI::Create(D3DXVECTOR3(120, -50, 0), CUI::UType::UI_SCORE);
	CN_Stock::Create(D3DXVECTOR3(-80, -50, 0));
	CN_Score::Create(D3DXVECTOR3(165, -50, 0));
	CScope::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CStage::LoadStage(1);
	return S_OK;
}

/*============================
//�I��
=============================*/

void CDebug::Uninit()
{
	CScene::Uninit();
	CSound::BGM(CSound::SOUND_BGM::BGM_TEST, CSound::BGM_STATE::BGM_CLOSE);
}

/*============================
//�X�V
=============================*/

void CDebug::Update()
{
	CScene::Update();
}

/*============================
//�`��
=============================*/

void CDebug::Draw()
{
	CScene::Draw();
}