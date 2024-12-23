#ifndef _SCENE_H_
#define _SCENE_H_

//インクルード
#include "main.h"

//前方宣言
class CRenderer;
class CInputKeyboard;
class CCamera;
class CLight;
class CCollision;

//画面基底クラス
class CScene
{
public:
	//種類
	typedef enum
	{
		M_NONE = 0,	//なにもなし
		M_TITLE,	//タイトル
		M_GAME,		//ゲーム画面
		M_RESULT,	//リザルト画面
		M_DEBUG,	//デバッグ用
		M_MAX,			
	}MODE;

	CScene();
	virtual ~CScene();
	virtual HRESULT Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();
	static CScene* Create(MODE mode);

private:
	MODE m_Mode;
	static CScene* m_apScene;

protected:
	//static CRenderer* m_pRenderer;
	static CInputKeyboard* m_pKeyboard;
	static CCamera* m_pCamera;
	static CLight* m_pLight;
	static CCollision* m_pCol;
	bool IsUse;
	int GMode;
};

//タイトル画面
class CTitle : public CScene
{
public:
	CTitle();
	 ~CTitle()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
};

//ゲーム画面
class CGame : public CScene
{
public:
	CGame();
	~CGame()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
};

//リザルト画面
class CResult : public CScene
{
public:
	CResult();
	~CResult()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
};

//デバッグ画面（ゲーム画面とほぼ同じに）
class CDebug : public CScene
{
public:
	CDebug();
	~CDebug()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
};
#endif // !_SCENE_H_

