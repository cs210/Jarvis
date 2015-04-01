
#pragma once

#include "Core.h"
#include "CoreUObject.h"
#include "Engine.h"
#include "Engine/EngineTypes.h"
#include "SpeechRecognitionPluginPrivatePCH.h"
#include "SpeechRecognizerFunctionLibrary.generated.h"
 
//above name must match the name on your hard disk for this .h file
 
//note about UBlueprintFunctionLibrary
// This class is a base class for any function libraries exposed to blueprints.
// Methods in subclasses are expected to be static
 
UCLASS()
class USpeechRecognizerFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()
 
	/** Saves text to filename of your choosing, make sure include whichever file extension you want in the filename, ex: SelfNotes.txt . Make sure to include the entire file path in the save directory, ex: C:\MyGameDir\BPSavedTextFiles */
	UFUNCTION(BlueprintCallable, Category="SpeechRecognizerFunctionLibrary")
	static bool SaveStringTextToFile(FString SaveDirectory, FString FileName, bool AllowOverWriting = false);
};