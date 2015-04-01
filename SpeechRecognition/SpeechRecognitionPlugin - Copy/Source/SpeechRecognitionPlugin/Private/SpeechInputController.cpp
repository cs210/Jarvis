
#include "SpeechRecognitionPluginPrivatePCH.h"
#include "SpeechInputController.h"
#include "SpeechEventInterface.h"

USpeechInputController::USpeechInputController(const FObjectInitializer &init) :
	UActorComponent(init)
{

}

void USpeechInputController::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	InterfaceEventTick(DeltaTime);
}

/*
void USpeechInputController::OnRegister() {

}
*/

void USpeechInputController::InterfaceEventTick(float DeltaTime) {
	//SpeechEventColor.Broadcast();
	/*
	auto t = Cast<ISpeechEventInterface>(this);
	if (t != nullptr) {
		TScriptInterface<ISpeechEventInterface> s = TScriptInterface<ISpeechEventInterface>();
		s.SetObject(this);
		s.SetInterface(t);
		t->Execute_SpeechEventColor(this);
	}
	*/

	ticks++;
}