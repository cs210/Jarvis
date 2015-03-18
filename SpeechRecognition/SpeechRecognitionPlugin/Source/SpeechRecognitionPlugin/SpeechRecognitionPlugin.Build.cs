// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

namespace UnrealBuildTool.Rules
{
    public class SpeechRecognitionPlugin : ModuleRules
	{
		public SpeechRecognitionPlugin(TargetInfo Target)
		{
			PublicIncludePaths.AddRange(
				new string[] {
                    "SpeechRecognitionPlugin/Public",
					// ... add public include paths required here ...
				}
				);

			PrivateIncludePaths.AddRange(
				new string[] {
					"SpeechRecognitionPlugin/Private",
                    "SpeechRecognitionPlugin/Classes",
					// ... add other private include paths required here ...
				}
				);

			PublicDependencyModuleNames.AddRange(
				new string[]
				{
                    "CoreUObject",				
                    "Core",
                    "Engine",
                    "InputDevice",
                    "K4WLib",
                    "MSSpeech",
                    "InputCore",
                    "Slate"
					// ... add other public dependencies that you statically link with here ...
				}
				);

			PrivateDependencyModuleNames.AddRange(
				new string[]
				{
                    "CoreUObject",
					"Core",
                    "Engine",
					// ... add private dependencies that you statically link with here ...
				}
				);

			DynamicallyLoadedModuleNames.AddRange(
				new string[]
				{
					// ... add any modules that your module loads dynamically here ...
				}
				);
		}
	}
}