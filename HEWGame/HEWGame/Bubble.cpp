#include "Bubble.h"

void Bubble::Update() {
	pos.y += speed;
}

void Bubble::SetSpeed(float spd) {
	speed = spd;
}

float Bubble::GetPosY(){
	return pos.y;
}