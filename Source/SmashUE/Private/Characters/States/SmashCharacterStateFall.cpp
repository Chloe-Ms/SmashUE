// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/States/SmashCharacterStateFall.h"

#include "Characters/SmashCharacterStateMachine.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values for this component's properties
USmashCharacterStateFall::USmashCharacterStateFall()
{
}

ESmashCharacterStateID USmashCharacterStateFall::GetStateID()
{
	return ESmashCharacterStateID::Fall;
}

void USmashCharacterStateFall::StateInit(USmashCharacterStateMachine* InStateMachine)
{
	Super::StateInit(InStateMachine);
}

void USmashCharacterStateFall::StateEnter(ESmashCharacterStateID PreviousStateID)
{
	Super::StateEnter(PreviousStateID);
	Character->GetCharacterMovement()->AirControl = FallAirControl;
	Character->GetCharacterMovement()->GravityScale = FallGravityScale;
	Character->GetCharacterMovement()->MaxWalkSpeed = FallHorizontalMoveSpeed;
}

void USmashCharacterStateFall::StateExit(ESmashCharacterStateID NextStateID)
{
	Super::StateExit(NextStateID);
}

void USmashCharacterStateFall::MoveHorizontally()
{
	if (FMath::Abs(Character->GetInputMoveX()) >= CharacterSettings->InputMoveXThreshold)
	{
		Character->SetOrientX(Character->GetInputMoveX());
		Character->AddMovementInput(FVector::ForwardVector * Character->GetOrientX(), 1);
	}
}

void USmashCharacterStateFall::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);

	MoveHorizontally();
	if (!Character->GetCharacterMovement()->IsFalling())
	{
		StateMachine->ChangeState(ESmashCharacterStateID::Idle);
	}
}


// Called when the game starts
void USmashCharacterStateFall::BeginPlay()
{
	Super::BeginPlay();
}

