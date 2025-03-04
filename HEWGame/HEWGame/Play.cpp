#include "Play.h"

void Play::Init(std::vector<std::vector<int>> MapList)
{
	Map = MapList;
	light_max = 0;

	//データの入力
	CheckEdge();
	CheckLight();
	SetGimmick();
	SetLightUpMap();
}

//削除
void Play::Uninit()
{
}

std::vector<std::vector<int>> Play::Update(std::vector<std::vector<int>> MapList)
{
	input.Update();

	Map = MapList;

	for (int nowlight = 0; nowlight < light_max; nowlight++) {
		keepLightOn[nowlight] = LightOn[nowlight];
	}

	ChangeLight();
	//ライトのチェンジの後
	old_direction = Direction[light_number];
	MoveLight();
	LightUp();

	//もし場所が変わるなら
	if (old_pos_x != new_pos_x || old_pos_y != new_pos_y) {
		MapUpdate();
	}

	return Map;
}

//初期化系
void Play::CheckEdge()
{
	//横幅を取得
	for (int i = 0; i < WIDTH; i++) {
		if (Map[0][i] == NODATA) {
			width = i - 1;
			break;
		}
	}
	//高さを取得
	for (int j = 0; j < HEIGHT; j++) {
		if (Map[j][0] == NODATA) {
			height = j - 1;
			break;
		}
	}
}
void Play::CheckLight()
{
	for (int i = 0; i <= height; i++) {
		for (int j = 0; j <= width; j++) {
			if (Map[i][j] == LIGHT_1 || Map[i][j] == LIGHT_2 || Map[i][j] == LIGHT_3 || Map[i][j] == D_LIGHT) {
				LightPos_x.push_back(j);
				keep_pos_x.push_back(j);
				LightPos_y.push_back(i);
				keep_pos_y.push_back(i);
				LightOn.push_back(false);
				keepLightOn.push_back(false);
				LightStop.push_back(true);
				LightOk.push_back(true);
				light_max++;
			}
		}
	}

	for (int i = 0; i < light_max; i++) {
		if (LightPos_y[i] == height) {
			Direction.push_back(UP);
		}
		else if (LightPos_y[i] == 0) {
			Direction.push_back(DOWN);
		}
		else if (LightPos_x[i] == 0) {
			Direction.push_back(RIGHT);
		}
		else if (LightPos_x[i] == width) {
			Direction.push_back(LEFT);
		}

		Direction.push_back(UP);
		keep_Direction.push_back(Direction[i]);
	}
}
void Play::SetGimmick()
{
	for (int i = 0; i <= height; i++) {
		for (int j = 0; j <= width; j++) {
			switch (Map[i][j]) {
			case WALL:
				Gimmick[i][j] = WALL;
				break;

			case MIRROR_U:
				Gimmick[i][j] = MIRROR_U;
				break;

			case MIRROR_D:
				Gimmick[i][j] = MIRROR_D;
				break;

			case MOB_2:
				Gimmick[i][j] = MOB_2;
				break;
			}
		}
	}
}
void Play::SetLightUpMap()
{
	for (int i = 0; i <= height; i++) {
		for (int j = 0; j <= width; j++) {
			switch (Map[i][j]) {
			case WALL:
			case MAP_END:
			case GOAL:
			case LIGHT_1:
			case LIGHT_2:
			case LIGHT_3:
			case D_LIGHT:
				LightUpMap[i][j] = NOTLIGHTUP;
				break;

			default:
				LightUpMap[i][j] = NEUTRAL;
			}
		}
	}
}

