// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CameraSettings.h"
#include "Subsystems/WorldSubsystem.h"
#include "CameraWorldSubsystem.generated.h"

class UCameraComponent;
/**
 * 
 */
UCLASS()
class SMASHUE_API UCameraWorldSubsystem : public UTickableWorldSubsystem
{
private:
	GENERATED_BODY()

#pragma region Subsystem Overrides
public:
	virtual TStatId GetStatId() const override { return TStatId(); };
	
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	
	virtual void PostInitialize() override;
	
	virtual void Tick(float DeltaTime) override;

#pragma endregion

#pragma region Main Camera
protected:
	UPROPERTY()
	TObjectPtr<UCameraComponent> CameraMain;
	
	UPROPERTY()
	const UCameraSettings* CameraSettings;

	void TickUpdateCameraZoom(float DeltaTime);
	
	void TickUpdateCameraPosition(float DeltaTime);
#pragma endregion

#pragma region Follow Targets
public:
	void AddFollowTarget(UObject* FollowTarget);

	void RemoveFollowTarget(UObject* FollowTarget);
	
	FVector CalculateAveragePositionBetweenTargets();

	float CalculateGreatestDistanceBetweenTargets();

protected:
	UPROPERTY()
	TArray<UObject*> FollowTargets;
	
#pragma endregion

#pragma region Bounds
protected:
	UPROPERTY()
	FVector2D CameraBoundsMin;
	
	UPROPERTY()
	FVector2D CameraBoundsMax;

	UPROPERTY()
	float CameraBoundsYProjectionCenter;

	AActor* FindCameraBoundsActor();

	void InitCameraBounds(AActor* CameraBoundsActor);

	void ClampPositionIntoCameraBounds(FVector& Position);

	void GetViewportBounds(FVector2D& OutViewportBoundsMin,FVector2D& OutViewportBoundsMax);
	
	FVector CalculateWorldPositionFromViewportPosition(const FVector2D& ViewportPosition);
	
#pragma endregion

#pragma region Zoom
	
protected:
	UPROPERTY()
	float CameraZoomYMin = 0.f;

	UPROPERTY()
	float CameraZoomYMax = 0.f;

	UFUNCTION()
	void InitCameraZoomParameters();

#pragma endregion
	
#pragma region Misc
protected:
	
	UCameraComponent* FindCameraByTag(const FName& Tag) const;
#pragma endregion
};
