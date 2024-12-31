// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SmashCharacterStateMachine.h"

#include "SmashCharacterState.h"
#include "Characters/SmashCharacterStateID.h"
#include "Kismet/GameplayStatics.h"

void USmashCharacterStateMachine::Init(ASmashCharacter* InCharacter)
{
	Character = InCharacter;
	FindStates();
	InitStates();
	
	ChangeState(ESmashCharacterStateID::Idle);
}

void USmashCharacterStateMachine::Tick(float DeltaTime)
{
	if (CurrentState == nullptr) return;
	CurrentState->StateTick(DeltaTime);
}

ASmashCharacter* USmashCharacterStateMachine::GetCharacter() const
{
	return Character;
}

void USmashCharacterStateMachine::ChangeState(ESmashCharacterStateID NextStateID)
{
	USmashCharacterState* NextState = GetState(NextStateID);

	//Do nothing if NextState not found
	if (NextState == nullptr) return;

	if (CurrentState != nullptr)
	{
		CurrentState->StateExit(NextStateID);
	}

	ESmashCharacterStateID PreviousStateID = CurrentStateID;
	CurrentStateID = NextStateID;
	CurrentState = NextState;

	if (CurrentState != nullptr)
	{
		CurrentState->StateEnter(PreviousStateID);
	}
}

USmashCharacterState* USmashCharacterStateMachine::GetState(ESmashCharacterStateID StateID)
{
	for(USmashCharacterState* State : AllStates)
	{
		if (StateID == State->GetStateID())
			return State;
	}
	
	return nullptr;
}

void USmashCharacterStateMachine::FindStates()
{
	const USmashCharacterSettings* CharacterSettings = GetDefault<USmashCharacterSettings>();
	TArray<TSubclassOf<USmashCharacterState>> FoundStates = CharacterSettings->CharacterStates;
	TMap<ESmashCharacterStateID,TSubclassOf<USmashCharacterState>> OveriddenStates = Character->OverridenStates;
	for (TSubclassOf<USmashCharacterState> State : FoundStates)
	{
		USmashCharacterState* CharacterState = State.GetDefaultObject();
		if (CharacterState != nullptr && OveriddenStates.Contains(CharacterState->GetStateID()))
		{
			UObject* StateObjectSpawned = UGameplayStatics::SpawnObject(OveriddenStates[CharacterState->GetStateID()], this);
			if (USmashCharacterState* StateObjectCasted = Cast<USmashCharacterState>(StateObjectSpawned))
			{
				AllStates.Add(StateObjectCasted);
			}
		} else
		{
			UObject* StateObjectSpawned = UGameplayStatics::SpawnObject(State, this);
			if (USmashCharacterState* StateObjectCasted = Cast<USmashCharacterState>(StateObjectSpawned))
			{
				AllStates.Add(StateObjectCasted);
			}
		}
		
	}
}

void USmashCharacterStateMachine::InitStates()
{
	for (USmashCharacterState* State : AllStates)
	{
		State->StateInit(this);
	}
}