//更新系
void Play::ChangeLight()
{
	//ライトチェンジ
	if (input.GetKeyTrigger(VK_Q) || input.GetButtonTrigger(XINPUT_LEFT_SHOULDER)) {	//前に戻る
		//Map[LightPos_x[light_number]][LightPos_y[light_number]] = LIGHT_1;
		light_number--;
		//Map[LightPos_x[light_number]][LightPos_y[light_number]] = LIGHT_2;
		if (light_number < 0) {
			//最大値は1~なため
			light_number = light_max - 1;
		}
	}

	if (input.GetKeyTrigger(VK_E) || input.GetButtonTrigger(XINPUT_RIGHT_SHOULDER)) {	//次に進む
		//Map[LightPos_x[light_number]][LightPos_y[light_number]] = LIGHT_1;
		light_number++;
		//Map[LightPos_x[light_number]][LightPos_y[light_number]] = LIGHT_2;
		if (light_number >= light_max) {
			light_number = 0;
		}
	}
}
void Play::MoveLight()
{
	old_pos_x = LightPos_x[light_number];
	new_pos_x = LightPos_x[light_number];
	old_pos_y = LightPos_y[light_number];
	new_pos_y = LightPos_y[light_number];

	//上
	if (input.GetKeyTrigger(VK_W) || input.GetButtonTrigger(XINPUT_UP)) {
		if (old_pos_y > 0) {
			if (Map[old_pos_y - 1][old_pos_x] == MAP_END) {
				new_pos_y--;
			}

			if (new_pos_y == 0) {
				if (old_pos_x == 0) {
					new_pos_x++;
				}
				else {
					new_pos_x--;
				}
				Direction[light_number] = DOWN;
			}

			if (old_pos_x == 1 && old_pos_y == height) {
				new_pos_x--;
				new_pos_y--;
				Direction[light_number] = RIGHT;
			}
			else if (old_pos_x == width - 1 && old_pos_y == height) {
				new_pos_x++;
				new_pos_y--;
				Direction[light_number] = LEFT;
			}

			if (new_pos_x > 0 && new_pos_x < width &&
				new_pos_y > 0) {
				if (Map[new_pos_y - 1][new_pos_x] != MAP_END) {
					Direction[light_number] = UP;
				}
			}

			if (LightOn[light_number] == true) {
				LightOn[light_number] = false;
				LightOk[light_number] = false;
				LightStop[light_number] = false;
			}
		}
	}

	//下
	if (input.GetKeyTrigger(VK_S) || input.GetButtonTrigger(XINPUT_DOWN)) {
		//高さを1マス下げる
		if (old_pos_y < height) {
			if (Map[old_pos_y + 1][old_pos_x] == MAP_END) {
				new_pos_y++;
			}

			if (new_pos_y == height) {
				if (old_pos_x == 0) {
					new_pos_x++;
				}
				else {
					new_pos_x--;
				}
				Direction[light_number] = UP;
			}

			if (old_pos_x == 1 && old_pos_y == 0) {
				new_pos_x--;
				new_pos_y++;
				Direction[light_number] = RIGHT;
			}
			else if (old_pos_x == width - 1 && old_pos_y == 0) {
				new_pos_x++;
				new_pos_y++;
				Direction[light_number] = LEFT;
			}

			if (new_pos_x > 0 && new_pos_x < width &&
				new_pos_y < height) {
				if (Map[new_pos_y + 1][new_pos_x] != MAP_END) {
					Direction[light_number] = DOWN;
				}
			}

			if (LightOn[light_number] == true) {
				LightOn[light_number] = false;
				LightOk[light_number] = false;
				LightStop[light_number] = false;
			}
		}
	}

	//右
	if (input.GetKeyTrigger(VK_D) || input.GetButtonTrigger(XINPUT_RIGHT)) {
		//右に1マス
		if (old_pos_x < width) {
			if (Map[old_pos_y][old_pos_x + 1] == MAP_END) {
				new_pos_x++;
			}

			if (new_pos_x == width) {
				if (old_pos_y == 0) {
					new_pos_y++;
				}
				else {
					new_pos_y--;
				}
				Direction[light_number] = LEFT;
			}

			if (old_pos_x == 0 && old_pos_y == 1) {
				new_pos_x++;
				new_pos_y--;
				Direction[light_number] = DOWN;
			}
			else if (old_pos_x == 0 && old_pos_y == height - 1) {
				new_pos_x++;
				new_pos_y++;
				Direction[light_number] = UP;
			}

			if (new_pos_x < width &&
				new_pos_y > 0 && new_pos_y < height) {
				if (Map[new_pos_y][new_pos_x + 1] != MAP_END) {
					Direction[light_number] = RIGHT;
				}
			}

			if (LightOn[light_number] == true) {
				LightOn[light_number] = false;
				LightOk[light_number] = false;
				LightStop[light_number] = false;
			}
		}
	}

	//左
	if (input.GetKeyTrigger(VK_A) || input.GetButtonTrigger(XINPUT_LEFT)) {
		//右に1マス
		if (old_pos_x > 0) {
			if (Map[old_pos_y][old_pos_x - 1] == MAP_END) {
				new_pos_x--;
			}

			if (new_pos_x == 0) {
				if (old_pos_y == 0) {
					new_pos_y++;
				}
				else {
					new_pos_y--;
				}
				Direction[light_number] = RIGHT;
			}

			if (old_pos_x == width && old_pos_y == 1) {
				new_pos_x--;
				new_pos_y--;
				Direction[light_number] = DOWN;
			}
			else if (old_pos_x == width && old_pos_y == height - 1) {
				new_pos_x--;
				new_pos_y++;
				Direction[light_number] = UP;
			}

			if (new_pos_x > 0 &&
				new_pos_y > 0 && new_pos_y < height) {
				if (Map[new_pos_y][new_pos_x - 1] != MAP_END) {
					Direction[light_number] = LEFT;
				}
			}

			if (LightOn[light_number] == true) {
				LightOn[light_number] = false;
				LightOk[light_number] = false;
				LightStop[light_number] = false;
			}
		}
	}
}
void Play::LightUp()
{
	//ライトの点灯を検知
	if (input.GetKeyTrigger(VK_SPACE) || input.GetButtonTrigger(XINPUT_A)) {
		if (LightOn[light_number]) {
			LightOn[light_number] = false;
			LightOk[light_number] = false;
		}
		else if (LightOk[light_number] == true) {
			LightOn[light_number] = true;
		}
	}

	//ライトの更新
	for (int nowlight = 0; nowlight < light_max; nowlight++) {
		if (LightOn[nowlight] != keepLightOn[nowlight]) {
			if (LightOn[nowlight]) {
				keep_pos_x[nowlight] = new_pos_x;
				keep_pos_y[nowlight] = new_pos_y;
			}
			else {
				keep_pos_x[nowlight] = old_pos_x;
				keep_pos_y[nowlight] = old_pos_y;
			}

			keep_Direction[light_number] = old_direction;
			LightStop[light_number] = false;
		}

		if (!LightStop[nowlight]) {
			switch (keep_Direction[nowlight]) {
			case UP://上
				//衝突判定まで
				keep_pos_y[nowlight]--;
				LightStop[nowlight] = Flash(keep_pos_x[nowlight], keep_pos_y[nowlight],
					LightOn[nowlight], nowlight);
				break;
			case DOWN://下
				//衝突判定まで
				keep_pos_y[nowlight]++;
				LightStop[nowlight] = Flash(keep_pos_x[nowlight], keep_pos_y[nowlight],
					LightOn[nowlight], nowlight);
				break;
			case RIGHT://右
				//衝突判定まで
				keep_pos_x[nowlight]++;
				LightStop[nowlight] = Flash(keep_pos_x[nowlight], keep_pos_y[nowlight],
					LightOn[nowlight], nowlight);
				break;
			case LEFT://左
				//衝突判定まで
				keep_pos_x[nowlight]--;
				LightStop[nowlight] = Flash(keep_pos_x[nowlight], keep_pos_y[nowlight],
					LightOn[nowlight], nowlight);
				break;
			}
		}
	}
}
bool Play::Flash(const int pos_x, const int pos_y,
	const bool light_on, const int nowlight)
{
	bool stop = false;

	if (light_on) {
		//マップを光らせて更新する
		if (LightUpMap[pos_y][pos_x] != NOTLIGHTUP) {
			LightUpMap[pos_y][pos_x]++;
		}
		else {
			switch (Map[pos_y][pos_x]) {
			case GOAL:
				break;

			case WALL:
				Map[pos_y][pos_x] = LIGHTUPWALL;
			default:
				stop = true;
				break;
			}
		}

		//ギミックに対する動き
		switch (Gimmick[pos_y][pos_x]) {
			//鏡鯛
		case MIRROR_U:
		case MIRROR_D:
			Map[pos_y][pos_x] = LUMINOUS; //発光
			Reflection(pos_x, pos_y, nowlight);
		}
	}
	else {
		//光を消す
		if (LightUpMap[pos_y][pos_x] > 0) {
			LightUpMap[pos_y][pos_x]--;
		}
		else {
			switch (Map[pos_y][pos_x]) {
			case GOAL:
				break;

			default:
				stop = true;
				LightOk[nowlight] = true;
				break;
			}
		}

		//ギミックに対する動き
		switch (Gimmick[pos_y][pos_x]) {
			//鏡鯛
		case MIRROR_U:
		case MIRROR_D:
			Reflection(pos_x, pos_y, nowlight);

			//オニキンメ
		case MOB_1:
			break;

			//アンコウ
		case MOB_2:
			break;
		}
	}

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (LightUpMap[i][j] > 0) {
				Map[i][j] = LUMINOUS;
			}
			else if (Map[i][j] == LUMINOUS) {
				Map[i][j] = SPACE;
			}
			else {
				Map[i][j] = Map[i][j];
			}
		}
	}

	return stop;
}
void Play::Reflection(const int pos_x, const int pos_y, const int nowlight)
{
	//鏡鯛（右上がり
	if (Gimmick[pos_y][pos_x] == MIRROR_U) {
		switch (keep_Direction[nowlight]) {
		case UP:
			keep_Direction[nowlight] = RIGHT;
			break;
		case DOWN:
			keep_Direction[nowlight] = LEFT;
			break;
		case RIGHT:
			keep_Direction[nowlight] = UP;
			break;
		case LEFT:
			keep_Direction[nowlight] = DOWN;
			break;
		}
	}
	//鏡鯛（右下がり
	else {
		switch (keep_Direction[nowlight]) {
		case UP:
			keep_Direction[nowlight] = LEFT;
			break;
		case DOWN:
			keep_Direction[nowlight] = RIGHT;
			break;
		case RIGHT:
			keep_Direction[nowlight] = DOWN;
			break;
		case LEFT:
			keep_Direction[nowlight] = UP;
			break;
		}
	}
}

//マップ関連
void Play::MapUpdate()
{
	Map[new_pos_y][new_pos_x] = Map[old_pos_y][old_pos_x];
	Map[old_pos_y][old_pos_x] = MAP_END;
	LightPos_x[light_number] = new_pos_x;
	LightPos_y[light_number] = new_pos_y;
	DebugMap();
}
void Play::DebugMap()
{
	std::cout << "マップ更新:Light" << std::endl;
	//デバッグ	マップ数値表示
	for (int i = 0; i < 18; i++) {
		for (int j = 0; j < 32; j++) {
			std::cout << Map[i][j] << ",";
		}
		std::cout << std::endl;
	}
	//======================
}

//値を返す
float Play::GetAngle(int y, int x)
{
	for (int light = 0; light < light_max; light++) {
		if (LightPos_x[light] == x && LightPos_y[light] == y) {
			switch (Direction[light]) {
			case UP:
				return 0.0f;
				break;

			case DOWN:
				return 180.0f;
				break;
			case RIGHT:
				return 270.0f;
				break;
			case LEFT:
				return 90.0f;
				break;
			}
		}
	}

	return 0.0f;
}