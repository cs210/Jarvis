
#pragma once
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include <sphinxbase/err.h>
#include <sphinxbase/ad.h>

#include "pocketsphinx.h"

#include "JarvisPluginPrivatePCH.h"
#include "SpeechInputController.generated.h"

UCLASS(ClassGroup = Input, meta = (BlueprintSpawnableComponent))
class USpeechInputController : public UActorComponent
{
	GENERATED_UCLASS_BODY()

public:

	virtual void OnRegister() override;

	//virtual void OnUnregister() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	void SetInterfaceDelegate(UObject* newDelegate);

	//void USpeechInputController::InitializePocketSphinxRecognizer();

private:

	//void InterfaceEventTick(float DeltaTime);

	UObject* interfaceDelegate;
	uint32_t ticks = 0;

	// TODO: Refactor these memebers into a separate object: eg: PocketSphinxRecognizer or so

	/*
	ps_decoder_t *ps;
	cmd_ln_t *config;

	ad_rec_t *ad;
	int16 adbuf[2048];
	uint8 utt_started, in_speech;
	int32 k;
	char const *hyp;
	const char *COLOR = "color";
	const char *TEXTURE = "texture";
	*/
};

/*
static const arg_t cont_args_def[] = {
	POCKETSPHINX_OPTIONS,

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
*/