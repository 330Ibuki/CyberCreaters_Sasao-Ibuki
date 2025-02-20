/*=============================================
//
// C++ポリゴン描画
// Author: Sasao Ibuki
//
==============================================*/

/*=======================
//インクルード
=======================*/
#include "main.h"
#include "object.h"
#include "renderer.h"
/*=======================
//静的メンバ初期化
=======================*/

int CObject::m_nNumAll = 0;
int CObject::m_nPriority = 0;
CObject* CObject::m_apObject[MPRI][MOBJ] = {};

CObject* CObject::m_pTop[MPRI] = {};
CObject* CObject::m_pCur[MPRI] = {};

/*=======================
//コンストラクタ・デストラクタ
=======================*/

CObject::CObject(int nPriority)
{
	m_nID = 0;
	m_nPriority = nPriority;
	m_pNext = nullptr;
	m_pPrev = nullptr;
	IsUse = true;

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
//初期化
=======================*/

HRESULT CObject::Init()
{
	return S_OK;
}

/*=======================
//終了
=======================*/

void CObject::Uninit()
{

}

/*=======================
//更新
=======================*/

void CObject::Update()
{

}

/*=======================
//描画
=======================*/

void CObject::Draw()
{

}

/*=======================
//自分自身の開放
=======================*/

void CObject::Release()
{
	int nID = m_nID;
	int pri = CObject::GetPri();

		if (/*m_apObject[pri][nID] != nullptr || */m_apObject[pri][nID]->IsUse == false)
		{
			delete m_apObject[pri][nID];
			m_apObject[pri][nID] = nullptr;
		}
}

//void CObject::Remove(CObject* obj)
//{
//	int pri = obj->GetPri();
//	auto it = object.find(pri);
//
//	if (it != object.end())
//	{
//		it->second.remove(obj);
//		if (it->second.empty())
//		{
//			object.erase(it);	//リストが空ならエントリ削除
//		}
//	}
//}

/*=======================
//全オブジェクト開放・更新・描画
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
				m_apObject[pri][obj]->Uninit();
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

	//for (auto& pair : object)
	//{
	//	for (CObject* obj : pair.second)
	//	{
	//		obj->Update();
	//	}
	//}
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

int CObject::GetPri() const
{
	return m_nPriority;
}

//void CObject::AddObj(CObject* obj)
//{
//	object[obj->GetPri()].push_back(obj);
//}
