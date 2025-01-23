#include "O2.h"

void O2::Update() {
	switch (state) {
	case 0:
		
		break;
	case 1:
		pos.y -= gravity;
		break;
	}
}