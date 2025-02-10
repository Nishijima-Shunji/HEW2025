#include "File.h"
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

void SaveFile(int map, int mendako)
{
	ofstream fout;

	string filename = "SaveData/map";
	filename += to_string(map);
	filename.append(".bin");

	fout.open(filename, ios::out | ios::binary);
	if (fout.is_open()) {
		fout.write((char*)&mendako, sizeof(mendako));
	}
	else {
		cout << "ファイルが開けませんでした" << endl;
	}
	fout.close();
}

int LoadFile(int map)
{
	int mendako;
	ifstream fin;

	string filename = "SaveData/map";
	filename += to_string(map);
	filename.append(".bin");

	fin.open(filename, ios::in | ios::binary);

	if (fin.is_open()) {
		fin.read((char*)&mendako, sizeof(mendako));
	}
	else {
		cout << "ファイルが存在しませんでした" << endl;
	}
	fin.close();

	return mendako;
}

void ResetFile()
{
	ofstream fout;
	int map = 1, mendako = 0;

	for (map; map < 9; map++) {
		string filename = "SaveData/map";
		filename += to_string(map);
		filename.append(".bin");

		fout.open(filename, ios::out | ios::binary);
		if (fout.is_open()) {
			fout.write((char*)&mendako, sizeof(mendako));
		}
		else {
			cout << "ファイルが開けませんでした" << endl;
		}
		fout.close();
	}
}

void SaveDirection(int direction, int num)
{
	ofstream fout;

	string filename = "SaveData/direction";
	filename += to_string(num);
	filename.append(".bin");

	fout.open(filename, ios::out | ios::binary);
	if (fout.is_open()) {
		fout.write((char*)&direction, sizeof(direction));
	}
	else {
		cout << "ファイルが開けませんでした" << endl;
	}
	fout.close();
}

int LoadDirection(int num)
{
	int direction;
	ifstream fin;

	string filename = "SaveData/direction";
	filename += to_string(num);
	filename.append(".bin");

	fin.open(filename, ios::in | ios::binary);

	if (fin.is_open()) {
		fin.read((char*)&direction, sizeof(direction));
	}
	else {
		cout << "ファイルが存在しませんでした" << endl;
	}
	fin.close();

	return direction;
}