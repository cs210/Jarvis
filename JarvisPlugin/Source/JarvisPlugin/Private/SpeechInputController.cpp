
#include "JarvisPluginPrivatePCH.h"
#include "SpeechInputController.h"
#include "SpeechEventInterface.h"

USpeechInputController::USpeechInputController(const FObjectInitializer &init) :
	UActorComponent(init)
{
	bAutoActivate = true;
	PrimaryComponentTick.bCanEverTick = true;
	//InitializePocketSphinxRecognizer();
}

void USpeechInputController::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	ticks++;
	if (ticks % 5 == 0)
	{
		//InterfaceEventTick(DeltaTime);
	}
}

/*
void USpeechInputController::InterfaceEventTick(float DeltaTime) {
	if ((k = ad_read(ad, adbuf, 2048)) < 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to read audio\n"));
	}

	ps_process_raw(ps, adbuf, k, FALSE, FALSE);
	//ps_process_raw(ps, adbuf, k, FALSE, TRUE);
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
			ISpeechEventInterface::Execute_SpeechEventCommand(interfaceDelegate, FString(ANSI_TO_TCHAR(hyp)));

			if (strcmp(hyp, COLOR) == 0)
			{
				ISpeechEventInterface::Execute_SpeechEventColor(interfaceDelegate);
			}
			else
			{
				ISpeechEventInterface::Execute_SpeechEventTexture(interfaceDelegate);
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("No hypothesis available"));
		}

		if (ps_start_utt(ps) < 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to start utterance\n"));
		}

		utt_started = FALSE;
	}
}
*/

/*
void USpeechInputController::InterfaceEventTick(float DeltaTime) {
	if ((k = ad_read(ad, adbuf, 2048)) < 0)
	{
		E_FATAL("Failed to read audio\n");
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
			ISpeechEventInterface::Execute_SpeechEventCommand(interfaceDelegate, FString(ANSI_TO_TCHAR(hyp)));

			if (strcmp(hyp, COLOR) == 0)
			{
				ISpeechEventInterface::Execute_SpeechEventColor(interfaceDelegate);
			}
			else
			{
				ISpeechEventInterface::Execute_SpeechEventTexture(interfaceDelegate);
			}
		}

		if (ps_start_utt(ps) < 0)
		{
			E_FATAL("Failed to start utterance\n");
		}

		utt_started = FALSE;
	}
}
*/

void USpeechInputController::OnRegister()
{
	Super::OnRegister();

	SetInterfaceDelegate(GetOwner());
}

void USpeechInputController::SetInterfaceDelegate(UObject* newDelegate)
{
	if (newDelegate->GetClass()->ImplementsInterface(USpeechEventInterface::StaticClass()))
	{
		interfaceDelegate = newDelegate;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("SpeechInputController Warning: Delegate is NOT set, did you implement SpeechEventInterface?"));
	}
}

/*
void USpeechInputController::InitializePocketSphinxRecognizer()
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
		E_INFO("Specify '-infile <file.wav>' to recognize from file or '-inmic yes' to recognize from microphone.");
		cmd_ln_free_r(config);
		return;
	}

	ps_default_search_args(config);
	ps = ps_init(config);
	if (ps == NULL) {
		cmd_ln_free_r(config);
		return;
	}

	E_INFO("%s COMPILED ON: %s, AT: %s\n\n", argv[0], __DATE__, __TIME__);

	if ((ad = ad_open_dev(cmd_ln_str_r(config, "-adcdev"),
		(int)cmd_ln_float32_r(config,
		"-samprate"))) == NULL)
		E_FATAL("Failed to open audio device\n");
	if (ad_start_rec(ad) < 0)
		E_FATAL("Failed to start recording\n");

	if (ps_start_utt(ps) < 0)
		E_FATAL("Failed to start utterance\n");
	utt_started = FALSE;
}
*/