/*
BG
*/

//include
#include "object2d.h"
#include "billboard.h"
#include "main.h"

//class
class CBG : public CB_board
{
public:
	typedef enum
	{
		BG_TITLE = 0,
		BG_RESULT,
		BG_GAME,
		BG_MAX
	}BG_Type;

	CBG();
	~CBG()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static CBG* Create(BG_Type type/*,bool Game*/);
	static CBG* GetBG();
	static int GetBGNum();
	int B_Type;
	//bool IsGame;	//trueでタイトル,、falseでゲーム等
private:
	static CBG* m_BG;
	static int BGNum;

};
