#pragma once

#include <xaudio2.h>

//SE�����
typedef enum
{
	SE01 = 0,

	SOUND_LABEL_SE_MAX
} SOUND_LABEL_SE;

//BGM�����
typedef enum
{
	BGM01 = 0,
	BGM02 = 1,
	BGM03 = 2,
	BGM04 = 3,

	SOUND_LABEL_BGM_MAX
} SOUND_LABEL_BGM;

class Sound {
private:
	Sound();
	~Sound();

	// �Q�[�����[�v�J�n�O�ɌĂяo���T�E���h�̏���������
	HRESULT Init(void);
	// �Q�[�����[�v�I����ɌĂяo���T�E���h�̉������
	void Uninit(void);

	// �p�����[�^�\����
	//SE�̃p�����[�^
	typedef struct
	{
		LPCSTR filename;	// �����t�@�C���܂ł̃p�X��ݒ�
	} PARAM_SE;
	PARAM_SE m_param_SE[SOUND_LABEL_SE_MAX] =
	{
		{"asset/SE/JUMPSE.wav"} ,		//�i���[�v���Ȃ��̂�false�ݒ�j
	};

	//BGM�̃p�����[�^
	typedef struct
	{
		LPCSTR filename;
	} PARAM_BGM;
	PARAM_BGM m_param_BGM[SOUND_LABEL_BGM_MAX] =
	{
		{"asset/BGM/S1.wav"},	//���[�v������̂�true�ݒ�
		{"asset/BGM/Map01BGM.wav"},
	};

	//���[�h�p�Ɏg���ϐ�
	IXAudio2* m_pXAudio2 = NULL;
	IXAudio2MasteringVoice* m_pMasteringVoice = NULL;
	IXAudio2SourceVoice* m_pSourceVoice[SOUND_LABEL_SE_MAX];
	WAVEFORMATEXTENSIBLE m_wfx[SOUND_LABEL_SE_MAX]; // WAV�t�H�[�}�b�g
	XAUDIO2_BUFFER m_buffer[SOUND_LABEL_SE_MAX];
	BYTE* m_DataBuffer[SOUND_LABEL_SE_MAX];

	IXAudio2SourceVoice* m_pSourceVoice_BGM;
	WAVEFORMATEXTENSIBLE m_wfx_BGM; // WAV�t�H�[�}�b�g
	XAUDIO2_BUFFER m_buffer_BGM;
	BYTE* m_DataBuffer_BGM;

	HRESULT FindChunk(HANDLE, DWORD, DWORD&, DWORD&);
	HRESULT ReadChunkData(HANDLE, void*, DWORD, DWORD);

	float BGM_vol = 1.0f, SE_vol = 1.0f;

	IXAudio2SourceVoice* pSV_BGM = m_pSourceVoice_BGM;

public:
	static Sound& GetInstance() {
		static Sound instance;
		return instance;
	}

	//BGM�̃��[�h�Ŏg�p
	HRESULT RoadBGM(SOUND_LABEL_BGM label);

	// �����Ŏw�肵���T�E���h���Đ�����
	void PlaySE(SOUND_LABEL_SE label);
	void PlayBGM();

	// �����Ŏw�肵���T�E���h���~����
	void StopBGM();

	// �����Ŏw�肵���T�E���h�̍Đ����ĊJ����
	void ResumeBGM();

	//BGM�̍폜
	void ReleaseBGM();

	//�{�����[���̒���
	void SetVolSE(const float _vol);
	void SetVolBGM(const float _vol);
};

#define g_Sound Sound::GetInstance()