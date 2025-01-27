#pragma once

#include <xaudio2.h>

//SE入れて
typedef enum
{
	SE01 = 0,

	SOUND_LABEL_SE_MAX
} SOUND_LABEL_SE;

//BGM入れて
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

	// ゲームループ開始前に呼び出すサウンドの初期化処理
	HRESULT Init(void);
	// ゲームループ終了後に呼び出すサウンドの解放処理
	void Uninit(void);

	// パラメータ構造体
	//SEのパラメータ
	typedef struct
	{
		LPCSTR filename;	// 音声ファイルまでのパスを設定
	} PARAM_SE;
	PARAM_SE m_param_SE[SOUND_LABEL_SE_MAX] =
	{
		{"asset/SE/JUMPSE.wav"} ,		//（ループしないのでfalse設定）
	};

	//BGMのパラメータ
	typedef struct
	{
		LPCSTR filename;
	} PARAM_BGM;
	PARAM_BGM m_param_BGM[SOUND_LABEL_BGM_MAX] =
	{
		{"asset/BGM/S1.wav"},	//ループさせるのでtrue設定
		{"asset/BGM/Map01BGM.wav"},
	};

	//ロード用に使う変数
	IXAudio2* m_pXAudio2 = NULL;
	IXAudio2MasteringVoice* m_pMasteringVoice = NULL;
	IXAudio2SourceVoice* m_pSourceVoice[SOUND_LABEL_SE_MAX];
	WAVEFORMATEXTENSIBLE m_wfx[SOUND_LABEL_SE_MAX]; // WAVフォーマット
	XAUDIO2_BUFFER m_buffer[SOUND_LABEL_SE_MAX];
	BYTE* m_DataBuffer[SOUND_LABEL_SE_MAX];

	IXAudio2SourceVoice* m_pSourceVoice_BGM;
	WAVEFORMATEXTENSIBLE m_wfx_BGM; // WAVフォーマット
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

	//BGMのロードで使用
	HRESULT RoadBGM(SOUND_LABEL_BGM label);

	// 引数で指定したサウンドを再生する
	void PlaySE(SOUND_LABEL_SE label);
	void PlayBGM();

	// 引数で指定したサウンドを停止する
	void StopBGM();

	// 引数で指定したサウンドの再生を再開する
	void ResumeBGM();

	//BGMの削除
	void ReleaseBGM();

	//ボリュームの調整
	void SetVolSE(const float _vol);
	void SetVolBGM(const float _vol);
};

#define g_Sound Sound::GetInstance()