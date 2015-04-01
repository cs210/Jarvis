
#include "SpeechRecognitionPluginPrivatePCH.h"
#include "ISpeechRecognitionPlugin.h"
#include "SpeechEventInterface.h"

uint32 FSpeechRecognizer::Run() {
	uint32_t i = 0;

	while (!bStopRecognizer) {
		if ((i % 2) == 0) {
			//ISpeechEventInterface::Execute_SpeechInputColor();
		} else {
			//ISpeechEventInterface::Execute_SpeechInputTexture();
		}

		i++;
	}

	return 0;
}

void FSpeechRecognizer::Stop() {
	bStopRecognizer = true;
}

void FSpeechRecognizer::Exit() {

}

FSpeechRecognizer::FSpeechRecognizer() : 
	bStopRecognizer(false)
{
	// Nothing else to do
}