#ifndef _SCENE_H_
#define _SCENE_H_

//�C���N���[�h
#include "main.h"

//�O���錾
class CRenderer;
class CInputKeyboard;
class CCamera;
class CLight;
class CCollision;

//��ʊ��N���X
class CScene
{
public:
	//���
	typedef enum
	{
		M_NONE = 0,	//�Ȃɂ��Ȃ�
		M_TITLE,	//�^�C�g��
		M_GAME,		//�Q�[�����
		M_RESULT,	//���U���g���
		M_DEBUG,	//�f�o�b�O�p
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

//�^�C�g�����
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

//�Q�[�����
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

//���U���g���
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

//�f�o�b�O��ʁi�Q�[����ʂƂقړ����Ɂj
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

