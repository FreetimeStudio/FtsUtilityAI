// (c) MIT 2020 by FreetimeStudio

#include "FtsUtilityAIEditorCommands.h"

#define LOCTEXT_NAMESPACE "FFtsUtilityAIEditorModule"

void FFtsUtilityAIEditorCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "FtsUtilityAIEditor", "Bring up FtsUtilityAIEditor window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
