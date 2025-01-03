﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "CameraSettings.generated.h"

/**
 * 
 */
UCLASS(Config = Game, DefaultConfig, meta = (DisplayName = "Camera Settings"))
class SMASHUE_API UCameraSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:
	UPROPERTY(Config, EditAnywhere, Category = "Camera Settings")
	FName CameraMainTag;

	UPROPERTY(Config, EditAnywhere, Category = "Camera Settings")
	FName CameraDistanceMinTag;

	UPROPERTY(Config, EditAnywhere, Category = "Camera Settings")
	FName CameraDistanceMaxTag;

	UPROPERTY(Config, EditAnywhere, Category = "Camera Settings")
	FName CameraBoundsTag;

	UPROPERTY(Config, EditAnywhere, Category = "Camera Settings")
	float DistanceBetweenTargetsMin = 300.f;

	UPROPERTY(Config, EditAnywhere, Category = "Camera Settings")
	float DistanceBetweenTargetsMax = 1500.f;

	UPROPERTY(Config, EditAnywhere, Category = "Camera Settings")
	float SizeDampingFactor = 5.f;

	UPROPERTY(Config, EditAnywhere, Category = "Camera Settings")
	float PositionDampingFactor = 5.f;
};
