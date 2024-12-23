#ifndef _CAMERA_H_
#define _CAMERA_H_

//�C���N���[�h
#include "main.h"

//�J�����N���X�̒�`
class CCamera
{
public:
	CCamera();
	~CCamera();
	HRESULT Init();
	void Uninit();
	void Update();
	void SetCamera();	//�J�����̐ݒ�
	D3DXVECTOR3 m_PosV;	//���_
	D3DXVECTOR3 m_PosR;	//�����_
	D3DXMATRIX m_mtxView;		//�r���[�s��

private:

	D3DXVECTOR3 m_PosU;	//������x�N�g��
	D3DXVECTOR3 m_Rot;	//��]
	D3DXMATRIX m_mtxProjection;	//�v���W�F�N�V�����s��

	float m_Length;
};
#endif // !_CAMERA_H_
