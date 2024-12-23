/*=================================
#
# GameTool_StageCrafter
# Author: Sasao Ibuki
#
=================================*/

#ifndef _TOOL_H_
#define _TOOL_H_

#include "main.h"
#include "block.h"
#include "renderer.h"
#include "manager.h"

class CToolPlace
{
public:
	CToolPlace();
	~CToolPlace();
	void Init();
	void Uninit();
	void Update();
	//static CToolPlace *ToolActive();
private:
	static CToolPlace* TP;
	int B_Num;	//ブロックの番号
	float B_x, B_y, B_z; //ブロック座標
};

#endif // !_TOOL_H_