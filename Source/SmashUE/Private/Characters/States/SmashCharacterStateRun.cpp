// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/States/SmashCharacterStateRun.h"

#include "Characters/SmashCharacter.h"


ESmashCharacterStateID USmashCharacterStateRun::GetStateID()
{
	return ESmashCharacterStateID::Run;
}

void USmashCharacterStateRun::StateInit(USmashCharacterStateMachine* InStateMachine)
{
	Super::StateInit(InStateMachine);
}

void USmashCharacterStateRun::StateEnter(ESmashCharacterStateID PreviousStateID)
{
	Super::StateEnter(PreviousStateID);
}

void USmashCharacterStateRun::StateExit(ESmashCharacterStateID NextStateID)
{
	Super::StateExit(NextStateID);
}

void USmashCharacterStateRun::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);

	FVector location = Character->GetActorLocation();
	location.X += DeltaTime * RunSpeedMax * Character->GetOrientX();
	Character->SetActorLocation(location);
}

// Sets default values for this component's properties
USmashCharacterStateRun::USmashCharacterStateRun()
{
	// // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// // off to improve performance if you don't need them.
	// PrimaryComponentTick.bCanEverTick = true;
	//
	// // ...
}


// Called when the game starts
void USmashCharacterStateRun::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

