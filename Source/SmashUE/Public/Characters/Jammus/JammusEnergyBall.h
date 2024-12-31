// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SmashCharacterStateNormalSpecialJammus.h"
#include "GameFramework/Actor.h"
#include "JammusEnergyBall.generated.h"

class ASmashCharacter;

UENUM(BlueprintType)
enum class ESmashCharacterNormalSpecialState : uint8
{
	None,
	Charging,
	Charged
};

UCLASS()
class SMASHUE_API AJammusEnergyBall : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	float TimeToFullyCharge = 5.f;

	UPROPERTY(BlueprintReadOnly)
	float ChargeRatio = 0.f;
	
	AJammusEnergyBall();

private:
	UPROPERTY()
	float CurrentTimeCharged = 0.f;

	UPROPERTY()
	TObjectPtr<USmashCharacterStateNormalSpecialJammus> NormalSpecialState;

	UPROPERTY()
	TObjectPtr<ASmashCharacter> JammusSmashCharacter;

	ESmashCharacterNormalSpecialState AttackState;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "ChargeStart"))
	void ReceiveChargeStart();

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "ChargeStop"))
	void ReceiveChargeStop();

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Shoot"))
	void ReceiveShoot(float Orientation);
	
public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnChargedEvent);

	UPROPERTY()
	FOnChargedEvent OnChargedEvent;
	
	void Init(ASmashCharacter* Character, USmashCharacterStateNormalSpecialJammus* State);
	
	void StartCharging();

	void Shoot(float Orientation);
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
