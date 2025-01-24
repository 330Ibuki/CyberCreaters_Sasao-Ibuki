/*=================================
#
# GameTool_StageCrafter
# Author: Sasao Ibuki
#
=================================*/

#ifndef _TOOL_H_
#define _TOOL_H_

#include "main.h"
#include "billboard.h"
#include "renderer.h"
#include "input.h"
#include "manager.h"

#define Place_M	(1000)


class CToolPlace
{
public:
	CToolPlace();
	~CToolPlace();
	void Init();
	void Uninit();
	void Update();
	static CToolPlace* GetTool();
	static CToolPlace* Active();
	D3DXVECTOR3 B_pos; //ブロック座標
	bool IsActive;	//起動してるかどうか
	int B_Num;	//ブロックの番号
	int B_CurMax;	//現在時点での最大ブロック数
	bool IsFirst;	//初回限定処理
private:
	static CToolPlace* TP;

};

class CTP_img : public CB_board
{
public:
	CTP_img();
	~CTP_img()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static int GetImgNum();
	static CTP_img* Getimg(int Num);
	static CTP_img* Create(D3DXVECTOR3 pos, int Num);
	int ImgNum;

private:
	static CTP_img* Place_Img[Place_M];
	static int TP_INum;
};

class CTP_SaveLoad	//セーブロード+ステージ用のテキストデータへの変換
{
public:
	CTP_SaveLoad();
	~CTP_SaveLoad();
	static void Save();
	static void Load();
};

#endif // !_TOOL_H_