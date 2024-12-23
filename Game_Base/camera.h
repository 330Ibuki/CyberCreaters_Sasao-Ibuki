#ifndef _CAMERA_H_
#define _CAMERA_H_

//インクルード
#include "main.h"

//カメラクラスの定義
class CCamera
{
public:
	CCamera();
	~CCamera();
	HRESULT Init();
	void Uninit();
	void Update();
	void SetCamera();	//カメラの設定
	D3DXVECTOR3 m_PosV;	//視点
	D3DXVECTOR3 m_PosR;	//注視点
	D3DXMATRIX m_mtxView;		//ビュー行列

private:

	D3DXVECTOR3 m_PosU;	//上方向ベクトル
	D3DXVECTOR3 m_Rot;	//回転
	D3DXMATRIX m_mtxProjection;	//プロジェクション行列

	float m_Length;
};
#endif // !_CAMERA_H_
