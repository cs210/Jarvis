// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

namespace UnrealBuildTool.Rules
{
    public class JarvisPlugin : ModuleRules
	{
        public JarvisPlugin(TargetInfo Target)
		{
            string cmusphinxDir = UEBuildConfiguration.UEThirdPartySourceDirectory + "/CMUSphinx";
            string sphinxbaseDir = cmusphinxDir + "/sphinxbase";
            string pocketsphinxDir = cmusphinxDir + "/pocketsphinx-5prealpha";

			PublicIncludePaths.AddRange(
				new string[] {
                    "JarvisPlugin/Public",
                    sphinxbaseDir + "/include",
                    sphinxbaseDir + "/include/sphinxbase",
                    sphinxbaseDir + "/include/win32",
                    pocketsphinxDir + "/include",
                    pocketsphinxDir + "src/libpocketsphinx",
					// ... add public include paths required here ...
				}
				);

			PrivateIncludePaths.AddRange(
				new string[] {
					"JarvisPlugin/Private",
                    "JarvisPlugin/Classes",
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
                    //"K4WLib",
                    //"MSSpeech",
                    "InputCore",
                    "Slate",
                    "CMUSphinx",
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