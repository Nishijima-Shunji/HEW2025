#include "sound.h"

#ifdef _XBOX //Big-Endian
#define fourccRIFF 'RIFF'
#define fourccDATA 'data'
#define fourccFMT 'fmt '
#define fourccWAVE 'WAVE'
#define fourccXWMA 'XWMA'
#define fourccDPDS 'dpds'
#endif
#ifndef _XBOX //Little-Endian
#define fourccRIFF 'FFIR'
#define fourccDATA 'atad'
#define fourccFMT ' tmf'
#define fourccWAVE 'EVAW'
#define fourccXWMA 'AMWX'
#define fourccDPDS 'sdpd'
#endif

//=============================================================================
// ������
//=============================================================================
Sound::Sound()
{
	Init();
}

Sound::~Sound()
{
	ReleaseBGM();
	Uninit();
}

HRESULT Sound::Init()
{
	HRESULT hr;

	HANDLE hFile;
	DWORD  dwChunkSize;
	DWORD  dwChunkPosition;
	DWORD  filetype;

	// COM�̏�����
	hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
	if (FAILED(hr)) {
		CoUninitialize();
		return -1;
	}

	/**** Create XAudio2 ****/
	hr = XAudio2Create(&m_pXAudio2, 0);		// �������ͤ����t���O �f�o�b�O���[�h�̎w��(���݂͖��g�p�Ȃ̂�0�ɂ���)
	//hr=XAudio2Create(&g_pXAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR);		// ��O�����́Awindows�ł͖���
	if (FAILED(hr)) {
		CoUninitialize();
		return -1;
	}

	/**** Create Mastering Voice ****/
	hr = m_pXAudio2->CreateMasteringVoice(&m_pMasteringVoice);			// ����͂o�b�̃f�t�H���g�ݒ�ɔC���Ă���
	/*, XAUDIO2_DEFAULT_CHANNELS, XAUDIO2_DEFAULT_SAMPLERATE, 0, 0, NULL*/		// �{���U�̈����������Ă���
	if (FAILED(hr)) {
		if (m_pXAudio2)	m_pXAudio2->Release();
		CoUninitialize();
		return -1;
	}

	/**** Initalize Sound ****/
	for (int i = 0; i < SOUND_LABEL_SE_MAX; i++)
	{
		memset(&m_wfx[i], 0, sizeof(WAVEFORMATEXTENSIBLE));
		memset(&m_buffer[i], 0, sizeof(XAUDIO2_BUFFER));

		hFile = CreateFileA(m_param_SE[i].filename, GENERIC_READ, FILE_SHARE_READ, NULL,
			OPEN_EXISTING, 0, NULL);
		if (hFile == INVALID_HANDLE_VALUE) {
			return HRESULT_FROM_WIN32(GetLastError());
		}
		if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER) {
			return HRESULT_FROM_WIN32(GetLastError());
		}

		//check the file type, should be fourccWAVE or 'XWMA'
		FindChunk(hFile, fourccRIFF, dwChunkSize, dwChunkPosition);
		ReadChunkData(hFile, &filetype, sizeof(DWORD), dwChunkPosition);
		if (filetype != fourccWAVE)		return S_FALSE;

		FindChunk(hFile, fourccFMT, dwChunkSize, dwChunkPosition);
		ReadChunkData(hFile, &m_wfx[i], dwChunkSize, dwChunkPosition);

		//fill out the audio data buffer with the contents of the fourccDATA chunk
		FindChunk(hFile, fourccDATA, dwChunkSize, dwChunkPosition);
		m_DataBuffer[i] = new BYTE[dwChunkSize];
		ReadChunkData(hFile, m_DataBuffer[i], dwChunkSize, dwChunkPosition);

		CloseHandle(hFile);

		// 	�T�u�~�b�g�{�C�X�ŗ��p����T�u�~�b�g�o�b�t�@�̐ݒ�
		m_buffer[i].AudioBytes = dwChunkSize;
		m_buffer[i].pAudioData = m_DataBuffer[i];
		m_buffer[i].Flags = XAUDIO2_END_OF_STREAM;
		m_buffer[i].LoopCount = 0;

		m_pXAudio2->CreateSourceVoice(&m_pSourceVoice[i], &(m_wfx[i].Format));
	}

	return hr;
}

