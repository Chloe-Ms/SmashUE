// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/SmashCharacterState.h"
#include "SmashCharacterStateNormalSpecial.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SMASHUE_API USmashCharacterStateNormalSpecial : public USmashCharacterState
{
public:
	virtual ESmashCharacterStateID GetStateID() override { return ESmashCharacterStateID::SpecialAttack; }

private:
	GENERATED_BODY()
};
