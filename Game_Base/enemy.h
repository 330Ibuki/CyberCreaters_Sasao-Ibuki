/*====================================
//
//enemy
//
====================================*/

//インクルード
#include "main.h"
#include "objectx.h"

//マクロ定義
#define ENM_MAX	(50)

//エネミークラス
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

	CEnemy();				//コンストラクタ
	virtual ~CEnemy()override;		//デストラクタ
	virtual HRESULT Init()override;	//初期化
	virtual void Uninit()override;	//破棄
	virtual void Update()override;	//更新
	virtual void Draw()override;	//描画
	static CEnemy* Create(D3DXVECTOR3 pos,E_TYPE E_Type);	//生成
	static CEnemy* GetEnmey(int Num);		//取得
	static int GetE_Num();					//総数取得
	int E_Score;	//討伐時のスコア
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
	CE_Normal();				//コンストラクタ
	~CE_Normal()override;		//デストラクタ
	HRESULT Init()override;	//初期化
	void Uninit()override;	//破棄
	void Update()override;	//更新
	void Draw()override;	//描画

private:
	bool M_Switch;
	int flame_move;
	int flame_switch;

};

class CE_Rapid : public CEnemy
{
public:
	CE_Rapid();				//コンストラクタ
	~CE_Rapid()override;		//デストラクタ
	HRESULT Init()override;	//初期化
	void Uninit()override;	//破棄
	void Update()override;	//更新
	void Draw()override;	//描画

private:
	//static CE_Rapid* E_R[ENM_MAX];

};

class CE_Speed : public CEnemy
{
public:
	CE_Speed();				//コンストラクタ
	~CE_Speed()override;		//デストラクタ
	HRESULT Init()override;	//初期化
	void Uninit()override;	//破棄
	void Update()override;	//更新
	void Draw()override;	//描画

private:
	//static CE_Speed* E_S[ENM_MAX];

};

class CE_3Way_Up : public CEnemy
{
public:
	CE_3Way_Up();				//コンストラクタ
	~CE_3Way_Up()override;		//デストラクタ
	HRESULT Init()override;	//初期化
	void Uninit()override;	//破棄
	void Update()override;	//更新
	void Draw()override;	//描画

private:
	//static CE_3Way_Up* E_Up[ENM_MAX];

};

class CE_3Way_Down : public CEnemy
{
public:
	CE_3Way_Down();				//コンストラクタ
	~CE_3Way_Down()override;		//デストラクタ
	HRESULT Init()override;	//初期化
	void Uninit()override;	//破棄
	void Update()override;	//更新
	void Draw()override;	//描画

private:
	//static CE_3Way_Down* E_Down[ENM_MAX];

};

class CE_3Way_Left : public CEnemy
{
public:
	CE_3Way_Left();				//コンストラクタ
	~CE_3Way_Left()override;		//デストラクタ
	HRESULT Init()override;	//初期化
	void Uninit()override;	//破棄
	void Update()override;	//更新
	void Draw()override;	//描画

private:
	//static CE_3Way_Left* E_Left[ENM_MAX];

};

class CE_3Way_Right : public CEnemy
{
public:
	CE_3Way_Right();				//コンストラクタ
	~CE_3Way_Right()override;		//デストラクタ
	HRESULT Init()override;	//初期化
	void Uninit()override;	//破棄
	void Update()override;	//更新
	void Draw()override;	//描画

private:
	//static CE_3Way_Right* E_Right[ENM_MAX];

};