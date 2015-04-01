
#pragma once

#include "SpeechRecognitionPluginPrivatePCH.h"
#include "SpeechRecognizerFunctionLibrary.h"

class FSpeechRecognizer : public FRunnable 
{

public:

	virtual uint32 Run() override;

	//virtual bool Init() override;

	virtual void Stop() override;

	virtual void Exit() override;

	FSpeechRecognizer();

private:

	bool bStopRecognizer;

};