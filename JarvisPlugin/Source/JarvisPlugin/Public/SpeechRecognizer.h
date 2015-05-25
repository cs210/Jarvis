#pragma once

#include <sphinxbase/err.h>
#include <sphinxbase/ad.h>
#include "pocketsphinx.h"

#include "JarvisPluginPrivatePCH.h"
//#include "SpeechRecognizer.generated.h"

class SpeechRecognizer
	: public FRunnable
{
public:

	/** Default constructor. */
	SpeechRecognizer();

	/** Destructor. */
	~SpeechRecognizer();

	bool EnqueueCommand(int command);
	bool IsResultPending();

	//int GetResult();
	FString GetResult();

	// FRunnable interface
	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Stop() override;
	virtual void Exit() override;

	static const int CMD_STOP = 0;
	static const int CMD_GET_USER_INPUT = 1;

private:

	void InitializePocketSphinxRecognizer();
	FString ProcessUserCommand();
	void ReadAudioBuffer();

	TQueue< int > Commands;
	//TQueue< int > Results;
	TQueue< FString > Results;
	FEvent* WorkEvent;

	int Count = 0;

	ps_decoder_t *ps;
	cmd_ln_t *config;

	ad_rec_t *ad;
	int16 adbuf[2048];
	uint8 utt_started, in_speech;
	int32 k;
	char const *hyp;

	FString default_user_command = FString(ANSI_TO_TCHAR("UNK"));
};

static arg_t cont_args_def[] = {
	POCKETSPHINX_OPTIONS,
	/* Argument file. */
	{ "-argfile",
	ARG_STRING,
	NULL,
	"Argument file giving extra arguments." },
	{ "-adcdev",
	ARG_STRING,
	NULL,
	"Name of audio device to use for input." },
	{ "-infile",
	ARG_STRING,
	NULL,
	"Audio file to transcribe." },
	{ "-inmic",
	ARG_BOOLEAN,
	"no",
	"Transcribe audio from microphone." },
	{ "-time",
	ARG_BOOLEAN,
	"no",
	"Print word times in file transcription." },
	CMDLN_EMPTY_OPTION
};
