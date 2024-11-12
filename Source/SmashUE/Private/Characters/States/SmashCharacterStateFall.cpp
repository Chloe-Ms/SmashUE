// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/States/SmashCharacterStateFall.h"

#include "Characters/SmashCharacterStateMachine.h"


// Sets default values for this component's properties
USmashCharacterStateFall::USmashCharacterStateFall()
{
}

void USmashCharacterStateFall::StateInit(USmashCharacterStateMachine* InStateMachine)
{
	Super::StateInit(InStateMachine);
}

void USmashCharacterStateFall::StateEnter(ESmashCharacterStateID PreviousStateID)
{
	Super::StateEnter(PreviousStateID);
}

void USmashCharacterStateFall::StateExit(ESmashCharacterStateID NextStateID)
{
	Super::StateExit(NextStateID);
}

void USmashCharacterStateFall::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);
	StateMachine->ChangeState(ESmashCharacterStateID::Idle);
}


// Called when the game starts
void USmashCharacterStateFall::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

