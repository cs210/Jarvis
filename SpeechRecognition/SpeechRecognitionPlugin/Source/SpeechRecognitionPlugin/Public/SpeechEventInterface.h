
#pragma once
#include "SpeechEventInterface.generated.h"

UINTERFACE(MinimalAPI)
class USpeechEventInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class ISpeechEventInterface
{
	GENERATED_IINTERFACE_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent, meta = (FriendlyName = "SpeechInputColor", CompactNodeTitle = "", Keywords = "Speech Input Color"), Category = "Speech Input Event")
    void SpeechEventColor();

    UFUNCTION(BlueprintImplementableEvent, meta = (FriendlyName = "SpeechInputTexture", CompactNodeTitle = "", Keywords = "Speech Input Texture"), Category = "Speech Input Event")
	void SpeechEventTexture();

};
