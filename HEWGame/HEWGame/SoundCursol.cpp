#include "SoundCursol.h"

float SoundCursol::Update(Input* input) {
	if (input->GetKeyPress(VK_LEFT) && val > 0.0f) {
		val -= 0.01f;
	}else if (input->GetKeyPress(VK_RIGHT) && val < 1.0f) {
		val += 0.01f;
	}
	pos.x = val * 500.0f - 165.0f;
	return val;
}
