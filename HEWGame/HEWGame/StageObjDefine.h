#pragma once
//ステージオブジェクト一覧
#define DARKNESS  (-1)	//無
#define SPACE    (0)	//空間
#define WALL     (1)	//壁
#define P_DIVER  (2)	//プレイヤー
#define E_SHARK  (3)	//エネミー
#define GOAL     (4)	//ゴール
#define MENDAKO  (5)	//メンダコ
#define MIRROR_U (6)	//鏡鯛（右上がり）
#define MIRROR_D (7)	//鏡鯛（左下がり）
#define TRAP     (8)	//トラップ
#define STREAM_R (9)	//海流（右）
#define STREAM_L (10)	//海流（左）
#define MAP_END  (11)	//マップ端（ライトの移動場所）
#define LIGHT_1  (12)	//ライト（レベル：1)
#define LIGHT_2  (13)	//ライト（レベル：2）
#define LIGHT_3  (14)	//ライト（レベル：3）
#define MOB_1    (15)	//オニキンメ
#define MOB_2    (16)	//アンコウ
#define D_LIGHT  (19)	//デバッグ用ライト
#define LUMINOUS (20)	//発光マス
#define LIGHTUPWALL	(21)	//光を当てられた壁