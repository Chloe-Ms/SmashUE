// Fill out your copyright notice in the Description page of Project Settings.


#include "SmashCharacterState.h"

#include "Characters/SmashCharacter.h"
#include "Characters/SmashCharacterStateID.h"
#include "Characters/SmashCharacterStateMachine.h"


// Sets default values for this component's properties
USmashCharacterState::USmashCharacterState()
{
}

ESmashCharacterStateID USmashCharacterState::GetStateID()
{
	return ESmashCharacterStateID::None;
}

void USmashCharacterState::StateInit(USmashCharacterStateMachine* InStateMachine)
{
	StateMachine = InStateMachine;
	Character = InStateMachine->GetCharacter();
	CharacterSettings = GetDefault<USmashCharacterSettings>();
}

void USmashCharacterState::StateEnter(ESmashCharacterStateID PreviousStateID)
{
	if (AnimMontage != nullptr)
	{
		Character->PlayAnimMontage(AnimMontage);
	}
}

void USmashCharacterState::StateExit(ESmashCharacterStateID NextStateID)
{
}

void USmashCharacterState::StateTick(float DeltaTime)
{
}
