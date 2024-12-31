// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/States/SmashCharacterStateRun.h"

#include "Characters/SmashCharacter.h"
#include "Characters/SmashCharacterStateMachine.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values for this component's properties
USmashCharacterStateRun::USmashCharacterStateRun()
{
}

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

	Character->GetCharacterMovement()->MaxWalkSpeed = RunSpeedMax;
	Character->InputJumpEvent.AddDynamic(this,&USmashCharacterStateRun::OnInputJump);
	Character->InputNormalSpecialAttack.AddDynamic(this, &USmashCharacterStateRun::OnInputNormalSpecialAttack);
}

void USmashCharacterStateRun::StateExit(ESmashCharacterStateID NextStateID)
{
	Super::StateExit(NextStateID);
	Character->InputJumpEvent.RemoveDynamic(this,&USmashCharacterStateRun::OnInputJump);
	Character->InputNormalSpecialAttack.RemoveDynamic(this, &USmashCharacterStateRun::OnInputNormalSpecialAttack);
}

void USmashCharacterStateRun::StateTick(float DeltaTime)
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

void USmashCharacterStateRun::OnInputJump()
{
	StateMachine->ChangeState(ESmashCharacterStateID::Jump);
}

void USmashCharacterStateRun::OnInputNormalSpecialAttack()
{
	StateMachine->ChangeState(ESmashCharacterStateID::SpecialAttack);
}