HRESULT Sound::RoadBGM(SOUND_LABEL_BGM label)
{
	HRESULT hr;

	HANDLE hFile;
	DWORD  dwChunkSize;
	DWORD  dwChunkPosition;
	DWORD  filetype;

	// COM�̏�����
	hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
	if (FAILED(hr)) {
		CoUninitialize();
		return -1;
	}

	/**** Create XAudio2 ****/
	hr = XAudio2Create(&m_pXAudio2, 0);		// �������ͤ����t���O �f�o�b�O���[�h�̎w��(���݂͖��g�p�Ȃ̂�0�ɂ���)
	//hr=XAudio2Create(&g_pXAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR);		// ��O�����́Awindows�ł͖���
	if (FAILED(hr)) {
		CoUninitialize();
		return -1;
	}

	/**** Create Mastering Voice ****/
	hr = m_pXAudio2->CreateMasteringVoice(&m_pMasteringVoice);			// ����͂o�b�̃f�t�H���g�ݒ�ɔC���Ă���
	/*, XAUDIO2_DEFAULT_CHANNELS, XAUDIO2_DEFAULT_SAMPLERATE, 0, 0, NULL*/		// �{���U�̈����������Ă���
	if (FAILED(hr)) {
		if (m_pXAudio2)	m_pXAudio2->Release();
		CoUninitialize();
		return -1;
	}

	/**** Initalize Sound ****/
	memset(&m_wfx_BGM, 0, sizeof(WAVEFORMATEXTENSIBLE));
	memset(&m_buffer_BGM, 0, sizeof(XAUDIO2_BUFFER));

	hFile = CreateFileA(m_param_BGM[label].filename, GENERIC_READ, FILE_SHARE_READ, NULL,
		OPEN_EXISTING, 0, NULL);
	if (hFile == INVALID_HANDLE_VALUE) {
		return HRESULT_FROM_WIN32(GetLastError());
	}
	if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER) {
		return HRESULT_FROM_WIN32(GetLastError());
	}

	//check the file type, should be fourccWAVE or 'XWMA'
	FindChunk(hFile, fourccRIFF, dwChunkSize, dwChunkPosition);
	ReadChunkData(hFile, &filetype, sizeof(DWORD), dwChunkPosition);
	if (filetype != fourccWAVE)		return S_FALSE;

	FindChunk(hFile, fourccFMT, dwChunkSize, dwChunkPosition);
	ReadChunkData(hFile, &m_wfx_BGM, dwChunkSize, dwChunkPosition);

	//fill out the audio data buffer with the contents of the fourccDATA chunk
	FindChunk(hFile, fourccDATA, dwChunkSize, dwChunkPosition);
	m_DataBuffer_BGM = new BYTE[dwChunkSize];
	ReadChunkData(hFile, m_DataBuffer_BGM, dwChunkSize, dwChunkPosition);

	CloseHandle(hFile);

	// 	�T�u�~�b�g�{�C�X�ŗ��p����T�u�~�b�g�o�b�t�@�̐ݒ�
	m_buffer_BGM.AudioBytes = dwChunkSize;
	m_buffer_BGM.pAudioData = m_DataBuffer_BGM;
	m_buffer_BGM.Flags = XAUDIO2_END_OF_STREAM;
	m_buffer_BGM.LoopCount = XAUDIO2_LOOP_INFINITE;

	m_pXAudio2->CreateSourceVoice(&m_pSourceVoice_BGM, &(m_wfx_BGM.Format));

	pSV_BGM = m_pSourceVoice_BGM;

	return hr;
}

//=============================================================================
// �J������
//=============================================================================
void Sound::Uninit(void)
{
	for (int i = 0; i < SOUND_LABEL_SE_MAX; i++)
	{
		if (m_pSourceVoice[i])
		{
			m_pSourceVoice[i]->Stop(0);
			m_pSourceVoice[i]->FlushSourceBuffers();
			m_pSourceVoice[i]->DestroyVoice();			// �I�[�f�B�I�O���t����\�[�X�{�C�X���폜
			delete[]  m_DataBuffer[i];
		}
	}

	m_pMasteringVoice->DestroyVoice();

	if (m_pXAudio2) m_pXAudio2->Release();

	// COM�̔j��
	CoUninitialize();
}

void Sound::ReleaseBGM()
{
	XAUDIO2_VOICE_STATE xa2state;
	m_pSourceVoice_BGM->GetState(&xa2state);
	if (xa2state.BuffersQueued)
	{
		m_pSourceVoice_BGM->Stop(0);
	}

	if (m_pSourceVoice_BGM)
	{
		m_pSourceVoice_BGM->Stop(0);
		m_pSourceVoice_BGM->FlushSourceBuffers();
		m_pSourceVoice_BGM->DestroyVoice();			// �I�[�f�B�I�O���t����\�[�X�{�C�X���폜
		delete[]  m_DataBuffer_BGM;
	}
}

