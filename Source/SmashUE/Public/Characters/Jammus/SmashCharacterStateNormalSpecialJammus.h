// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/States/SmashCharacterStateNormalSpecial.h"
#include "SmashCharacterStateNormalSpecialJammus.generated.h"

UENUM(BlueprintType)
enum class SmashCharacterNormalSpecialState : uint8
{
	Charging,
	Charged
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SMASHUE_API USmashCharacterStateNormalSpecialJammus : public USmashCharacterStateNormalSpecial
{
public:
	virtual void StateInit(USmashCharacterStateMachine* InStateMachine) override;
	virtual void StateEnter(ESmashCharacterStateID PreviousStateID) override;
	virtual void StateExit(ESmashCharacterStateID NextStateID) override;
	virtual void StateTick(float DeltaTime) override;

private:
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	float TimeCharging = 3.0f;

};
