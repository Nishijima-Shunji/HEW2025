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
#include "GameScene.h"

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

void Player::Init(std::vector<std::vector<int>> MapData)
{
    for (int i = 0; i < 18; i++) {
        for (int j = 0; j < 32; j++) {
            switch (MapData[i][j]) {
            case P_DIVER:
                MapList[i][j] = P_DIVER;
                break;

            case GOAL:
                MapList[i][j] = GOAL;
                break;

            case STREAM_R:
                MapList[i][j] = STREAM_R;
                break;

            case STREAM_L:
                MapList[i][j] = STREAM_L;
                break;

            case MIRROR_U:
                MapList[i][j] = MIRROR_U;
                break;

            case MIRROR_D:
                MapList[i][j] = MIRROR_D;
                break;
            }
        }
    }
}

std::vector<std::vector<int>> Player::Update(std::vector<std::vector<int>> MapData,GameScene& game)
{
    Map = MapData;

    if (MapList[PosY][PosX] == GOAL) {
        goalFg = true;
    }

    PlayerMove();

	Animation(game);

	// =====アニメーション=====
	

	return Map;
}

void Player::PlayerMove()
{
    bool inLight = false;

    if (Map[PosY][PosX] == LUMINOUS) {
        inLight = true;
    }

    if (inLight && !move) {
        CheckMove();
    }

    if (move) {
        MovePlayer();
    }
}

void Player::CheckMove()
{
    bool up_check = true, down_check = true,
        left_check = true, right_check = true;
    bool gimmicFg = false;

    targetX = PosX;
    targetY = PosY;

    gimmicFg = CheckGimmic();

    bool exit = false;
    if (!gimmicFg) {
        for (int check_dir = 0; check_dir < 4; check_dir++) {
            switch ((direction + check_dir) % 4) {
            case P_UP:
                exit = CheckMap(PosY - 1, PosX, P_UP);
                break;

            case P_RIGHT:
                exit = CheckMap(PosY, PosX + 1, P_RIGHT);
                break;

            case P_DOWN:
                exit = CheckMap(PosY + 1, PosX, P_DOWN);
                break;

            case P_LEFT:
                exit = CheckMap(PosY, PosX - 1, P_LEFT);
                break;
            }
            if (exit)    break;
        }
    }
    direction = holdDire;
}
//ギミック別の処理
bool Player::CheckGimmic()
{
    switch (MapList[PosY][PosX]) {
    case MIRROR_D:
    case MIRROR_U:
        Reflection(MapList[PosY][PosX]);
        return false;

    case STREAM_R:
    case STREAM_L:
        Stream(MapList[PosY][PosX]);
        return true;
    }

    return false;
}
//鏡鯛の処理
void Player::Reflection(int gimmic)
{
    if (gimmic == MIRROR_D) {
        switch (direction) {
        case P_UP:
        case P_DOWN:
            direction = (direction + 3) % 4;
            break;
        case P_RIGHT:
        case P_LEFT:
            direction = (direction + 1) % 4;
            break;
        }
    }
    else {
        switch (direction) {
        case P_UP:
        case P_DOWN:
            direction = (direction + 1) % 4;
            break;
        case P_RIGHT:
        case P_LEFT:
            direction = (direction + 3) % 4;
            break;
        }
    }
}
void Player::Stream(int gimmic)
{
    if (gimmic == STREAM_R) {
        targetX += 1;
        move = true;
    }
    else {
        targetX -= 1;
        move = true;
    }
}
bool Player::CheckMap(int pos_y, int pos_x, int dire)
{
    if (Map[pos_y][pos_x] == LUMINOUS || Map[pos_y][pos_x] == GOAL) {
        DirectionCase(dire);
        holdDire = dire;
        move = true;
        return true;
    }
    //止まる場所の検知
    if (Map[pos_y][pos_x] == WALL || Map[pos_y][pos_x] == LIGHTUPWALL ||
        Map[pos_y][pos_x] == MAP_END || Map[pos_y][pos_x] == LIGHT_1 || Map[pos_y][pos_x] == LIGHT_2) {
        holdDire = (dire + 2) % 4;
    }

    return false;
}
void Player::DirectionCase(int dire)
{
    switch (dire)
    {
    case P_UP:
        targetY = PosY - 1;
        break;
    case P_RIGHT:
        targetX = PosX + 1;
        break;
    case P_DOWN:
        targetY = PosY + 1;
        break;
    case P_LEFT:
        targetX = PosX - 1;
        break;
    }
}

void Player::MovePlayer()
{
    switch (direction) {
    case P_UP:
        pos.y += speed;
        Vertical = true;
        break;

    case P_RIGHT:
        pos.x += speed;
        Horizontal = true;
        break;

    case P_DOWN:
        pos.y -= speed;
        Vertical = true;
        break;

    case P_LEFT:
        pos.x -= speed;
        Horizontal = true;
        break;
    }

    if (std::abs(std::abs(pos.x) - abs(targetX * 30.0f)) < 0.1f &&
        std::abs(std::abs(pos.y) - abs(targetY * 30.0f)) < 0.1f) {
        PosX = targetX;
        PosY = targetY;
        Vertical = false;
        Horizontal = false;
        move = false;
    }
}

void Player::Animation(GameScene& game) {
    TextureManager* texture = game.GetTexture_ptr();
    // 方向に応じてテクスチャ変更
    switch (direction) {
    case P_UP:      SetTexture(texture, L"asset/survivor2.png", 4, 2); break;
    case P_LEFT:    SetTexture(texture, L"asset/survivor1.png", 4, 2); break;
    case P_RIGHT:   SetTexture(texture, L"asset/survivor1.png", 4, 2); break;
    default:        SetTexture(texture, L"asset/survivor3.png", 4, 2);
    }

    // アニメーション再生
    SetUV(animcount % 4, (animcount / 4) % 2);
    if (framecount % 5 == 0) {
        animcount++;
    }

    framecount++;
}

//******************************************************************************
//	End of file.
//******************************************************************************
