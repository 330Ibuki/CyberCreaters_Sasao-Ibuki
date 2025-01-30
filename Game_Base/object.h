#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <Windows.h>
#include "d3dx9.h"

//�}�N��
#define MOBJ	(2048)
#define MPRI	(6)

//�S�I�u�W�F�N�g���N���X
class CObject
{
public:

	/*
	* �v���C�I���e�B
	* 
	* �Pchara
	* �Qblock
	* �RBG
	* �Sui/item
	* 5bullet
	*/
	CObject(int nPriority = 3);
	virtual ~CObject();
	virtual HRESULT Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	static int GetNumAll();
	static void ReleaseAll();
	static void UpdateAll();
	static void DrawAll();
	static CObject* GetObject(int Pri,int Idx);
	bool IsUse;

protected:
	void Release();
	int m_nPriority;
private:
	static CObject* m_apObject[MPRI][MOBJ];
	static int m_nNumAll;
	int m_nID;

	//�I�u�W�F�N�g�Ǘ�
	static CObject* m_pTop[MPRI];	//�擪�̃I�u�W�F�N�g�̃|�C���^
	static CObject* m_pCur[MPRI];	//���݁i�Ō���j�̃|�C���^
	CObject* m_pPrev;		//�O�̃I�u�W�F�N�g�̃|�C���^
	CObject* m_pNext;		//���̃I�u�W�F�N�g�ւ̃|�C���^
};

#endif // !_OBJECT_H_

