// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/Jammus/SmashCharacterStateNormalSpecialJammus.h"

#include "Characters/SmashCharacterStateMachine.h"
#include "Characters/Jammus/JammusEnergyBall.h"

void USmashCharacterStateNormalSpecialJammus::StateInit(USmashCharacterStateMachine* InStateMachine)
{
	Super::StateInit(InStateMachine);
}

void USmashCharacterStateNormalSpecialJammus::OnEnergyBallCharged()
{
	StateMachine->ChangeState(ESmashCharacterStateID::Idle);
}

void USmashCharacterStateNormalSpecialJammus::StateEnter(ESmashCharacterStateID PreviousStateID)
{
	Super::StateEnter(PreviousStateID);
		
	if (StoredEnergyBall == nullptr)
	{
		StoredEnergyBall = GetWorld()->SpawnActor<AJammusEnergyBall>(EnergyBall);
		StoredEnergyBall->Init(StateMachine->GetCharacter(), this);
		StoredEnergyBall->OnChargedEvent.AddDynamic(this, &USmashCharacterStateNormalSpecialJammus::OnEnergyBallCharged);
		StoredEnergyBall->SetActorLocation(StateMachine->GetCharacter()->GetActorLocation() +
			(StateMachine->GetCharacter()->GetOrientX() * BallLocationOffset));
		StoredEnergyBall->StartCharging();
	} else
	{
		Shoot();
	}
	
	Character->InputNormalSpecialAttack.AddDynamic(this, &USmashCharacterStateNormalSpecialJammus::OnInputNormalSpecialAttack);
}

void USmashCharacterStateNormalSpecialJammus::StateExit(ESmashCharacterStateID NextStateID)
{
	Super::StateExit(NextStateID);
	Character->InputNormalSpecialAttack.RemoveDynamic(this, &USmashCharacterStateNormalSpecialJammus::OnInputNormalSpecialAttack);
}

void USmashCharacterStateNormalSpecialJammus::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);
}

void USmashCharacterStateNormalSpecialJammus::OnInputNormalSpecialAttack()
{
	Shoot();
	StateMachine->ChangeState(ESmashCharacterStateID::Idle);
}


void USmashCharacterStateNormalSpecialJammus::Shoot()
{
	StoredEnergyBall->Shoot(Character->GetOrientX());
	StoredEnergyBall->OnChargedEvent.RemoveDynamic(this, &USmashCharacterStateNormalSpecialJammus::OnEnergyBallCharged);
	//Detach ball
	StoredEnergyBall = nullptr;
}


