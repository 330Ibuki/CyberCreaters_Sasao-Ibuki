#ifndef _PLAYER_H_
#define _PLAYER_H_


#include "d3dx9.h"
#include "object2d.h"

//ÉvÉåÉCÉÑÅ[
class CPlayer : public CObject2D
{
public:
	CPlayer(int nPriority = 3);
	~CPlayer()override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	static CPlayer* Create();

private:
	LPDIRECT3DTEXTURE9 m_pPLtex;
	static CPlayer* m_pPlayer;
};
#endif // !_PLAYER_H_
