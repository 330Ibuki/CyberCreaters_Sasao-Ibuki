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
	int B_Num;	//�u���b�N�̔ԍ�
	float B_x, B_y, B_z; //�u���b�N���W
};

#endif // !_TOOL_H_