//*****************************************************************************
//!	@file	ファイル名
//!	@brief	簡単な説明
//!	@note	メモ
//!	@author	製作者
//*****************************************************************************

//-----------------------------------------------------------------------------
//	Include header files.
//-----------------------------------------------------------------------------
#include "Player.h"

//-----------------------------------------------------------------------------
// プロトタイプ宣言
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// グローバル変数
//-----------------------------------------------------------------------------


//==============================================================================
//!	@fn		
//!	@brief	
//!	@param	
//!	@param	
//!	@param	
//!	@param	
//!	@retval 
//==============================================================================

std::vector<std::vector<int>> Player::Update(std::vector<std::vector<int>> MapData,GameScene& game)
{
    Map = MapData;
    if (Start == false)
    {
        SetUp();
        Start = true;
    }

    Move();

    // 待機アニメーション
    SetUV(animcount % 4 , (animcount / 4) % 2);
    if (framecount % 5 == 0) {
        animcount++;
    }

    framecount++;

    return Map;
}

void Player::SetUp()//ステージ更新ごとに行う
{
    for (int i = 0; i < 18; i++) {
        for (int j = 0; j < 32; j++) {
            if (Map[i][j] == P_DIVER)
            {   //プレイヤーを登録

                MoveList[i][j] = P_DIVER;
                Map[i][j] = DARKNESS;

                X = i;
                Y = j;
                targetX = pos.x;
                targetY = pos.y;
            }
            else if (Map[i][j] == GOAL)
            {   //ゴールを登録

                MoveList[i][j] = GOAL;
                Goal_X = i;
                Goal_Y = j;
            }
            else if (Map[i][j] == MENDAKO)
            {   //メンダコを登録

                MoveList[i][j] = MENDAKO;
                Map[i][j] = DARKNESS;
            }
            else if (Map[i][j] == TRAP)
            {   //トラップを登録

                MoveList[i][j] = TRAP;
                Map[i][j] = DARKNESS;
            }
            else if (Map[i][j] == STREAM_R)
            {   //海流(右)を登録

                MoveList[i][j] = STREAM_R;
                Map[i][j] = DARKNESS;
            }
            else if (Map[i][j] == STREAM_L)
            {   //海流(左)を登録

                MoveList[i][j] = STREAM_L;
                Map[i][j] = DARKNESS;
            }
            else if (Map[i][j] == MOB_1)
            {   //オニキンメを登録

                MoveList[i][j] = MOB_1;
                Map[i][j] = DARKNESS;
            }
            else
            {
                //   MoveList[i][j] = SPACE;
            }
        }
    }
}


void Player::Move()
{
    DirectX::XMFLOAT3 pos = GetPos();

    if (Map[X][Y] == GOAL)
    {

    }
    
    if (targetX == pos.x && targetY == pos.y)//移動が完了した
    {
        //ライトとの接触確認
        //照射中
        if (Map[X][Y] == Luminous)
        {
            //上下マスの発光を確認
            if (Map[X - 1][Y] == Luminous || Map[X + 1][Y] == Luminous)
            {
                Vertical = true;
            }
            else
            {
                Vertical = false;
            }
            //左右マスの発光を確認
            if (Map[X][Y - 1] == Luminous || Map[X][Y + 1] == Luminous)
            {
                Horizontal = true;
            }
            else
            {
                Horizontal = false;
            }

            //上下移動
            if (Vertical == true)
            {
                if (Map[X - 1][Y] != Luminous && Map[X - 1][Y] != GOAL)      //上のマスが発光していない
                {
                    Reverse = false;
                }
                else if (Map[X + 1][Y] != Luminous && Map[X + 1][Y] != GOAL) //下のマスが発光していない
                {
                    Reverse = true;
                }

                if (Reverse == false)
                {
                    targetY -= 30.0f;
                    X += 1;
                }
                else if (Reverse == true)
                {
                    targetY += 30.0f;
                    X -= 1;
                }
            }

            //左右移動
            if (Horizontal == true)
            {
                if (Map[X][Y - 1] != Luminous && Map[X][Y - 1] != GOAL)      //左のマスが発光していない
                {
                    Reverse = false;
                }
                else if (Map[X][Y + 1] != Luminous && Map[X][Y + 1] != GOAL) //右のマスが発光していない
                {
                    Reverse = true;
                }
                if (Reverse == false)
                {
                    targetX += 30.0f;
                    Y += 1;
                }
                else if (Reverse == true)
                {
                    targetX -= 30.0f;
                    Y -= 1;
                }
            }

        }
        //非照射
        else
        {
            Vertical = false;
            Horizontal = false;
            Reverse = false;
        }

    }
    else//移動中
    {
        // 滑らかに目標座標へ移動
        //目標座標より上に存在
        if (pos.x < targetX)
        {
            pos.x += 1.0f;
        }
        //目標座標より下に存在
        else if (pos.x > targetX)
        {
            pos.x -= 1.0f;
        }
        //目標座標より右に存在
        else if (pos.y > targetY)
        {
            pos.y -= 1.0f;
        }
        //目標座標より左に存在
        else if (pos.y < targetY)
        {
            pos.y += 1.0f;
        }

        SetPos(pos.x, pos.y, pos.z);
    }
}

void Player::DebugList()
{
    std::cout << "マップ更新:Player" << std::endl;
    //デバッグ	マップ数値表示
    for (int i = 0; i < 18; i++) {
        for (int j = 0; j < 32; j++) {
            std::cout << MoveList[i][j] << ",";
        }
        std::cout << std::endl;
    }
    //======================
}

//******************************************************************************
//	End of file.
//******************************************************************************
