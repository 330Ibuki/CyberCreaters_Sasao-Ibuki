/*

Stage


*/

//�C���N���[�h
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "block.h"
//#include "gimic.h"

using namespace std;

//�X�e�[�W�\�z�N���X

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
	int Lvcol;									//�G�N�Z���i��j
	int Lvrow;									//�G�N�Z���i�s�j
	int Lv;										//�G�N�Z���i�V�[�g�j
	bool ColReset;								//�G�N�Z���i��j�̃��Z�b�g
vector<std::string> StageData;
string line;
string value;
};