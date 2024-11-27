// Fill out your copyright notice in the Description page of Project Settings.


#include "LocalMultiplayerSubsystem.h"

#include "EnhancedInputSubsystems.h"
#include "LocalMultiplayerSettings.h"
#include "Kismet/GameplayStatics.h"

void ULocalMultiplayerSubsystem::CreateAndInitPlayers(ELocalMultiplayerInputMappingType MappingType)
{
	const ULocalMultiplayerSettings* LocalMultiplayerSettings = GetDefault<ULocalMultiplayerSettings>();
	if (LocalMultiplayerSettings == nullptr) return;
	int TotalPlayers = LocalMultiplayerSettings->KeyboardProfilesData.Num() + LocalMultiplayerSettings->NbMaxGamepads;
	
	for (int i = 0; i < TotalPlayers; i++)
	{
		if (!UGameplayStatics::GetPlayerController(GetWorld(),i))
		{
			UGameplayStatics::CreatePlayer(GetWorld(),i);
		}
	}
}

int ULocalMultiplayerSubsystem::GetAssignedPlayerIndexFromKeyboardProfileIndex(int KeyboardProfileIndex)
{
	int* Value = PlayerIndexFromKeyboardProfileIndex.Find(KeyboardProfileIndex);

	if (Value) return *Value;

	return -1;
}

int ULocalMultiplayerSubsystem::AssignNewPlayerToKeyboardProfile(int KeyboardProfileIndex)
{
	const ULocalMultiplayerSettings* LocalMultiplayerSettings = GetDefault<ULocalMultiplayerSettings>();
	if (LocalMultiplayerSettings == nullptr) return -1;
	
	if (PlayerIndexFromKeyboardProfileIndex.Num() >= LocalMultiplayerSettings->KeyboardProfilesData.Num()) return -1;
	
	PlayerIndexFromKeyboardProfileIndex.Emplace(KeyboardProfileIndex, LastAssignedPlayerIndex);
	
	return LastAssignedPlayerIndex++;
}

void ULocalMultiplayerSubsystem::AssignKeyboardMapping(int PlayerIndex, int KeyboardProfileIndex,
	ELocalMultiplayerInputMappingType MappingType) const
{
	const ULocalMultiplayerSettings* LocalMultiplayerSettings = GetDefault<ULocalMultiplayerSettings>();
	if (LocalMultiplayerSettings == nullptr) return;

	//TODO Check KeyboardProfileIndex is in keyboardprofilesdata
	UInputMappingContext* InputMappingContext = LocalMultiplayerSettings->KeyboardProfilesData[KeyboardProfileIndex].GetIMCFromType(MappingType);
	if (InputMappingContext == nullptr) return;
	
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(),PlayerIndex);
	if (PlayerController == nullptr) return;
	
	ULocalPlayer* Player = PlayerController->GetLocalPlayer();
	if (Player == nullptr) return;

	FModifyContextOptions ModifyContextOptions;
	ModifyContextOptions.bForceImmediately = true;
	UEnhancedInputLocalPlayerSubsystem* InputSystem = Player->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	InputSystem->AddMappingContext(InputMappingContext, 0, ModifyContextOptions);
}

int ULocalMultiplayerSubsystem::GetAssignedPlayerIndexFromGamepadDeviceID(int DeviceID)
{
	int* Value = PlayerIndexFromGamepadProfileIndex.Find(DeviceID);

	if (Value) return *Value;

	return -1;
}

int ULocalMultiplayerSubsystem::AssignNewPlayerToGamepadDeviceID(int DeviceID)
{
	const ULocalMultiplayerSettings* LocalMultiplayerSettings = GetDefault<ULocalMultiplayerSettings>();
	if (LocalMultiplayerSettings == nullptr) return -1;
	
	if (PlayerIndexFromGamepadProfileIndex.Num() >= LocalMultiplayerSettings->NbMaxGamepads) return -1;
	
	PlayerIndexFromGamepadProfileIndex.Emplace(DeviceID,LastAssignedPlayerIndex);
	return LastAssignedPlayerIndex++;
}

void ULocalMultiplayerSubsystem::AssignGamepadInputMapping(int PlayerIndex,
	ELocalMultiplayerInputMappingType MappingType) const
{
	const ULocalMultiplayerSettings* LocalMultiplayerSettings = GetDefault<ULocalMultiplayerSettings>();
	if (LocalMultiplayerSettings == nullptr) return;

	UInputMappingContext* InputMappingContext = LocalMultiplayerSettings->GamepadProfileData.GetIMCFromType(MappingType);
	if (InputMappingContext == nullptr) return;
	
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(),PlayerIndex);
	if (PlayerController == nullptr) return;
	
	ULocalPlayer* Player = PlayerController->GetLocalPlayer();
	if (Player == nullptr) return;

	FModifyContextOptions ModifyContextOptions;
	ModifyContextOptions.bForceImmediately = true;
	
	UEnhancedInputLocalPlayerSubsystem* InputSystem = Player->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	InputSystem->AddMappingContext(InputMappingContext, 0, ModifyContextOptions);
}
