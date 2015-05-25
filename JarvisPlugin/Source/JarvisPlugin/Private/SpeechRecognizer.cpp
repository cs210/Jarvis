#include "JarvisPluginPrivatePCH.h"
#include "SpeechRecognizer.h"

SpeechRecognizer::SpeechRecognizer()
{
	WorkEvent = FPlatformProcess::CreateSynchEvent(true);	
}

SpeechRecognizer::~SpeechRecognizer()
{
	delete WorkEvent;
}

bool SpeechRecognizer::Init()
{
	InitializePocketSphinxRecognizer();
	return true;
}

uint32 SpeechRecognizer::Run()
{
	while (true)
	{
		if (WorkEvent->Wait())
		{
			int Command;

			if (Commands.Dequeue(Command))
			{
				if (Command == CMD_STOP)
				{
					break;
				}
				else
				{
					//FPlatformProcess::Sleep(5);
					//Results.Enqueue(Count++);
					Results.Enqueue(ProcessUserCommand());
				}
			}

			WorkEvent->Reset();
		}
	}

	return 0;
}

void SpeechRecognizer::Stop()
{
	// Nothing to do
}

void SpeechRecognizer::Exit()
{
	// Nothing to do
}

bool SpeechRecognizer::EnqueueCommand(int Command)
{
	if ( (!Commands.IsEmpty()) || (!Results.IsEmpty()) || (!Commands.Enqueue(Command)) )
	{
		return false;
	}

	WorkEvent->Trigger();

	return true;
}

bool SpeechRecognizer::IsResultPending()
{
	return !Results.IsEmpty();
}

FString SpeechRecognizer::GetResult()
{
	FString Tmp;
	Results.Dequeue(Tmp);

	return Tmp;
}

/*
int SpeechRecognizer::GetResult()
{
	int Tmp;
	Results.Dequeue(Tmp);

	return Tmp;
}
*/

void SpeechRecognizer::InitializePocketSphinxRecognizer()
{
	//TODO: Parametrize the hard-coded paths below - use configuration files?
	int argc = 9;
	char **argv = (char **)malloc(argc * sizeof(char *));
	argv[0] = "";
	argv[1] = "-inmic"; argv[2] = "yes";
	argv[3] = "-hmm"; argv[4] = "C:\\Users\\Jarvis\\Downloads\\CMUSphinx\\pocketsphinx-5prealpha\\model\\en-us\\en-us";
	argv[5] = "-lm"; argv[6] = "C:\\Users\\Jarvis\\Downloads\\CMUSphinx\\pocketsphinx-5prealpha\\model\\en-us\\en-us.lm.dmp";
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

	utt_started = FALSE;
}

FString SpeechRecognizer::ProcessUserCommand()
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

void SpeechRecognizer::ReadAudioBuffer()
{
	if ((k = ad_read(ad, adbuf, 2048)) < 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to read audio\n"));
		return;
	}

	ps_process_raw(ps, adbuf, k, FALSE, FALSE);
	in_speech = ps_get_in_speech(ps);
	FPlatformProcess::Sleep(0.005);
}
