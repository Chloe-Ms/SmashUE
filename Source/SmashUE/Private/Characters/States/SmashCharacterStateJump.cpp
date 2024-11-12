// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/States/SmashCharacterStateJump.h"

#include "Characters/SmashCharacterStateMachine.h"


// Sets default values for this component's properties
USmashCharacterStateJump::USmashCharacterStateJump()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void USmashCharacterStateJump::StateInit(USmashCharacterStateMachine* InStateMachine)
{
	Super::StateInit(InStateMachine);
}

void USmashCharacterStateJump::StateEnter(ESmashCharacterStateID PreviousStateID)
{
	Super::StateEnter(PreviousStateID);
	InitialVelocityY = 2 * JumpMaxHeight / JumpDuration;
	VelocityY = InitialVelocityY;
}

void USmashCharacterStateJump::StateExit(ESmashCharacterStateID NextStateID)
{
	Super::StateExit(NextStateID);
}

void USmashCharacterStateJump::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);

	Timer += DeltaTime;
	if (Timer <= JumpDuration)
	{
		float acc = 1/2 * Gravity * Timer * Timer + InitialVelocityY * Timer; 
		VelocityY += acc * DeltaTime;
		Character->AddMovementInput(FVector(0, 0, VelocityY));
	} else if (Timer > (JumpDuration + JumpAirControl))
	{
		StateMachine->ChangeState(ESmashCharacterStateID::Jump);
	}
}


// Called when the game starts
void USmashCharacterStateJump::BeginPlay()
{
	Super::BeginPlay();
}

