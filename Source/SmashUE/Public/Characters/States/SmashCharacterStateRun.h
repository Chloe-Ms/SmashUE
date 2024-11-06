// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/SmashCharacterState.h"
#include "SmashCharacterStateRun.generated.h"


UCLASS(ClassGroup=(SmashCharacterState), meta=(BlueprintSpawnableComponent))
class SMASHUE_API USmashCharacterStateRun : public USmashCharacterState
{
public:
	virtual ESmashCharacterStateID GetStateID() override;
	
	virtual void StateInit(USmashCharacterStateMachine* InStateMachine) override;
	
	virtual void StateEnter(ESmashCharacterStateID PreviousStateID) override;
	
	virtual void StateExit(ESmashCharacterStateID NextStateID) override;
	
	virtual void StateTick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	float RunSpeedMax = 1000.f;

private:
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USmashCharacterStateRun();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	
};
