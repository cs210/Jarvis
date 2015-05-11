
#include "JarvisPluginPrivatePCH.h"

DEFINE_LOG_CATEGORY(UserActionsLog);

UJarvisFunctionLibrary::UJarvisFunctionLibrary(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	InitializePocketSphinxRecognizer();
}

//===========================================
// Jarvis general blueprint methods
//===========================================
 
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

//===========================================
// Jarvis AssetRegistry methods
//===========================================

TArray<FString> UJarvisFunctionLibrary::LoadMeshCollections(FString directoryPath)
{
	// Get a reference to the AssetRegistry
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();

	// Scan all the assets in the provided directory (which is expected to be the root directory containing all the meshes related to the Jarvis project)
	TArray<FString> PathsToScan;
	PathsToScan.Add(directoryPath);
	AssetRegistry.ScanPathsSynchronous(PathsToScan);

	// Create a filter for the statis mesh assets in the registry
	FARFilter Filter;
	Filter.ClassNames.Add(FName(*(UStaticMesh::StaticClass()->GetName())));

	// Apply the filter and store the results in AssetData
	TArray<FAssetData> AssetData;
	AssetRegistryModule.Get().GetAssets(Filter, AssetData);

	TArray<FString> meshPaths;
	for (int32 i = 0; i < AssetData.Num(); i++)
	{
		FString path = AssetData[i].ObjectPath.ToString();
		if (path.StartsWith(directoryPath)) // We consider only those meshes that are placed in the specified directory
		{
			meshPaths.Add(path);
			UStaticMesh* mesh = LoadStaticMesh(path);

			// Obtain name of the collection from the mesh path and store the mesh in the (collection -> meshes) map
			TArray<FString> elems;
			path.ParseIntoArray(&elems, TEXT("/"), true);
			int32 numElems = elems.Num();
			if (numElems >= 3) {
				FString collection = elems[numElems - 2].ToLower();
				AddMeshToCollection(collection, mesh);
			}
		}
	}

	PrintCollectionToMeshesMap();

	return meshPaths;
}

TArray<UStaticMesh*> UJarvisFunctionLibrary::GetMeshesFromCollection(FString collectionName)
{
	UE_LOG(LogTemp, Warning, TEXT("Calling GetMeshesFromCollection() with collection == %s"), *collectionName);

	if (collectionToMeshes.Contains(collectionName))
	{
		return collectionToMeshes[collectionName];
	}

	TArray<UStaticMesh*> meshes;
	return meshes;
}

void UJarvisFunctionLibrary::AddMeshToCollection(FString collection, UStaticMesh* mesh)
{
	UE_LOG(LogTemp, Warning, TEXT("Adding mesh %s to collection: %s"), *(mesh->GetFullName()), *collection);
	if (!(collectionToMeshes.Contains(collection)))
	{
		TArray<UStaticMesh*> meshPaths;
		collectionToMeshes.Add(collection, meshPaths);
	}

	collectionToMeshes[collection].Add(mesh);
}

UStaticMesh* UJarvisFunctionLibrary::LoadStaticMesh(FString ObjectPath)
{
	UObject* mesh = StaticLoadObject(UStaticMesh::StaticClass(), NULL, *ObjectPath);
	return Cast<UStaticMesh>(mesh);
}

void UJarvisFunctionLibrary::PrintCollectionToMeshesMap()
{
	for (const auto& entry : collectionToMeshes)
	{
		auto collection = entry.Key;
		auto meshes = entry.Value;
		UE_LOG(LogTemp, Warning, TEXT("Collection: %s"), *collection);

		for (const auto& m : meshes)
		{
			UE_LOG(LogTemp, Warning, TEXT("\t\t\tMesh: %s"), *(m->GetFullName()));
		}
	}
}

//===========================================
// World-to-meters methods
//===========================================

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

//===========================================
// Speech recognition methods
//===========================================

