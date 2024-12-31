// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Jammus/JammusEnergyBall.h"

#include "Characters/SmashCharacter.h"
#include "Characters/Jammus/SmashCharacterStateNormalSpecialJammus.h"


// Sets default values
AJammusEnergyBall::AJammusEnergyBall()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AJammusEnergyBall::BeginPlay()
{
	Super::BeginPlay();
}

void AJammusEnergyBall::Init(ASmashCharacter* Character, USmashCharacterStateNormalSpecialJammus* State)
{
	JammusSmashCharacter = Character;
	NormalSpecialState = State;
}

void AJammusEnergyBall::StartCharging()
{
	AttackState = ESmashCharacterNormalSpecialState::Charging;
	ReceiveChargeStart();
}

void AJammusEnergyBall::Shoot(float Orientation)
{
	AttackState = ESmashCharacterNormalSpecialState::None;
	ReceiveChargeStop();
	ReceiveShoot(Orientation);
}

// Called every frame
void AJammusEnergyBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (AttackState == ESmashCharacterNormalSpecialState::Charging)
	{
		CurrentTimeCharged += DeltaTime;
		ChargeRatio = CurrentTimeCharged/TimeToFullyCharge;
		if (CurrentTimeCharged >= TimeToFullyCharge)
		{
			CurrentTimeCharged = TimeToFullyCharge;
			ChargeRatio = 1.f;
			AttackState = ESmashCharacterNormalSpecialState::Charged;
			OnChargedEvent.Broadcast();
			ReceiveChargeStop();
		}
	}
}

