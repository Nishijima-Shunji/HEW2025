#pragma once
#include "Object.h"
#include "Input.h"
#include "sound.h"

class SoundCursol : public Object
{
private:
	float val = 0.05f;
public:
	float Update(Input*);
};