// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/SmashCharacterState.h"
#include "SmashCharacterStateFall.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SMASHUE_API USmashCharacterStateFall : public USmashCharacterState
{
private:
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	float FallHorizontalMoveSpeed = 100.f;

	UPROPERTY(EditAnywhere)
	float FallAirControl = 1.f;

	UPROPERTY(EditAnywhere)
	float FallGravityScale = 3.f;

	UPROPERTY(EditAnywhere)
	float FallFastGravityScale = 10.f;

	// Sets default values for this component's properties
	USmashCharacterStateFall();

	virtual ESmashCharacterStateID GetStateID() override;

	virtual void StateInit(USmashCharacterStateMachine* InStateMachine) override;

	virtual void StateEnter(ESmashCharacterStateID PreviousStateID) override;

	virtual void StateExit(ESmashCharacterStateID NextStateID) override;
	
	void MoveHorizontally();

	virtual void StateTick(float DeltaTime) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
};
