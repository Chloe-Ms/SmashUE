// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/States/SmashCharacterStateJump.h"

#include "Characters/SmashCharacterStateMachine.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values for this component's properties
USmashCharacterStateJump::USmashCharacterStateJump()
{
}

ESmashCharacterStateID USmashCharacterStateJump::GetStateID()
{
	return ESmashCharacterStateID::Jump;
}

void USmashCharacterStateJump::StateInit(USmashCharacterStateMachine* InStateMachine)
{
	Super::StateInit(InStateMachine);
}

void USmashCharacterStateJump::StateEnter(ESmashCharacterStateID PreviousStateID)
{
	Super::StateEnter(PreviousStateID);
	
	float halfDuration = JumpDuration;
	InitialVelocityY = 2 * JumpMaxHeight / halfDuration;
	float computeGravity = - 2 * JumpMaxHeight / (halfDuration * halfDuration);
	float gravityScale = - computeGravity / Gravity;
	Character->GetCharacterMovement()->GravityScale = gravityScale;

	Character->GetCharacterMovement()->MaxWalkSpeed = JumpWalkSpeed;
	Character->GetCharacterMovement()->AirControl = JumpAirControl;
	Character->GetCharacterMovement()->JumpZVelocity = InitialVelocityY;
	Character->Jump();
}

void USmashCharacterStateJump::StateExit(ESmashCharacterStateID NextStateID)
{
	Super::StateExit(NextStateID);
}

void USmashCharacterStateJump::MoveHorizontally()
{
	if (FMath::Abs(Character->GetInputMoveX()) >= CharacterSettings->InputMoveXThreshold)
	{
		Character->SetOrientX(Character->GetInputMoveX());
		Character->AddMovementInput(FVector::ForwardVector * Character->GetOrientX(), 1);
	}
}

void USmashCharacterStateJump::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);
	MoveHorizontally();
		
	if (Character->GetCharacterMovement()->Velocity.Z < 0.f)
	{
		StateMachine->ChangeState(ESmashCharacterStateID::Fall);
	}
}


// Called when the game starts
void USmashCharacterStateJump::BeginPlay()
{
	Super::BeginPlay();
}

