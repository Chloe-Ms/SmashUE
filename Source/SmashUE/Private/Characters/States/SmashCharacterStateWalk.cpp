// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/States/SmashCharacterStateWalk.h"

#include "Characters/SmashCharacter.h"
#include "Characters/SmashCharacterSettings.h"
#include "Characters/SmashCharacterStateID.h"
#include "Characters/SmashCharacterStateMachine.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values for this component's properties
USmashCharacterStateWalk::USmashCharacterStateWalk()
{
}

ESmashCharacterStateID USmashCharacterStateWalk::GetStateID()
{
	return ESmashCharacterStateID::Walk;
}

void USmashCharacterStateWalk::StateEnter(ESmashCharacterStateID PreviousStateID)
{
	Super::StateEnter(PreviousStateID);

	Character->GetCharacterMovement()->MaxWalkSpeed = WalkSpeedMax;
	Character->InputMoveXFastEvent.AddDynamic(this,&USmashCharacterStateWalk::OnInputMoveXFast);
	Character->InputJumpEvent.AddDynamic(this, &USmashCharacterStateWalk::OnInputJump);
}

void USmashCharacterStateWalk::StateExit(ESmashCharacterStateID NextStateID)
{
	Super::StateExit(NextStateID);
	Character->InputMoveXFastEvent.RemoveDynamic(this,&USmashCharacterStateWalk::OnInputMoveXFast);
	Character->InputJumpEvent.RemoveDynamic(this,&USmashCharacterStateWalk::OnInputJump);
}

void USmashCharacterStateWalk::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);

	if (FMath::Abs(Character->GetInputMoveX()) < CharacterSettings->InputMoveXThreshold)
	{
		StateMachine->ChangeState(ESmashCharacterStateID::Idle);
	} else
	{
		Character->SetOrientX(Character->GetInputMoveX());

		Character->AddMovementInput(FVector::ForwardVector * Character->GetOrientX(), 1);
	}

	if (Character->GetCharacterMovement()->Velocity.Z < 0.f)
	{
		StateMachine->ChangeState(ESmashCharacterStateID::Fall);
	}
}

void USmashCharacterStateWalk::OnInputMoveXFast(float InputMoveX)
{
	StateMachine->ChangeState(ESmashCharacterStateID::Run);
}

void USmashCharacterStateWalk::OnInputJump()
{
	StateMachine->ChangeState(ESmashCharacterStateID::Jump);
}

