/*
number
*/

//include
#include "number.h"

//静的メンバ初期化
CN_Score* CN_Score::m_Score[SCORENUM] = {};
CN_Stock* CN_Stock::m_Stock = {};
int CN_Score::ScoreNum = NULL;
int CN_Score::S_Num = NULL;


/*======================
//CN_Score
======================*/
/*=========================
//コンストラクタ・デストラクタ
=========================*/
CN_Score::CN_Score() : CB_board(m_Priority = 4)
{
	DispNum = NULL;
	DoOnce = true;
	CurScore = NULL;
	ScoreNum++;
}

CN_Score::~CN_Score()
{
	ScoreNum--;
}

/*========================
//初期化
========================*/
HRESULT CN_Score::Init()
{
	VERTEX_3D* pVtx;
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Number.png",
		&m_ptex);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0 - B_Width, 0 + B_Height, -51);
	pVtx[1].pos = D3DXVECTOR3(0 + B_Width, 0 + B_Height, -51);
	pVtx[2].pos = D3DXVECTOR3(0 - B_Width, 0 - B_Height, -51);
	pVtx[3].pos = D3DXVECTOR3(0 + B_Width, 0 - B_Height, -51);

	//法線ベクトル
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//頂点カラー設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.9f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.9f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	m_pVtxBuff->Unlock();

	//ifstream Score("data\\SCORE\\Score.txt");
	//if (Score.is_open())
	//{
	//	string line;
	//	getline(Score, line);
	//	CurScore = stoi(line);
	//}

	return S_OK;
}

/*===========================
//破棄
===========================*/
void CN_Score::Uninit()
{
	CB_board::Uninit();
	Release();
}

/*==========================
//更新
==========================*/
void CN_Score::Update()
{
	CPlayerX* Player = Player->GetPlayer();

	VERTEX_3D* pVtx;
	if (IsUse != true)
	{
		CN_Score::Uninit();
	}

	else
	{		 
		for (int i = 0; i < SCORENUM; i++)
		{
			m_Score[i]->m_pos.x = Player->m_pos.x + 148 - (15 * i);
			m_Score[i]->m_pos.y = Player->m_pos.y + 65;
		}
		
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		////テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1 * DispNum), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1 * DispNum), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1 * DispNum), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1 * DispNum), 1.0f);

		m_pVtxBuff->Unlock();

		ofstream Score("data\\SCORE\\Score.txt");
		if (Score.is_open())
		{
			Score << CurScore << endl;	//データ数
			Score.close();
		}

		if (IsUse == false)
		{
			IsUse = false;
		}
	}
}

/*===========================
//描画
===========================*/
void CN_Score::Draw()
{
	if (IsUse == true)
	{
		CB_board::Draw();
	}
}

/*===========================
//取得
===========================*/
int CN_Score::GetScoreNum()
{
	return ScoreNum;
}

/*==========================
//生成・設定
==========================*/
CN_Score* CN_Score::Create(D3DXVECTOR3 pos)
{
	for (int i = 0; i < SCORENUM; i++)
	{
		int Num = CN_Score::GetScoreNum();
		if (m_Score[Num] != nullptr)
		{
			m_Score[Num] = nullptr;
		}

		if (m_Score[Num] == nullptr)
		{
			m_Score[Num] = new CN_Score();
			m_Score[Num]->m_pos.x = pos.x - (15 * Num);
			m_Score[Num]->m_pos.y = pos.y;
			m_Score[Num]->m_pos.z = pos.z;
			m_Score[Num]->B_Height = 13;
			m_Score[Num]->B_Width = 10;
			m_Score[Num]->IsUse = true;
			m_Score[Num]->Init();
		}
	}

	return m_Score[0];
}

CN_Score* CN_Score::SetScore(int Score)
{
	m_Score[0]->CurScore += Score;
	S_Num += m_Score[0]->CurScore;
	for (int i = 0; i < SCORENUM; i++)
	{
		if (m_Score[i] != nullptr)
		{
			m_Score[i]->DispNum += S_Num % 10;
			if (m_Score[i]->DispNum >= 10)
			{
				m_Score[i + 1]->DispNum += 1;
				m_Score[i]->DispNum = 0;
			}
			S_Num = S_Num / 10;
		}
	}

	return m_Score[0];
}


/*=========================
//CN_Stock
=========================*/

/*=========================
//コンストラクタ・デストラクタ
=========================*/
CN_Stock::CN_Stock() : CB_board(m_Priority = 4)
{
	StockNum = NULL;
}

CN_Stock::~CN_Stock()
{

}

/*========================
//初期化
========================*/
HRESULT CN_Stock::Init()
{
	VERTEX_3D* pVtx;
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\Number.png",
			&m_ptex);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0 - B_Width, 0 + B_Height, -51);
	pVtx[1].pos = D3DXVECTOR3(0 + B_Width, 0 + B_Height, -51);
	pVtx[2].pos = D3DXVECTOR3(0 - B_Width, 0 - B_Height, -51);
	pVtx[3].pos = D3DXVECTOR3(0 + B_Width, 0 - B_Height, -51);

	//法線ベクトル
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//頂点カラー設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.9f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.9f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	m_pVtxBuff->Unlock();
	return S_OK;
}

/*===========================
//破棄
===========================*/
void CN_Stock::Uninit()
{
	CB_board::Uninit();
	Release();
}

/*==========================
//更新
==========================*/
void CN_Stock::Update()
{
	CPlayerX* Player = Player->GetPlayer();
	VERTEX_3D* pVtx;
	if (IsUse == false)
	{
		CN_Stock::Uninit();
	}

	else
	{
		m_pos.x = Player->m_pos.x - 100;
		m_pos.y = Player->m_pos.y + 70;

		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1 * StockNum), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1 * StockNum), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1 * StockNum), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1 * StockNum), 1.0f);

		m_pVtxBuff->Unlock();

		if (StockNum < 0)
		{
			IsUse = false;
		}
	}
}

/*===========================
//描画
===========================*/
void CN_Stock::Draw()
{
	if (IsUse == true)
	{
		CB_board::Draw();
	}
}

/*==========================
//生成・設定・取得
==========================*/
CN_Stock* CN_Stock::Create(D3DXVECTOR3 pos)
{
	if (m_Stock != nullptr)
	{
		m_Stock = nullptr;
	}

	if (m_Stock == nullptr)
	{
		m_Stock = new CN_Stock();
		m_Stock->m_pos = pos;
		m_Stock->B_Height = 20;
		m_Stock->B_Width = 10;
		m_Stock->StockNum = 9;
		m_Stock->IsUse = true;
		m_Stock->Init();
	}
	return m_Stock;
}

CN_Stock* CN_Stock::SetStock(int Num, bool IsDamaged)
{
	if (m_Stock != nullptr)
	{
		if (IsDamaged == true)
		{
				m_Stock->StockNum = m_Stock->StockNum - Num;
		}
		else
		{
			if (m_Stock->StockNum < 9)
			{
				m_Stock->StockNum = m_Stock->StockNum + Num;
			}
			
		}
	}

	return m_Stock;
}

CN_Stock* CN_Stock::GetStock()
{
	return m_Stock;
}