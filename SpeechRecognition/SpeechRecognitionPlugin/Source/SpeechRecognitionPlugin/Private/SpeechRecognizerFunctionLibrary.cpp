
#include "SpeechRecognitionPluginPrivatePCH.h"

//USpeechRecognizerFunctionLibrary::USpeechRecognizerFunctionLibrary(const class FPostConstructInitializeProperties& PCIP)
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