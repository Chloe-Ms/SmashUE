// Fill out your copyright notice in the Description page of Project Settings.


#include "LocalMultiplayerSettings.h"

#include "InputMappingContext.h"

bool FLocalMultiplayerProfileData::ContainsKey(const FKey& Key, ELocalMultiplayerInputMappingType MappingType) const
{
	UInputMappingContext* InputMappingContext = GetIMCFromType(MappingType);

	if (!InputMappingContext) return false;

	for (FEnhancedActionKeyMapping ActionKey : InputMappingContext->GetMappings())
	{
		if (ActionKey.Key == Key) return true;
	}
	return false;
}

UInputMappingContext* FLocalMultiplayerProfileData::GetIMCFromType(ELocalMultiplayerInputMappingType MappingType) const
{
	UInputMappingContext* InputMappingContext = nullptr;
	switch (MappingType)
	{
		case ELocalMultiplayerInputMappingType::InGame:
			InputMappingContext = IMCInGame;
			break;
		case ELocalMultiplayerInputMappingType::Menu:
			InputMappingContext = IMCMenu;
			break;
	}
	
	return InputMappingContext;
}

int ULocalMultiplayerSettings::GetNbKeyboardProfiles() const
{
	return KeyboardProfilesData.Num();
}

int ULocalMultiplayerSettings::FindKeyboardProfileIndexFromKey(const FKey& Key,
	ELocalMultiplayerInputMappingType MappingType) const
{
	for (int i = 0; i < KeyboardProfilesData.Num(); i++)
	{
		if (KeyboardProfilesData[i].ContainsKey(Key, MappingType))
		{
			return i;
		}
	}
	
	return -1;
}
