
#pragma once
#include "SpeechRecognitionPluginPrivatePCH.h"
#include "SpeechInputController.generated.h"

UCLASS(ClassGroup = Input, meta = (BlueprintSpawnableComponent))
class USpeechInputController : public UActorComponent
{
	GENERATED_UCLASS_BODY()

public:

	//virtual void OnRegister() override;

	//virtual void OnUnregister() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	//UFUNCTION(BlueprintImplementableEvent, meta = (FriendlyName = "SpeechInputColor", CompactNodeTitle = "", Keywords = "Speech Input Color"), Category = "Speech Input Event")
	//void SpeechEventColor();
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSpeechInputControllerUsedDelegate);
	UPROPERTY(BlueprintAssignable, Category = "Ability")
	FSpeechInputControllerUsedDelegate SpeechEventColor;
	

	UFUNCTION(BlueprintImplementableEvent, meta = (FriendlyName = "SpeechInputTexture", CompactNodeTitle = "", Keywords = "Speech Input Texture"), Category = "Speech Input Event")
	void SpeechEventTexture();

private:

	void InterfaceEventTick(float DeltaTime);

	uint32_t ticks = 0;
};