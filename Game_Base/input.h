#ifndef _INPUT_H_
#define _INPUT_H_

//インクルード
#include "main.h"

//マクロ
#define M_KEY	(256)

//入力基底クラス
class CInput
{
public:
	CInput();
	~CInput();
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	virtual void Uninit();
	virtual void Update() = 0;	//入力端末ごとに実装

protected:
	static LPDIRECTINPUT8 m_pInput;
	LPDIRECTINPUTDEVICE8 m_pDevice;
};

//キーボード
class CInputKeyboard : public CInput
{
public:
	CInputKeyboard();
	~CInputKeyboard();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit();
	void Update();

	bool GetPress(int nKey);	//プレスの取得
	bool GetTrigger(int nKey);	//トリガーの取得

private:
	BYTE m_aKeyState[M_KEY];
	BYTE m_aKeyStateTrigger[M_KEY];
};

//コントローラー
//class CInputController : public CInput
//{
//
//};
#endif // !_INPUT_H_
