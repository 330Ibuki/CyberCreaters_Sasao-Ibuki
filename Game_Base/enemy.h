/*====================================
//
//enemy
//
====================================*/

//�C���N���[�h
#include "main.h"
#include "objectx.h"

//�}�N����`
#define ENM_MAX	(50)

//�G�l�~�[�N���X
class CEnemy : public CObjectX
{
public:
	typedef enum
	{
		E_Normal = 0,
		E_3Way_Up,
		E_3Way_Down,
		E_3Way_Left,
		E_3Way_Right,
		E_RapidFire,
		E_Speed,
		E_MAX
	}E_TYPE;

	CEnemy();				//�R���X�g���N�^
	virtual ~CEnemy()override;		//�f�X�g���N�^
	virtual HRESULT Init()override;	//������
	virtual void Uninit()override;	//�j��
	virtual void Update()override;	//�X�V
	virtual void Draw()override;	//�`��
	static CEnemy* Create(D3DXVECTOR3 pos,E_TYPE E_Type);	//����
	static CEnemy* GetEnmey(int Num);		//�擾
	static int GetE_Num();					//�����擾
	int E_Score;	//�������̃X�R�A
	int EType;
	
	int E_HP;
protected:
	static CEnemy* m_apEnemy[ENM_MAX];
	static int EnemyNum;
	bool RF_OverHeat;
	int Direction;
	int RF_Count;
	D3DXVECTOR3 move;
};

class CE_Normal : public CEnemy
{
public:
	CE_Normal();				//�R���X�g���N�^
	~CE_Normal()override;		//�f�X�g���N�^
	HRESULT Init()override;	//������
	void Uninit()override;	//�j��
	void Update()override;	//�X�V
	void Draw()override;	//�`��

private:
	bool M_Switch;
	int flame_move;
	int flame_switch;

};

class CE_Rapid : public CEnemy
{
public:
	CE_Rapid();				//�R���X�g���N�^
	~CE_Rapid()override;		//�f�X�g���N�^
	HRESULT Init()override;	//������
	void Uninit()override;	//�j��
	void Update()override;	//�X�V
	void Draw()override;	//�`��

private:
	//static CE_Rapid* E_R[ENM_MAX];

};

class CE_Speed : public CEnemy
{
public:
	CE_Speed();				//�R���X�g���N�^
	~CE_Speed()override;		//�f�X�g���N�^
	HRESULT Init()override;	//������
	void Uninit()override;	//�j��
	void Update()override;	//�X�V
	void Draw()override;	//�`��

private:
	//static CE_Speed* E_S[ENM_MAX];

};

class CE_3Way_Up : public CEnemy
{
public:
	CE_3Way_Up();				//�R���X�g���N�^
	~CE_3Way_Up()override;		//�f�X�g���N�^
	HRESULT Init()override;	//������
	void Uninit()override;	//�j��
	void Update()override;	//�X�V
	void Draw()override;	//�`��

private:
	//static CE_3Way_Up* E_Up[ENM_MAX];

};

class CE_3Way_Down : public CEnemy
{
public:
	CE_3Way_Down();				//�R���X�g���N�^
	~CE_3Way_Down()override;		//�f�X�g���N�^
	HRESULT Init()override;	//������
	void Uninit()override;	//�j��
	void Update()override;	//�X�V
	void Draw()override;	//�`��

private:
	//static CE_3Way_Down* E_Down[ENM_MAX];

};

class CE_3Way_Left : public CEnemy
{
public:
	CE_3Way_Left();				//�R���X�g���N�^
	~CE_3Way_Left()override;		//�f�X�g���N�^
	HRESULT Init()override;	//������
	void Uninit()override;	//�j��
	void Update()override;	//�X�V
	void Draw()override;	//�`��

private:
	//static CE_3Way_Left* E_Left[ENM_MAX];

};

class CE_3Way_Right : public CEnemy
{
public:
	CE_3Way_Right();				//�R���X�g���N�^
	~CE_3Way_Right()override;		//�f�X�g���N�^
	HRESULT Init()override;	//������
	void Uninit()override;	//�j��
	void Update()override;	//�X�V
	void Draw()override;	//�`��

private:
	//static CE_3Way_Right* E_Right[ENM_MAX];

};