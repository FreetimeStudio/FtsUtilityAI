// (c) MIT 2020 by FreetimeStudio

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "FtsUtilityAIEditorStyle.h"

class FFtsUtilityAIEditorCommands : public TCommands<FFtsUtilityAIEditorCommands>
{
public:

	FFtsUtilityAIEditorCommands()
		: TCommands<FFtsUtilityAIEditorCommands>(TEXT("FtsUtilityAIEditor"), NSLOCTEXT("Contexts", "FtsUtilityAIEditor", "FtsUtilityAIEditor Plugin"), NAME_None, FFtsUtilityAIEditorStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};