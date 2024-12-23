#ifndef _UI_H_
#define _UI_H_

//�C���N���[�h
#include "main.h"
#include "billboard.h"

//�}�N����`
#define UMAX	(2);

//UI�N���X
class CUI : public CB_board
{
public:
	typedef enum
	{
		UI_LIFE = 0,
		UI_SCORE,
		UI_S_GUIDE,
		UI_BG_TEST,
		UI_MAX
	}UType;

	CUI();
	~CUI()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static CUI* Create(D3DXVECTOR3 pos,UType type);
	static CUI* GetUI(int num);
	static int GetUINum();

private:
	static CUI* m_UI[2];
	static int UINum;
	int UI_type;
	float UI_A;			//�����x
	bool A_Reduction;	//�����x�����X�C�b�`
};


#endif // ! _UI_H_
