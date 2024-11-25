// Fill out your copyright notice in the Description page of Project Settings.
#include "LocalMultiplayerGameViewportClient.h"

#include "Kismet/GameplayStatics.h"
#include "LocalMultiplayerSettings.h"
#include "LocalMultiplayerSubsystem.h"
#include "GameFramework/PlayerInput.h"

void ULocalMultiplayerGameViewportClient::PostInitProperties()
{
	Super::PostInitProperties();
	LocalMultiplayerSettings = GetDefault<ULocalMultiplayerSettings>();
	MaxSplitscreenPlayers = 8;
}

bool ULocalMultiplayerGameViewportClient::InputKey(const FInputKeyEventArgs& EventArgs)
{
	if (GameInstance == nullptr) return Super::InputKey(EventArgs);
	
	ULocalMultiplayerSubsystem* LocalMultiplayerSubsystem = GameInstance->GetSubsystem<ULocalMultiplayerSubsystem>();
	if (LocalMultiplayerSubsystem == nullptr) return Super::InputKey(EventArgs);
	int AssignedPlayerIndex = -1;
	if (EventArgs.IsGamepad())
	{
		AssignedPlayerIndex = LocalMultiplayerSubsystem->GetAssignedPlayerIndexFromGamepadDeviceID(EventArgs.ControllerId);

		if (AssignedPlayerIndex == -1)
		{
			AssignedPlayerIndex = LocalMultiplayerSubsystem->AssignNewPlayerToGamepadDeviceID(EventArgs.ControllerId);
			LocalMultiplayerSubsystem->AssignGamepadInputMapping(
				AssignedPlayerIndex,
				ELocalMultiplayerInputMappingType::InGame
			);
			
			if (AssignedPlayerIndex == -1) return Super::InputKey(EventArgs);
		}
	} else
	{
		int ProfileIndex = LocalMultiplayerSettings->FindKeyboardProfileIndexFromKey(EventArgs.Key, ELocalMultiplayerInputMappingType::InGame);

		if (ProfileIndex == -1) return Super::InputKey(EventArgs);
		
		AssignedPlayerIndex = LocalMultiplayerSubsystem->GetAssignedPlayerIndexFromKeyboardProfileIndex(ProfileIndex);
		if (AssignedPlayerIndex == -1)
		{
			AssignedPlayerIndex = LocalMultiplayerSubsystem->AssignNewPlayerToKeyboardProfile(ProfileIndex);
			LocalMultiplayerSubsystem->AssignKeyboardMapping(AssignedPlayerIndex,
				ProfileIndex,
				ELocalMultiplayerInputMappingType::InGame);
			
			if (AssignedPlayerIndex == -1) return Super::InputKey(EventArgs);
		}
	}

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(),AssignedPlayerIndex);
	if (PlayerController == nullptr) return Super::InputKey(EventArgs);

	FInputKeyParams Params;
	Params.Key = EventArgs.Key;
	Params.Event = EventArgs.Event;
	Params.Delta.X = EventArgs.AmountDepressed;
	Params.InputDevice = EventArgs.InputDevice;
	Params.bIsGamepadOverride = EventArgs.IsGamepad();
	
	return PlayerController->InputKey(Params);
}

bool ULocalMultiplayerGameViewportClient::InputAxis(FViewport* InViewport, FInputDeviceId InputDevice, FKey Key,
	float Delta, float DeltaTime, int32 NumSamples, bool bGamepad)
{
	if (GameInstance == nullptr)
		return Super::InputAxis(InViewport, InputDevice, Key, Delta, DeltaTime, NumSamples, bGamepad);
	
	ULocalMultiplayerSubsystem* LocalMultiplayerSubsystem = GameInstance->GetSubsystem<ULocalMultiplayerSubsystem>();
	if (LocalMultiplayerSubsystem == nullptr)
		return Super::InputAxis(InViewport, InputDevice, Key, Delta, DeltaTime, NumSamples, bGamepad);
	
	int AssignedPlayerIndex = LocalMultiplayerSubsystem->GetAssignedPlayerIndexFromGamepadDeviceID(InputDevice.GetId());

	if (AssignedPlayerIndex == -1)
	{
		AssignedPlayerIndex = LocalMultiplayerSubsystem->AssignNewPlayerToGamepadDeviceID(InputDevice.GetId());
		LocalMultiplayerSubsystem->AssignGamepadInputMapping(
			AssignedPlayerIndex,
			ELocalMultiplayerInputMappingType::InGame
		);
		
		if (AssignedPlayerIndex == -1)
			return Super::InputAxis(InViewport, InputDevice, Key, Delta, DeltaTime, NumSamples, bGamepad);
	}

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(),AssignedPlayerIndex);
	if (PlayerController == nullptr)
		return Super::InputAxis(InViewport, InputDevice, Key, Delta, DeltaTime, NumSamples, bGamepad);

	FInputKeyParams Params;
	Params.NumSamples = NumSamples;
	Params.Delta.X = Delta;
	Params.DeltaTime = DeltaTime;
	Params.Key = Key;
	Params.InputDevice = InputDevice;
	Params.bIsGamepadOverride = bGamepad;
	
	return PlayerController->InputKey(Params);
}
