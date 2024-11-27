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
std::vector<std::vector<int>> Loadmap(const char* filePath) {
    std::vector<std::vector<int>> DataTable(MAP_HEIGHT, std::vector<int>(MAP_WIDTH));

    // �t�@�C�����J��
    std::ifstream fileStream(filePath);
    if (!fileStream) {
        std::cout << "�t�@�C���I�[�v�����s" << std::endl;
        return DataTable;
    }

    std::string bufferString;

    // 1�s�ڂ̓ǂݍ��݂�BOM�̃`�F�b�N
    if (std::getline(fileStream, bufferString)) {
        // BOM�����o���č폜
        const std::string BOM = "\xEF\xBB\xBF"; // UTF-8 BOM�@�폜
        if (bufferString.compare(0, BOM.size(), BOM) == 0) {
            bufferString.erase(0, BOM.size());
        }
    }

    // ���s�ڂ�
    int i = 0;

    // �t�@�C�����I���܂œǂݍ���
    do {
        if (bufferString.empty()) continue;

        i++;
        std::istringstream stringStream(bufferString);
        std::vector<std::string> datas;
        std::string tmp;

        // �J���}��؂�Ńf�[�^��؂蕪��
        while (std::getline(stringStream, tmp, ',')) {
            datas.push_back(tmp);
        }

        if (i <= MAP_HEIGHT) {
            // �e�ԍ���z��Ɋi�[
            for (int j = 0; j < MAP_WIDTH; j++) {
                // �󔒂△���l�̏ꍇ��0��ݒ�
                DataTable[i - 1][j] = (j < datas.size() && !datas[j].empty())
                    ? std::strtol(datas[j].c_str(), nullptr, 10)
                    : 0;
            }
        }
    } while (std::getline(fileStream, bufferString));

    // �t�@�C���N���[�Y
    fileStream.close();
    return DataTable;
}


//******************************************************************************
//	End of file.
//******************************************************************************
