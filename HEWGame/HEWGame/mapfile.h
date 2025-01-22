#pragma once
#include<stdio.h>
#include <string>
#include <vector>
#include<DirectXMath.h>

#define MAP_WIDTH (32)
#define MAP_HEIGHT (18)

std::vector<std::vector<int>> Loadmap(const wchar_t*);