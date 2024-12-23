/*=============================================
//
// C++�|���S���`��
// Author: Sasao Ibuki
//
==============================================*/

//�C���N���[�h
#include"manager.h"
#include "renderer.h"
#include "input.h"
#include "camera.h"
#include "light.h"
#include "object2d.h"
#include "object3d.h"
#include "block.h"
#include "gimic.h"
#include "player.x.h"
#include "collision.h"
#include "billboard.h"
#include "scope.h"
#include "bullet.h"
#include "enemy.h"
#include "stage.h"
//#include "Item.h"
//#include "tool.h"



//�ÓI�����o������
CRenderer* CManager::m_pRenderer = nullptr;
CInputKeyboard* CManager::m_pKeyboard = nullptr;
CCamera* CManager::m_pCamera = nullptr;
CLight* CManager::m_pLight = nullptr;
CScene* CManager::m_pScene = nullptr;
CCollision* CManager::m_pCol = nullptr;
CManager* CManager::m_Manager = nullptr;
HWND CManager::m_hWnd = nullptr;
HINSTANCE CManager::m_hInstance = nullptr;

//CToolPlace* CToolPlace::TP = nullptr;


/*=======================
//�R���X�g���N�^�E�f�X�g���N�^
=======================*/

CManager::CManager()
{

}

CManager::~CManager()
{

}

/*=======================
//������
=======================*/

HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	//�����_���[�̐���
	m_pRenderer = new CRenderer();
	m_pRenderer->Init(hWnd, bWindow);

	//�L�[�{�[�h����
	m_pKeyboard = new CInputKeyboard();
	m_pKeyboard->Init(hInstance, hWnd, bWindow);

	//�J��������
	m_pCamera = new CCamera();
	m_pCamera->Init();

	//���C�g����
	m_pLight = new CLight();
	m_pLight->Init();

	//�ŏ��̃V�[���̐ݒ�
	SetMode(CScene::MODE::M_DEBUG);

	return S_OK;
}

/*=======================
//�I��
=======================*/

void CManager::Uninit()
{
	m_pScene->Uninit();
}

/*=======================
//�X�V�E�`��i�����_���[�́j
=======================*/

void CManager::Update()
{
	m_pScene->Update();

}

void CManager::Draw()
{
	m_pScene->Draw();
}

/*=======================
//�����_���[�̎擾
=======================*/

CRenderer * CManager::GetRenderer()
{
	return m_pRenderer;
}

/*=======================
//�L�[�{�[�h�̎擾
=======================*/

CInputKeyboard* CManager::GetKeyboard()
{
	return m_pKeyboard;
}

/*=======================
//�J�����̎擾
=======================*/

CCamera* CManager::GetCamera()
{
	return m_pCamera;
}

/*=======================
//���C�g�̎擾
=======================*/

CLight* CManager::GetLight()
{
	return m_pLight;
}

/*=======================
//�}�l�[�W���[�̎擾
=======================*/

CManager* CManager::GetManager()
{
	return m_Manager;
}

//CToolPlace* CManager::ToolActive()
//{
//	return TP;
//}

/*=======================
//���[�h�̐ݒ�
=======================*/

void CManager::SetMode(CScene::MODE mode)
{
	if (m_pScene != nullptr)
	{
		m_pScene->Uninit();
		delete m_pScene;
		m_pScene = nullptr;
	}

	//����
	m_pScene = CScene::Create(mode);
}

/*=======================
//�f�o�b�O�\��
=======================*/

