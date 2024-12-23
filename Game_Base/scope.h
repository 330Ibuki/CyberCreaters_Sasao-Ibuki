/*==========================
#
# UI_Scope
#
==========================*/

//インクルード
#include "main.h"
#include "billboard.h"

//スコープ
class CScope : public CB_board
{
public:
	CScope();
	~CScope() override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static CScope* Create(D3DXVECTOR3 pos);
	static CScope* GetScope();
private:
	static CScope* m_scope;

};