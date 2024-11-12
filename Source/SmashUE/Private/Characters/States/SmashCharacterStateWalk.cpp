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
	// // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// // off to improve performance if you don't need them.
	// PrimaryComponentTick.bCanEverTick = true;
	//
	// // ...
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
}

void USmashCharacterStateWalk::StateExit(ESmashCharacterStateID NextStateID)
{
	Super::StateExit(NextStateID);
	Character->InputMoveXFastEvent.RemoveDynamic(this,&USmashCharacterStateWalk::OnInputMoveXFast);


	
}

void USmashCharacterStateWalk::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);

	// FVector location = Character->GetActorLocation();
	// location.X += DeltaTime * WalkSpeedMax * Character->GetOrientX();
	// Character->SetActorLocation(location);
	if (FMath::Abs(Character->GetInputMoveX()) < CharacterSettings->InputMoveXThreshold)
	{
		StateMachine->ChangeState(ESmashCharacterStateID::Idle);
	} else
	{
		Character->SetOrientX(Character->GetInputMoveX());
		Character->AddMovementInput(FVector::ForwardVector * Character->GetOrientX(), 1);
	}
}

void USmashCharacterStateWalk::OnInputMoveXFast(float InputMoveX)
{
	StateMachine->ChangeState(ESmashCharacterStateID::Run);
}

