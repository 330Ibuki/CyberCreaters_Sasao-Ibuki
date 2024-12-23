/*=============================================
//
// C++ポリゴン描画
// Author: Sasao Ibuki
//
==============================================*/

//インクルード
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



//静的メンバ初期化
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
//コンストラクタ・デストラクタ
=======================*/

CManager::CManager()
{

}

CManager::~CManager()
{

}

/*=======================
//初期化
=======================*/

HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	//レンダラーの生成
	m_pRenderer = new CRenderer();
	m_pRenderer->Init(hWnd, bWindow);

	//キーボード生成
	m_pKeyboard = new CInputKeyboard();
	m_pKeyboard->Init(hInstance, hWnd, bWindow);

	//カメラ生成
	m_pCamera = new CCamera();
	m_pCamera->Init();

	//ライト生成
	m_pLight = new CLight();
	m_pLight->Init();

	//最初のシーンの設定
	SetMode(CScene::MODE::M_DEBUG);

	return S_OK;
}

/*=======================
//終了
=======================*/

void CManager::Uninit()
{
	m_pScene->Uninit();
}

/*=======================
//更新・描画（レンダラーの）
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
//レンダラーの取得
=======================*/

CRenderer * CManager::GetRenderer()
{
	return m_pRenderer;
}

/*=======================
//キーボードの取得
=======================*/

CInputKeyboard* CManager::GetKeyboard()
{
	return m_pKeyboard;
}

/*=======================
//カメラの取得
=======================*/

CCamera* CManager::GetCamera()
{
	return m_pCamera;
}

/*=======================
//ライトの取得
=======================*/

CLight* CManager::GetLight()
{
	return m_pLight;
}

/*=======================
//マネージャーの取得
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
//モードの設定
=======================*/

void CManager::SetMode(CScene::MODE mode)
{
	if (m_pScene != nullptr)
	{
		m_pScene->Uninit();
		delete m_pScene;
		m_pScene = nullptr;
	}

	//生成
	m_pScene = CScene::Create(mode);
}

/*=======================
//デバッグ表示
=======================*/

