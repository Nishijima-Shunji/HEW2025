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

std::vector<std::vector<int>> Player::Update(std::vector<std::vector<int>> MapData)
{
    Map = MapData;

    SetUp();

    Move();

    // 待機アニメーション
    SetUV(animcount % 4 , (animcount / 4) % 2);
    if (framecount % 5 == 0) {
        animcount++;
    }

    framecount++;

    return Map;
    //原因↑返し値が代入されていない
}

void Player::SetUp()//ステージ更新ごとに行う
{
    for (int i = 0; i < 18; i++) {
        for (int j = 0; j < 32; j++) {
            if (Map[i][j] == P_DIVER)
            {   //プレイヤーを登録

                MoveList[i][j] = P_DIVER;
                Map[i][j] = NOTHING;

                X = i;
                Y = j;
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
                Map[i][j] = NOTHING;
            }
            else if (Map[i][j] == TRAP)
            {   //トラップを登録

                MoveList[i][j] = TRAP;
                Map[i][j] = NOTHING;
            }
            else if (Map[i][j] == STREAM_R)
            {   //海流(右)を登録

                MoveList[i][j] = STREAM_R;
                Map[i][j] = NOTHING;
            }
            else if (Map[i][j] == STREAM_L)
            {   //海流(左)を登録

                MoveList[i][j] = STREAM_L;
                Map[i][j] = NOTHING;
            }
            else if (Map[i][j] == MOB_1)
            {   //オニキンメを登録

                MoveList[i][j] = MOB_1;
                Map[i][j] = NOTHING;
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

    //プレイヤーのマップ上の座標を計算
    targetX = pos.x;
    targetY = pos.y;
    //ライトとの接触確認
    //照射中
    if (Map[X][Y] == Luminous)
    {
        //ライト方向を確認
        if (Map[X - 1][Y] == Luminous)
        {
            //上下移動
            Vertical = true;
            Horizontal = false;
        }
        else if (Map[X + 1][Y] == Luminous)
        {
            //上下移動（上は壁）
            Vertical = true;
            Horizontal = false;
        }
        else
        {
            //左右移動
            Vertical = false;
            Horizontal = true;
        }

        //ゴールに近い方向へ移動
        if (Vertical == true)
        {
            if (Goal_X > X) //ゴールより上にある
            {
                targetY -= 30.0f;
                X += 1;
            }
            else if (Goal_X < X)//ゴールより下にある
            {
                targetY += 30.0f;
                X -= 1;
            }
            else// ゴールと同じ高さ
            {

            }
        }
        else if (Horizontal == true)
        {
            if (Goal_Y > Y) //ゴールより左にある
            {
                targetX += 30.0f;
                Y += 1;
            }
            else if (Goal_Y < Y)//ゴールより右にある
            {
                targetX -= 30.0f;
                Y -= 1;
            }
            else// ゴールと同じ高さ
            {

            }
        }
    }
    //非照射
    else
    {
        Vertical = false;
        Horizontal = false;
    }

    Animation();
}

void Player::Animation()
{
    /*アニメーション*/
     // 滑らかに目標座標へ移動
    if (std::abs(pos.x - targetX) > 0.01f)
        pos.x += (targetX - pos.x) * speed * deltaTime;
    if (std::abs(pos.y - targetY) > 0.01f)
        pos.y += (targetY - pos.y) * speed * deltaTime;

    //SetPos(pos.x, pos.y, pos.z);
    SetPos(targetX, targetY, pos.z);
}

void Player::DebugList()
{
    std::cout << "マップ更新" << std::endl;
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
