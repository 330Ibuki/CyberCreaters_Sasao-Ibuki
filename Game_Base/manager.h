#ifndef _MANAGER_H_
#define _MANAGER_H_

//インクルード
#include <Windows.h>
#include "d3dx9.h"
#include "scene.h"


//前方宣言
class CRenderer;
class CInputKeyboard;
class CCamera;
class CLight;
class CCollision;
//class CToolPlace;
class CScene;
//マネージャークラス
class CManager
{
public:
	CManager();
	~CManager();
	HRESULT Init(HINSTANCE hInstance,HWND hWnd, BOOL bWindow);
	void Uninit();
	void Update();
	void Draw();
	//void Debuglog();
	static CRenderer* GetRenderer();
	static CInputKeyboard* GetKeyboard();
	static CCamera* GetCamera();
	static CLight* GetLight();
	static CManager* GetManager();
	//static CToolPlace* ToolActive();
	static void SetMode(CScene::MODE mode);
	static HINSTANCE m_hInstance;
	static BOOL m_bWindow;
	static HWND m_hWnd;

private:
	static CRenderer* m_pRenderer;
	static CInputKeyboard* m_pKeyboard;
	static CCamera* m_pCamera;
	static CLight* m_pLight;
	static CScene* m_pScene;
	static CCollision* m_pCol;
	static CManager* m_Manager;
	//int m_pFPS;
	//LPD3DXFONT m_pFont;
	//static CToolPlace* TP;
};
#endif // !_MANAGER_H_
