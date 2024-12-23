/*

Stage


*/

//インクルード
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "block.h"
//#include "gimic.h"

//ステージ構築クラス

class CStage
{
public:
	CStage();
	~CStage();
	HRESULT Init();
	void Uninit();
	void Update();
	static CStage* LoadStage(int StgNum);

private:

	static CStage* m_Stage;
	int Lvcol;									//エクセル（列）
	int Lvrow;									//エクセル（行）
	int Lv;										//エクセル（シート）
	bool ColReset;								//エクセル（列）のリセット
	std::vector<std::string> StageData;
	std::string line;
	std::string value;
};