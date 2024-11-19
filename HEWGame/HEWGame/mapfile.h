#pragma once
#include<stdio.h>
#include <string>
#include <vector>
#include<DirectXMath.h>

#define MAP_WIDTH (10)
#define MAP_HEIGHT (7)

std::vector<int> Loadmap(const char* filePath);