//=============================================================================
// �Đ�
//=============================================================================
void Sound::PlaySE(SOUND_LABEL_SE label)
{
	IXAudio2SourceVoice*& pSV = m_pSourceVoice[(int)label];

	if (pSV != nullptr)
	{
		pSV->DestroyVoice();
		pSV = nullptr;
	}

	// �\�[�X�{�C�X�쐬
	m_pXAudio2->CreateSourceVoice(&pSV, &(m_wfx[(int)label].Format));
	pSV->SubmitSourceBuffer(&(m_buffer[(int)label]));	// �{�C�X�L���[�ɐV�����I�[�f�B�I�o�b�t�@�[��ǉ�

	//���ʒ���
	pSV->SetVolume(SE_vol);
	// �Đ�
	pSV->Start(0);
}

void Sound::PlayBGM()
{
	//pSV_BGM = m_pSourceVoice_BGM;

	if (pSV_BGM != nullptr)
	{
		pSV_BGM->DestroyVoice();
		pSV_BGM = nullptr;
	}

	// �\�[�X�{�C�X�쐬
	m_pXAudio2->CreateSourceVoice(&pSV_BGM, &(m_wfx_BGM.Format));
	pSV_BGM->SubmitSourceBuffer(&(m_buffer_BGM));	// �{�C�X�L���[�ɐV�����I�[�f�B�I�o�b�t�@�[��ǉ�

	//���ʒ���
	pSV_BGM->SetVolume(BGM_vol);
	// �Đ�
	pSV_BGM->Start(0);
}

//=============================================================================
// ��~
//=============================================================================
void Sound::StopBGM()
{
	if (m_pSourceVoice_BGM == NULL) return;

	XAUDIO2_VOICE_STATE xa2state;
	m_pSourceVoice_BGM->GetState(&xa2state);
	if (xa2state.BuffersQueued)
	{
		m_pSourceVoice_BGM->Stop(0);
	}
}

//=============================================================================
// �ꎞ��~
//=============================================================================
void Sound::ResumeBGM()
{
	IXAudio2SourceVoice*& pSV = m_pSourceVoice_BGM;
	pSV->Start();
}

//=============================================================================
//�ݒ�
//=============================================================================
void Sound::SetVolSE(const float _vol)
{
	SE_vol = _vol;

	if (SE_vol < 0.0f) {
		SE_vol = 0.0f;
	}
}

void Sound::SetVolBGM(const float _vol)
{
	BGM_vol = _vol;
	if (BGM_vol < 0.0f) {
		BGM_vol = 0.0f;
	}
	//���ʒ���
	pSV_BGM->SetVolume(BGM_vol);
}

//=============================================================================
// ���[�e�B���e�B�֐��Q
//=============================================================================
HRESULT Sound::FindChunk(HANDLE hFile, DWORD fourcc, DWORD& dwChunkSize, DWORD& dwChunkDataPosition)
{
	HRESULT hr = S_OK;
	if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, 0, NULL, FILE_BEGIN))
		return HRESULT_FROM_WIN32(GetLastError());
	DWORD dwChunkType;
	DWORD dwChunkDataSize;
	DWORD dwRIFFDataSize = 0;
	DWORD dwFileType;
	DWORD bytesRead = 0;
	DWORD dwOffset = 0;
	while (hr == S_OK)
	{
		DWORD dwRead;
		if (0 == ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL))
			hr = HRESULT_FROM_WIN32(GetLastError());
		if (0 == ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL))
			hr = HRESULT_FROM_WIN32(GetLastError());
		switch (dwChunkType)
		{
		case fourccRIFF:
			dwRIFFDataSize = dwChunkDataSize;
			dwChunkDataSize = 4;
			if (0 == ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL))
				hr = HRESULT_FROM_WIN32(GetLastError());
			break;
		default:
			if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT))
				return HRESULT_FROM_WIN32(GetLastError());
		}
		dwOffset += sizeof(DWORD) * 2;
		if (dwChunkType == fourcc)
		{
			dwChunkSize = dwChunkDataSize;
			dwChunkDataPosition = dwOffset;
			return S_OK;
		}
		dwOffset += dwChunkDataSize;
		if (bytesRead >= dwRIFFDataSize) return S_FALSE;
	}
	return S_OK;
}

HRESULT Sound::ReadChunkData(HANDLE hFile, void* buffer, DWORD buffersize, DWORD bufferoffset)
{
	HRESULT hr = S_OK;
	if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, bufferoffset, NULL, FILE_BEGIN))
		return HRESULT_FROM_WIN32(GetLastError());
	DWORD dwRead;
	if (0 == ReadFile(hFile, buffer, buffersize, &dwRead, NULL))
		hr = HRESULT_FROM_WIN32(GetLastError());
	return hr;
}