void UJarvisFunctionLibrary::InitializePocketSphinxRecognizer()
{
	//TODO: Parametrize the hard-coded paths below - use configuration files?
	int argc = 9;
	char **argv = (char **)malloc(argc * sizeof(char *));
	argv[0] = "";
	argv[1] = "-inmic"; argv[2] = "yes";
	argv[3] = "-hmm"; argv[4] = "C:\\Users\\Jarvis\\Downloads\\CMUSphinx\\pocketsphinx-5prealpha\\model\\en-us\\en-us";
	argv[5] = "-lm"; argv[6] = "C:\\Users\\Jarvis\\Downloads\\CMUSphinx\\pocketsphinx-5prealpha\\model\\en-us\\en-us.lm.dmp";
	//argv[7] = "-dict"; argv[8] = "D:\\Tmp\\cmusphinx_app\\JarvisTestApp1\\model\\jarvis_vocab.dict";
	argv[7] = "-dict"; argv[8] = "D:\\Jarvis\\JarvisPlugin\\Model\\jarvis_vocab.dict";

	config = cmd_ln_parse_r(NULL, cont_args_def, argc, argv, TRUE);

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

	if ((ad = ad_open_dev(cmd_ln_str_r(config, "-adcdev"),
		(int)cmd_ln_float32_r(config,
		"-samprate"))) == NULL) {
		UE_LOG(LogTemp, Warning, TEXT("Failed to open audio device\n"));
		return;
	}

	/*
	if (ad_start_rec(ad) < 0) {
		UE_LOG(LogTemp, Warning, TEXT("Failed to start recording\n"));
		return;
	}
	*/

	/*
	if (ps_start_utt(ps) < 0) {
		UE_LOG(LogTemp, Warning, TEXT("Failed to start utterance\\n"));
		return;
	}
	*/

	utt_started = FALSE;
}

FString UJarvisFunctionLibrary::GetUserCommand()
{
	if (ad_start_rec(ad) < 0) {
		UE_LOG(LogTemp, Warning, TEXT("Failed to start recording\n"));
		return default_user_command;
	}

	if (ps_start_utt(ps) < 0) {
		UE_LOG(LogTemp, Warning, TEXT("Failed to start utterance\\n"));
		return default_user_command;
	}

	do { ReadAudioBuffer(); } while (!in_speech);
	while (in_speech) { ReadAudioBuffer(); }

	ps_end_utt(ps);
	hyp = ps_get_hyp(ps, NULL);

	if (hyp != NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("You said: %s"), ANSI_TO_TCHAR(hyp));

		if (ad_stop_rec(ad) < 0) {
			UE_LOG(LogTemp, Warning, TEXT("Failed to stop recording\n"));
		}

		return FString(ANSI_TO_TCHAR(hyp));
	}

	if (ad_stop_rec(ad) < 0) {
		UE_LOG(LogTemp, Warning, TEXT("Failed to stop recording\n"));
	}

	return default_user_command;
}

//===========================================
// Logger methods
//===========================================

void UJarvisFunctionLibrary::LogUserAction(FString msg)
{
	UE_LOG(UserActionsLog, Log, TEXT("%s"), *msg);
}

//===========================================
// Helper methods
//===========================================

void UJarvisFunctionLibrary::ReadAudioBuffer()
{
	if ((k = ad_read(ad, adbuf, 2048)) < 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to read audio\n"));
		return;
	}

	ps_process_raw(ps, adbuf, k, FALSE, FALSE);
	in_speech = ps_get_in_speech(ps);
	SleepMilliSec(5);
}

/* Sleep for specified msec */
void UJarvisFunctionLibrary::SleepMilliSec(int32 ms)
{
#if (defined(_WIN32) && !defined(GNUWINCE)) || defined(_WIN32_WCE)
	Sleep(ms);
#else
	/* ------------------- Unix ------------------ */
	struct timeval tmo;

	tmo.tv_sec = 0;
	tmo.tv_usec = ms * 1000;

	select(0, NULL, NULL, NULL, &tmo);
#endif
}