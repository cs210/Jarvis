
#pragma once

#include "Core.h"
#include "CoreUObject.h"
#include "Engine.h"
#include "Engine/EngineTypes.h"
#include "AssetRegistryModule.h"

//#include <sphinxbase/err.h>
//#include <sphinxbase/ad.h>

//#include "pocketsphinx.h"

#include "SpeechRecognizer.h"
#include "JarvisPluginPrivatePCH.h"
#include "JarvisFunctionLibrary.generated.h"
 
//above name must match the name on your hard disk for this .h file

DECLARE_LOG_CATEGORY_EXTERN(UserActionsLog, Log, All);
 
//note about UBlueprintFunctionLibrary
// This class is a base class for any function libraries exposed to blueprints.
// Methods in subclasses are expected to be static
 
//===========================================
// Enum type for user actions
//===========================================

UENUM(BlueprintType)
enum class EAction : uint8
{
	VE_Translate UMETA(DisplayName = "VE_Translate"),
	VE_Rotate	 UMETA(DisplayName = "VE_Rotate"),
	VE_Scale	 UMETA(DisplayName = "VE_Scale"),
	//VE_Delete	 UMETA(DisplayName = "VE_Delete"),
	//VE_Invalid	 UMETA(DisplayName = "VE_Invalid")
};

USTRUCT()
struct FActorState
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	AActor* Actor;

	UPROPERTY()
	FVector Location;

	UPROPERTY()
	FVector Scale;

	UPROPERTY()
	FRotator Rotation;
};

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

		//UFUNCTION(BlueprintCallable, Category = "SpeechRecognitionLibrary")
		//static FString GetUserCommand();

		UFUNCTION(BlueprintCallable, Category = "SpeechRecognitionLibrary")
		static void GetUserCommand_Mod();

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

		UFUNCTION(BlueprintCallable, Category = "Undo|Redo")
		static void CaptureActorState(AActor* Actor);

		UFUNCTION(BlueprintCallable, Category = "Undo|Redo")
		static void Redo();

		UFUNCTION(BlueprintCallable, Category = "Undo|Redo")
		static void Undo();

		// Helper methods
		static void AddMeshToCollection(FString collection, UStaticMesh* mesh);
		static void PrintCollectionToMeshesMap();

		static void SetActorState(FActorState* A); // Used by the undo/redo functionality
		static void LogFActorState(FActorState* A);
		static FActorState* GetActorState(AActor* Actor);

		//static void InitializePocketSphinxRecognizer();
		//static void SleepMilliSec(int32 ms);
		//static void ReadAudioBuffer();

		~UJarvisFunctionLibrary();	

	private:
		FRunnableThread* Thr;
		
};

static TMap<FString, TArray<UStaticMesh*>> collectionToMeshes;
static SpeechRecognizer* SpeechRecognitionThread = new SpeechRecognizer();

static TArray<FActorState*> UndoSnapshots;
static TArray<FActorState*> RedoSnapshots;

/*
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