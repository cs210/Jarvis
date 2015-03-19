
#include "SpeechRecognitionPluginPrivatePCH.h"
#include "SpeechInputController.h"
#include "SpeechEventInterface.h"

USpeechInputController::USpeechInputController(const FObjectInitializer &init) :
	UActorComponent(init)
{
	bAutoActivate = true;
	PrimaryComponentTick.bCanEverTick = true;
}

void USpeechInputController::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	InterfaceEventTick(DeltaTime);
}

void USpeechInputController::InterfaceEventTick(float DeltaTime) {
	if ((ticks % 80) < 40)
	{
		ISpeechEventInterface::Execute_SpeechEventColor(interfaceDelegate);
	}
	else
	{
		ISpeechEventInterface::Execute_SpeechEventTexture(interfaceDelegate);
	}
	
	ticks++;
}

void USpeechInputController::OnRegister()
{
	Super::OnRegister();

	SetInterfaceDelegate(GetOwner());
}

void USpeechInputController::SetInterfaceDelegate(UObject* newDelegate)
{
	if (newDelegate->GetClass()->ImplementsInterface(USpeechEventInterface::StaticClass()))
	{
		interfaceDelegate = newDelegate;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("SpeechInputController Warning: Delegate is NOT set, did you implement SpeechEventInterface?"));
	}
}