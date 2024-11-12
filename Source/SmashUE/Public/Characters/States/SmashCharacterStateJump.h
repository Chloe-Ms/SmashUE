// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/SmashCharacterState.h"
#include "SmashCharacterStateJump.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SMASHUE_API USmashCharacterStateJump : public USmashCharacterState
{
	GENERATED_BODY()
private:
	//Test
	const float Gravity = 9.81f;
	
public:
	UPROPERTY(EditAnywhere)
	float JumpWalkSpeed = 400.f;

	UPROPERTY(EditAnywhere)
	float JumpMaxHeight = 280.f;
	
	UPROPERTY(EditAnywhere)
	float JumpDuration = 1.f;

	UPROPERTY(EditAnywhere)
	float JumpAirControl = 1.f;

	// Sets default values for this component's properties
	USmashCharacterStateJump();

	virtual void StateInit(USmashCharacterStateMachine* InStateMachine) override;
	
	virtual void StateEnter(ESmashCharacterStateID PreviousStateID) override;
	
	virtual void StateExit(ESmashCharacterStateID NextStateID) override;
	
	virtual void StateTick(float DeltaTime) override;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY()
	float Timer;

	UPROPERTY()
	float InitialVelocityY;

	UPROPERTY()
	float VelocityY;
};
