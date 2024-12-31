// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/States/SmashCharacterStateNormalSpecial.h"
#include "SmashCharacterStateNormalSpecialJammus.generated.h"

class AJammusEnergyBall;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SMASHUE_API USmashCharacterStateNormalSpecialJammus : public USmashCharacterStateNormalSpecial
{
public:
	virtual void StateInit(USmashCharacterStateMachine* InStateMachine) override;
	UFUNCTION()
	void OnEnergyBallCharged();
	virtual void StateEnter(ESmashCharacterStateID PreviousStateID) override;
	virtual void StateExit(ESmashCharacterStateID NextStateID) override;
	virtual void StateTick(float DeltaTime) override;

private:
	GENERATED_BODY()

	UFUNCTION()
	void OnInputNormalSpecialAttack();

	UFUNCTION()
	void Shoot();

	UPROPERTY()
	AJammusEnergyBall* StoredEnergyBall;

public:
	UPROPERTY(EditAnywhere)
	FVector BallLocationOffset;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AJammusEnergyBall> EnergyBall;
};
