
#include "SpeechRecognitionPluginPrivatePCH.h"

USpeechRecognizerFunctionLibrary::USpeechRecognizerFunctionLibrary(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{

}
 
bool USpeechRecognizerFunctionLibrary::SaveStringTextToFile(
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

TArray<FString> USpeechRecognizerFunctionLibrary::GetNamesOfAllStaticMeshes()
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

TArray<FString> USpeechRecognizerFunctionLibrary::GetNamesOfAllMaterials()
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

