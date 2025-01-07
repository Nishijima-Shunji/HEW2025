//*****************************************************************************
//!	@file	�t�@�C����
//!	@brief	�ȒP�Ȑ���
//!	@note	����
//!	@author	�����
//*****************************************************************************

//-----------------------------------------------------------------------------
//	Include header files.
//-----------------------------------------------------------------------------
#include "mapfile.h"
#include <iostream>
#include <fstream>
#include <sstream>

//-----------------------------------------------------------------------------
// �v���g�^�C�v�錾
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// �O���[�o���ϐ�
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

    // �t�@�C�����J��
    std::wifstream fileStream(filePath);
    fileStream.imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t>)); // UTF-8 ���T�|�[�g
    if (!fileStream) {
        std::wcerr << L"�t�@�C���I�[�v�����s: " << filePath << std::endl;
        return DataTable;
    }

    std::wstring bufferString;

    // 1�s�ڂ̓ǂݍ��݂�BOM�̃`�F�b�N
    if (std::getline(fileStream, bufferString)) {
        const std::wstring BOM = L"\xFEFF"; // UTF-16 BOM
        if (bufferString.compare(0, BOM.size(), BOM) == 0) {
            bufferString.erase(0, BOM.size());
        }
    }

    int i = 0;

    // �t�@�C���̓ǂݍ��݃��[�v
    do {
        if (bufferString.empty()) continue;

        i++;
        std::wistringstream stringStream(bufferString);
        std::vector<std::wstring> datas;
        std::wstring tmp;

        // �J���}��؂�Ńf�[�^��؂蕪��
        while (std::getline(stringStream, tmp, L',')) {
            datas.push_back(tmp);
        }

        if (i <= MAP_HEIGHT) {
            // �e�ԍ���z��Ɋi�[
            for (int j = 0; j < MAP_WIDTH; j++) {
                DataTable[i - 1][j] = (j < datas.size() && !datas[j].empty())
                    ? std::wcstol(datas[j].c_str(), nullptr, 10)
                    : -1;
            }
        }
    } while (std::getline(fileStream, bufferString));

    // �t�@�C���N���[�Y
    fileStream.close();
    return DataTable;
}
