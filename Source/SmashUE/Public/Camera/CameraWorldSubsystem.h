// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Subsystems/WorldSubsystem.h"
#include "CameraWorldSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class SMASHUE_API UCameraWorldSubsystem : public UTickableWorldSubsystem
{
public:
	virtual TStatId GetStatId() const override { return TStatId(); };
	
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	
	virtual void PostInitialize() override;
	
	virtual void Tick(float DeltaTime) override;

	void AddFollowTarget(AActor* FollowTarget);

	void RemoveFollowTarget(AActor* FollowTarget);

private:
	GENERATED_BODY()

protected:
	UPROPERTY()
	TObjectPtr<UCameraComponent> CameraMain;

	UPROPERTY()
	TArray<AActor*> FollowTargets;

	void TickUpdateCameraPosition(float DeltaTime);

	FVector CalculateAveragePositionBetweenTargets();

	UCameraComponent* FindCameraByTag(const FName& Tag) const;
};
