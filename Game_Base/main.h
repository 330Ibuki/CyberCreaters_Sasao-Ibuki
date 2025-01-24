#ifndef _MAIN_H_
#define _MAIN_H_

//�C���N���[�h
#include <Windows.h>
#include "d3dx9.h"
#define DIRECTINPUT_VERSION	(0x0800)
#include "dinput.h"
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <list>

//���C�u�����̃����N
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "winmm.lib")

//�}�N����`

#define CLASS_NAME		("WindowsClass")
#define WINDOW_NAME		("no title")
#define SCREEN_WIDTH	(1280)
#define SCREEN_HEIGHT	(720)
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE)
#define FVF_VERTEX_3D	(D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define GAME_FPS		(60)
#define SENTER (D3DXVECTOR3(640.0f,360.0f,0.0f)) 
#define MAX_MOTIONMODE (8)

using namespace std;

//���_���\���̂̒�`
struct VERTEX_2D
{
	D3DXVECTOR3 pos;
	float rhw;
	D3DCOLOR col;
	D3DXVECTOR2 tex;
};

typedef struct
{
	D3DXVECTOR3 pos;	//���_���W
	D3DXVECTOR3 nor;	//�@���x�N�g��
	D3DCOLOR col;		//���_�J���[
	D3DXVECTOR2 tex;	//�e�N�X�`�����W
}VERTEX_3D;

void Uninit();

#endif // !_MAIN_H_

