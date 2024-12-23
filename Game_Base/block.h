#ifndef _BLOCK_H_
#define _BLOCK_H_

//�C���N���[�h
#include "main.h"
#include "objectx.h"

//�}�N����`
#define FROOF	(400)
#define PLAT	(400)
#define GROUND	(200)
#define MSG		(10)

//�X�e�[�W�\���p�u���b�N�N���X�i���N���X�FCObjectX�j
class CBlock : public CObjectX
{
public:
	CBlock();
	~CBlock();
	virtual HRESULT Init()override;
	virtual void Uninit()override;
	virtual void Update()override;
	virtual void Draw()override;
	static CBlock* Create(D3DXVECTOR3 pos);
	static CBlock* GetBlock(int Num);
	static int GetNumBlock();
private:
	static CBlock* m_apBlock[MOBJ];
	static int BlockNum;
};

//�V��
class CFloorRoof : public CBlock
{
public:
	CFloorRoof();
	~CFloorRoof()override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	static CFloorRoof* Create(D3DXVECTOR3 pos);
	static CFloorRoof* GetFloor(int Num);
	static int GetFRNum();

private:
	static CFloorRoof* m_apFRoof[FROOF];
	static int FRNum;
};

//��
class CFloorWall : public CBlock
{
public:
	CFloorWall();
	~CFloorWall()override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	static CFloorWall* Create(D3DXVECTOR3 pos);
	static CFloorWall* GetWall(int Num);
	static int GetFWNum();

private:
	static CFloorWall* m_apFWall[FROOF];
	static int FWNum;
};

//������ʂ蔲�����鑫��i������ށj
class CPlatform : public CBlock
{
public:
	typedef enum
	{
		BIG = 0,
		MIDDLE,
		SMALL,
		PlatMAX
	}PType;

	CPlatform();
	~CPlatform()override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	static CPlatform* Create(D3DXVECTOR3 pos, PType type);
	static CPlatform* GetPlat(int Num);
	static int GetPlatNum();
	int P_type;
private:
	static CPlatform* m_apPlat[PLAT];
	static int Plat;

};

//�n�ʁi������ށj
class CGround : public CBlock
{
public:
	typedef enum
	{
		BIG = 0,
		MIDDLE,
		SMALL,
		GroundMAX
	}GType;

	CGround();
	~CGround()override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	static CGround* Create(D3DXVECTOR3 pos, GType type);
	static CGround* GetGround(int Num);
	static int GetPlatNum();
	int G_type;
private:
	static CGround* m_apGround[GROUND];
	static int Ground;

};

//�X�^�[�g�E�S�[��
class CSG : public CBlock
{
public:
	CSG();
	~CSG()override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	static CSG* Create(D3DXVECTOR3 pos, bool IsStart);
	static CSG* GetSG(int Num);
	static int GetSGNum();
	bool IsStart;
private:
	static CSG* m_apSG[MSG];
	static int SGNum;
};

#endif // !_BLOCK_H_
