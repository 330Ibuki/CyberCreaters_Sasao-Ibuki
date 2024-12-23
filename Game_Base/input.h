#ifndef _INPUT_H_
#define _INPUT_H_

//�C���N���[�h
#include "main.h"

//�}�N��
#define M_KEY	(256)

//���͊��N���X
class CInput
{
public:
	CInput();
	~CInput();
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	virtual void Uninit();
	virtual void Update() = 0;	//���͒[�����ƂɎ���

protected:
	static LPDIRECTINPUT8 m_pInput;
	LPDIRECTINPUTDEVICE8 m_pDevice;
};

//�L�[�{�[�h
class CInputKeyboard : public CInput
{
public:
	CInputKeyboard();
	~CInputKeyboard();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit();
	void Update();

	bool GetPress(int nKey);	//�v���X�̎擾
	bool GetTrigger(int nKey);	//�g���K�[�̎擾

private:
	BYTE m_aKeyState[M_KEY];
	BYTE m_aKeyStateTrigger[M_KEY];
};

//�R���g���[���[
//class CInputController : public CInput
//{
//
//};
#endif // !_INPUT_H_
