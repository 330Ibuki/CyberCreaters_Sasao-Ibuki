/*=============================================
//
// C++�|���S���`��
// Author: Sasao Ibuki
//
==============================================*/

/*=======================
//�C���N���[�h
=======================*/
#include "main.h"
#include "object.h"
#include "renderer.h"
/*=======================
//�ÓI�����o������
=======================*/

int CObject::m_nNumAll = 0;
CObject* CObject::m_apObject[MPRI][MOBJ] = {};
CObject* CObject::m_pTop[MPRI] = {};
CObject* CObject::m_pCur[MPRI] = {};

/*=======================
//�R���X�g���N�^�E�f�X�g���N�^
=======================*/

CObject::CObject(int nPriority)
{
	m_nID = 0;
	m_nPriority = nPriority;
	m_pNext = nullptr;
	m_pPrev = nullptr;
	IsUse = false;

	for (int obj = 0; obj < MOBJ; obj++)
	{
		

		if (m_apObject[m_nPriority][obj] == nullptr)
		{
			m_apObject[m_nPriority][obj] = this;
			m_nID = obj;
			m_nNumAll++;
			break;
		}
	}

	//for (int pri = 0; pri < MPRI; pri++)
	//{
	//	if (m_apObject[m_nPriority][0] == nullptr)
	//	{
	//		
	//	}
	//}
}

CObject::~CObject()
{
	m_nNumAll--;
}

/*=======================
//������
=======================*/

HRESULT CObject::Init()
{
	return S_OK;
}

/*=======================
//�I��
=======================*/

void CObject::Uninit()
{

}

/*=======================
//�X�V
=======================*/

void CObject::Update()
{

}

/*=======================
//�`��
=======================*/

void CObject::Draw()
{

}

/*=======================
//�������g�̊J��
=======================*/

void CObject::Release()
{
	int nID = m_nID;

	for (int pri = 0; pri < MPRI; pri++)
	{
		if (m_apObject[pri][nID] != nullptr && m_apObject[pri][nID]->IsUse == false)
		{
			delete m_apObject[pri][nID];
			m_apObject[pri][nID] = nullptr;
			break;
		}
	}
}

/*=======================
//�S�I�u�W�F�N�g�J���E�X�V�E�`��
=======================*/

void CObject::ReleaseAll()
{
	for (int pri = 0; pri < MPRI; pri++)
	{
		//CObject* pObj = m_pTop[pri];

		//while (pObj != nullptr)
		//{
		//	CObject* pNext = pObj[pri].m_pNext;
		//	pObj->Release();
		//	pObj = pNext;
		//}

		for (int obj = 0; obj < MOBJ; obj++)
		{
			if (m_apObject[pri][obj] != nullptr)
			{

				m_apObject[pri][obj]->IsUse = false;
				//m_apObject[pri][obj]->Uninit();
				m_apObject[pri][obj]->Release();
			}
		}
	}
}

void CObject::UpdateAll()
{

	for (int pri = 0; pri < MPRI; pri++)
	{
		//CObject* pObj = m_pTop[pri];

		//while (pObj != nullptr)
		//{
		//	CObject* pNext = pObj[pri].m_pNext;
		//	pObj->Update();
		//	pObj = pNext;
		//}

		for (int obj = 0; obj < MOBJ; obj++)
		{
			if (m_apObject[pri][obj] != nullptr)
			{
				m_apObject[pri][obj]->Update();
			}
		}
	}
}

void CObject::DrawAll()
{
	for (int pri = 0; pri < MPRI; pri++)
	{
		//CObject* pObj = m_pTop[pri];

		//while (pObj != nullptr)
		//{
		//	CObject* pNext = pObj[pri].m_pNext;
		//	pObj->Draw();
		//	pObj = pNext;
		//}

		for (int obj = 0; obj < MOBJ; obj++)
		{
			if (m_apObject[pri][obj] != nullptr)
			{
				m_apObject[pri][obj]->Draw();
			}
		}
	}
}

int CObject::GetNumAll()
{
	return m_nNumAll;
}

CObject* CObject::GetObject(int Pri, int Idx)
{
	return m_apObject[Pri][Idx];
}