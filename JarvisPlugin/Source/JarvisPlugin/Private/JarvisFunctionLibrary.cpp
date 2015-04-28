
#include "JarvisPluginPrivatePCH.h"

UJarvisFunctionLibrary::UJarvisFunctionLibrary(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	InitializePocketSphinxRecognizer();
}
 
bool UJarvisFunctionLibrary::SaveStringTextToFile(
	FString SaveDirectory, 
	FString FileName,
	bool AllowOverWriting
){
	//Dir Exists?
	if ( !FPlatformFileManager::Get().GetPlatformFile().DirectoryExists( *SaveDirectory ))
	{
		//create directory if it not exist
		FPlatformFileManager::Get().GetPlatformFile().CreateDirectory( *SaveDirectory );
 
		//still could not make directory?
		if (!FPlatformFileManager::Get().GetPlatformFile().DirectoryExists( *SaveDirectory ))
		{
			//Could not make the specified directory
			return false;
			//~~~~~~~~~~~~~~~~~~~~~~
		}
	}
 
	//get complete file path
	SaveDirectory += "\\";
	SaveDirectory += FileName;
 
	//No over-writing?
	if (!AllowOverWriting)
	{
		//Check if file exists already
		if (FPlatformFileManager::Get().GetPlatformFile().FileExists( * SaveDirectory )) 
		{
			//no overwriting
			return false;
		}
	}
 
	return FFileHelper::SaveStringToFile(FString("Hello blueprint function library!"), * SaveDirectory);
}

TArray<FString> UJarvisFunctionLibrary::GetNamesOfAllStaticMeshes()
{
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	TArray<FAssetData> AssetData;
	FARFilter Filter;
	Filter.ClassNames.Add(FName(*(UStaticMesh::StaticClass()->GetName())));
	AssetRegistryModule.Get().GetAssets(Filter, AssetData);

	TArray<FString> names;
	for (int32 i = 0; i < AssetData.Num(); i++) {
		names.Add(AssetData[i].AssetName.ToString());
	}
	
	return names;
}

TArray<FString> UJarvisFunctionLibrary::GetNamesOfAllMaterials()
{
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	TArray<FAssetData> AssetData;
	FARFilter Filter;
	Filter.ClassNames.Add(FName(*(UMaterial::StaticClass()->GetName())));
	AssetRegistryModule.Get().GetAssets(Filter, AssetData);

	TArray<FString> names;
	for (int32 i = 0; i < AssetData.Num(); i++) {
		names.Add(AssetData[i].AssetName.ToString());
	}

	return names;
}

//============================

void UJarvisFunctionLibrary::SetWorldToMetersScale(UObject* WorldContext, float NewScale)
{
	if (WorldContext)
	{
		WorldContext->GetWorld()->GetWorldSettings()->WorldToMeters = NewScale;
	}
}

float UJarvisFunctionLibrary::GetWorldToMetersScale(UObject* WorldContext)
{
	return WorldContext ? WorldContext->GetWorld()->GetWorldSettings()->WorldToMeters : 0.f;
}

void UJarvisFunctionLibrary::InitializePocketSphinxRecognizer()
{
	//TODO: Parametrize the hard-coded paths below - use configuration files?
	int argc = 9;
	char **argv = (char **)malloc(argc * sizeof(char *));
	argv[0] = "";
	argv[1] = "-inmic"; argv[2] = "yes";
	argv[3] = "-hmm"; argv[4] = "C:\\Users\\Jarvis\\Downloads\\CMUSphinx\\pocketsphinx-5prealpha\\model\\en-us\\en-us";
	argv[5] = "-lm"; argv[6] = "C:\\Users\\Jarvis\\Downloads\\CMUSphinx\\pocketsphinx-5prealpha\\model\\en-us\\en-us.lm.dmp";
	argv[7] = "-dict"; argv[8] = "D:\\Tmp\\cmusphinx_app\\JarvisTestApp1\\model\\jarvis_vocab.dict";

	config = cmd_ln_parse_r(NULL, cont_args_def, argc, argv, TRUE);

	//TODO: Replace calls to the E_* logging functions with calls to appropriate functions exposed by UE
	if (config == NULL || (cmd_ln_str_r(config, "-infile") == NULL && cmd_ln_boolean_r(config, "-inmic") == FALSE)) {
		UE_LOG(LogTemp, Warning, TEXT("Specify '-infile <file.wav>' to recognize from file or '-inmic yes' to recognize from microphone.\n"));
		cmd_ln_free_r(config);
		return;
	}

	ps_default_search_args(config);
	ps = ps_init(config);
	if (ps == NULL) {
		cmd_ln_free_r(config);
		return;
	}

	//E_INFO("%s COMPILED ON: %s, AT: %s\n\n", argv[0], __DATE__, __TIME__);

	if ((ad = ad_open_dev(cmd_ln_str_r(config, "-adcdev"),
		(int)cmd_ln_float32_r(config,
		"-samprate"))) == NULL) {
		UE_LOG(LogTemp, Warning, TEXT("Failed to open audio device\n"));
		return;
	}

	if (ad_start_rec(ad) < 0) {
		UE_LOG(LogTemp, Warning, TEXT("Failed to start recording\n"));
		return;
	}

	if (ps_start_utt(ps) < 0) {
		UE_LOG(LogTemp, Warning, TEXT("Failed to start utterance\\n"));
		return;
	}

	utt_started = FALSE;
}

FString UJarvisFunctionLibrary::GetUserCommand()
{
	if ((k = ad_read(ad, adbuf, 2048)) < 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to read audio\n"));
	}

	ps_process_raw(ps, adbuf, k, FALSE, FALSE);
	in_speech = ps_get_in_speech(ps);

	if (in_speech && !utt_started)
	{
		utt_started = TRUE;
	}

	if (!in_speech && utt_started)
	{
		ps_end_utt(ps);
		hyp = ps_get_hyp(ps, NULL);
		if (hyp != NULL)
		{
			UE_LOG(LogTemp, Warning, TEXT("You said: %s"), ANSI_TO_TCHAR(hyp));
			return FString(ANSI_TO_TCHAR(hyp));
		}

		utt_started = FALSE;
	}

	return FString(ANSI_TO_TCHAR("UNK"));
}