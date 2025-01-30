#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <Windows.h>
#include "d3dx9.h"

//マクロ
#define MOBJ	(2048)
#define MPRI	(6)

//全オブジェクト基底クラス
class CObject
{
public:

	/*
	* プライオリティ
	* 
	* １chara
	* ２block
	* ３BG
	* ４ui/item
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

	//オブジェクト管理
	static CObject* m_pTop[MPRI];	//先頭のオブジェクトのポインタ
	static CObject* m_pCur[MPRI];	//現在（最後尾）のポインタ
	CObject* m_pPrev;		//前のオブジェクトのポインタ
	CObject* m_pNext;		//次のオブジェクトへのポインタ
};

#endif // !_OBJECT_H_

