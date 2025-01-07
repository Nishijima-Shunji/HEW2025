//*****************************************************************************
//!	@file	ファイル名
//!	@brief	簡単な説明
//!	@note	メモ
//!	@author	製作者
//*****************************************************************************

//-----------------------------------------------------------------------------
//	Include header files.
//-----------------------------------------------------------------------------
#include "mapfile.h"
#include <iostream>
#include <fstream>
#include <sstream>

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

#include "mapfile.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <locale>
#include <codecvt>

std::vector<std::vector<int>> Loadmap(const wchar_t* filePath) {
    std::vector<std::vector<int>> DataTable(MAP_HEIGHT, std::vector<int>(MAP_WIDTH, -1));

    // ファイルを開く
    std::wifstream fileStream(filePath);
    fileStream.imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t>)); // UTF-8 をサポート
    if (!fileStream) {
        std::wcerr << L"ファイルオープン失敗: " << filePath << std::endl;
        return DataTable;
    }

    std::wstring bufferString;

    // 1行目の読み込みとBOMのチェック
    if (std::getline(fileStream, bufferString)) {
        const std::wstring BOM = L"\xFEFF"; // UTF-16 BOM
        if (bufferString.compare(0, BOM.size(), BOM) == 0) {
            bufferString.erase(0, BOM.size());
        }
    }

    int i = 0;

    // ファイルの読み込みループ
    do {
        if (bufferString.empty()) continue;

        i++;
        std::wistringstream stringStream(bufferString);
        std::vector<std::wstring> datas;
        std::wstring tmp;

        // カンマ区切りでデータを切り分け
        while (std::getline(stringStream, tmp, L',')) {
            datas.push_back(tmp);
        }

        if (i <= MAP_HEIGHT) {
            // 各番号を配列に格納
            for (int j = 0; j < MAP_WIDTH; j++) {
                DataTable[i - 1][j] = (j < datas.size() && !datas[j].empty())
                    ? std::wcstol(datas[j].c_str(), nullptr, 10)
                    : -1;
            }
        }
    } while (std::getline(fileStream, bufferString));

    // ファイルクローズ
    fileStream.close();
    return DataTable;
}
