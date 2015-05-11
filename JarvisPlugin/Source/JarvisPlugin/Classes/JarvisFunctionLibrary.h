
#pragma once

#include "Core.h"
#include "CoreUObject.h"
#include "Engine.h"
#include "Engine/EngineTypes.h"
#include "AssetRegistryModule.h"

#include <sphinxbase/err.h>
#include <sphinxbase/ad.h>

#include "pocketsphinx.h"

#include "JarvisPluginPrivatePCH.h"
#include "JarvisFunctionLibrary.generated.h"
 
//above name must match the name on your hard disk for this .h file

DECLARE_LOG_CATEGORY_EXTERN(UserActionsLog, Log, All);
 
//note about UBlueprintFunctionLibrary
// This class is a base class for any function libraries exposed to blueprints.
// Methods in subclasses are expected to be static
 
UCLASS()
class UJarvisFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()
 
	public:
		/** Saves text to filename of your choosing, make sure include whichever file extension you want in the filename, ex: SelfNotes.txt . Make sure to include the entire file path in the save directory, ex: C:\MyGameDir\BPSavedTextFiles */
		UFUNCTION(BlueprintCallable, Category = "JarvisFunctionLibrary")
		static bool SaveStringTextToFile(FString SaveDirectory, FString FileName, bool AllowOverWriting = false);

		UFUNCTION(BlueprintCallable, Category = "MenuFunctionLibrary")
		static TArray<FString> LoadMeshCollections(FString directoryPath);

		UFUNCTION(BlueprintCallable, Category = "MenuFunctionLibrary")
		static TArray<UStaticMesh*> GetMeshesFromCollection(FString collectionName);

		UFUNCTION(BlueprintCallable, Category = "MenuFunctionLibrary")
		static UStaticMesh* LoadStaticMesh(FString ObjectPath);

		UFUNCTION(BlueprintCallable, Category = "SpeechRecognitionLibrary")
		static FString GetUserCommand();

		/**
		* Sets the World to Meters scale, which changes the scale of the world as perceived by the player
		*
		* @param NewScale	Specifies how many Unreal units correspond to one meter in the real world
		*/
		UFUNCTION(BlueprintCallable, Category = "Input|HeadMountedDisplay", meta = (WorldContext = "WorldContext"))
		static void SetWorldToMetersScale(UObject* WorldContext, float NewScale = 100.f);

		/**
		* Returns the World to Meters scale, which corresponds to the scale of the world as perceived by the player
		*
		* @return	How many Unreal units correspond to one meter in the real world
		*/
		UFUNCTION(BlueprintPure, Category = "Input|HeadMountedDisplay", meta = (WorldContext = "WorldContext"))
		static float GetWorldToMetersScale(UObject* WorldContext);

		UFUNCTION(BlueprintCallable, Category = "LogLibrary")
		static void LogUserAction(FString msg);

		// Helper methods
		static void AddMeshToCollection(FString collection, UStaticMesh* mesh);
		static void PrintCollectionToMeshesMap();
		static void InitializePocketSphinxRecognizer();
		static void SleepMilliSec(int32 ms);
		static void ReadAudioBuffer();
};

static TMap<FString, TArray<UStaticMesh*>> collectionToMeshes;

static ps_decoder_t *ps;
static cmd_ln_t *config;

static ad_rec_t *ad;
static int16 adbuf[2048];
static uint8 utt_started, in_speech;
static int32 k;
static char const *hyp;

static FString default_user_command = FString(ANSI_TO_TCHAR("UNK"));

static const arg_t cont_args_def[] = {
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