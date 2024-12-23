#ifndef _RENDERER_H_
#define _RENDERER_H_

//�C���N���[�h
#include <Windows.h>
#include "d3dx9.h"
#include "object.h"

//�����_���[�N���X�̒�`
class CRenderer 
{
public:
	CRenderer();
	~CRenderer();
	HRESULT Init(HWND hWnd, BOOL bWindow);
	void Uninit();
	void Update();
	void Draw();
	LPDIRECT3DDEVICE9 GetDevice();

private:
	LPDIRECT3D9 m_pD3D;					//Direct3D
	LPDIRECT3DDEVICE9 m_pD3DDevice;		//Direct3D�f�o�C�X
};
#endif // !_RENDERER_H_
