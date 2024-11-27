// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JammusEnergyBall.generated.h"

UCLASS()
class SMASHUE_API AJammusEnergyBall : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	float TimeToFullyCharge = 5.f;
	
	// Sets default values for this actor's properties
	AJammusEnergyBall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "ChargeStart"))
	void ReceiveChargeStart();

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "ChargeStart"))
	void ReceiveChargeStop();
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
