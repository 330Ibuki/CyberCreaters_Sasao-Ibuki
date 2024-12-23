/*
score
*/

#ifndef _NUMBER_H_
#define _NUMBER_H_

//include
#include "billboard.h"

//macro
#define SCORENUM	(6)

class CN_Score : public CB_board
{
public:
	CN_Score();
	~CN_Score()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static CN_Score* Create(D3DXVECTOR3 pos);
	static CN_Score* SetScore(int Score);
	static int GetScoreNum();
	static int S_Num;
	int CurScore;
private:
	static CN_Score* m_Score[SCORENUM];
	static int ScoreNum;
	bool DoOnce;
	int DispNum;

};

class CN_Stock : public CB_board
{
public:
	CN_Stock();
	~CN_Stock()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static CN_Stock* Create(D3DXVECTOR3 pos);
	static CN_Stock* SetStock(int Num, bool IsDamaged);
	static CN_Stock* GetStock();
	int StockNum;
private:
	static CN_Stock* m_Stock;
	

};

#endif // !_SCORE_H_

