// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/CameraWorldSubsystem.h"

#include "Camera/CameraComponent.h"
#include "Camera/CameraFollowTarget.h"
#include "Camera/CameraSettings.h"
#include "Kismet/GameplayStatics.h"

void UCameraWorldSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	
	CameraSettings = GetDefault<UCameraSettings>();
	
	CameraMain = FindCameraByTag(CameraSettings->CameraMainTag);

	AActor* CameraBoundsActor = FindCameraBoundsActor();
	if (CameraBoundsActor != nullptr)
	{
		InitCameraBounds(CameraBoundsActor);
	}

	InitCameraZoomParameters();
}

void UCameraWorldSubsystem::PostInitialize()
{
	Super::PostInitialize();
}

void UCameraWorldSubsystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TickUpdateCameraZoom(DeltaTime);
	TickUpdateCameraPosition(DeltaTime);
}

void UCameraWorldSubsystem::InitCameraZoomParameters()
{
	TArray<AActor*> FoundCamerasMin, FoundCamerasMax;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(),CameraSettings->CameraDistanceMinTag, FoundCamerasMin);
	if (CameraMain == nullptr || CameraMain->GetOwner() == nullptr) return;
	
	FVector locationCameraMain = CameraMain->GetOwner()->GetActorLocation();

	if (FoundCamerasMin.Num() > 0)
	{
		AActor* cameraMin = FoundCamerasMin[0];
		CameraZoomYMin = cameraMin->GetActorLocation().Y;
		if (locationCameraMain.Y < CameraZoomYMin)
		{
			locationCameraMain.Y = CameraZoomYMin;
			CameraMain->GetOwner()->SetActorLocation(locationCameraMain);
		}
	}
	
	UGameplayStatics::GetAllActorsWithTag(GetWorld(),CameraSettings->CameraDistanceMaxTag, FoundCamerasMax);
	if (FoundCamerasMax.Num() > 0)
	{
		AActor* cameraMax = FoundCamerasMax[0];
		CameraZoomYMax = cameraMax->GetActorLocation().Y;
		if (locationCameraMain.Y > CameraZoomYMax)
		{
			locationCameraMain.Y = CameraZoomYMax;
			CameraMain->GetOwner()->SetActorLocation(locationCameraMain);
		}
	}	
}

void UCameraWorldSubsystem::TickUpdateCameraZoom(float DeltaTime)
{
	if (CameraMain == nullptr) return;
	float GreatestDistanceBetweenTargets = CalculateGreatestDistanceBetweenTargets();

	float inverseValue = FMath::Clamp(FMath::GetRangePct(CameraSettings->DistanceBetweenTargetsMin,
		CameraSettings->DistanceBetweenTargetsMax,
		GreatestDistanceBetweenTargets), 0.f, 1.f);

	FVector locationCameraMain = CameraMain->GetOwner()->GetActorLocation();
	
	//locationCameraMain.Y = FMath::Lerp(CameraZoomYMin,CameraZoomYMax,inverseValue);
	float newCameraLocationY = FMath::Lerp(CameraZoomYMin,CameraZoomYMax,inverseValue);
	locationCameraMain.Y = FMath::Lerp(locationCameraMain.Y,newCameraLocationY,DeltaTime * CameraSettings->SizeDampingFactor);
	CameraMain->GetOwner()->SetActorLocation(locationCameraMain);
}

void UCameraWorldSubsystem::AddFollowTarget(UObject* FollowTarget)
{
	FollowTargets.Add(FollowTarget);
}

void UCameraWorldSubsystem::RemoveFollowTarget(UObject* FollowTarget)
{
	FollowTargets.Remove(FollowTarget);
}

AActor* UCameraWorldSubsystem::FindCameraBoundsActor()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(),CameraSettings->CameraBoundsTag, FoundActors);
	if (FoundActors.Num() == 0) return nullptr;
	
	return FoundActors[0];
}

void UCameraWorldSubsystem::InitCameraBounds(AActor* CameraBoundsActor)
{
	FVector BoundsCenter;
	FVector BoundsExtents;
	CameraBoundsActor->GetActorBounds(false, BoundsCenter, BoundsExtents);

	CameraBoundsYProjectionCenter = BoundsCenter.Y;
	CameraBoundsMin = FVector2D(BoundsCenter.X - BoundsExtents.X,BoundsCenter.Z - BoundsExtents.Z);
	CameraBoundsMax = FVector2D(BoundsCenter.X + BoundsExtents.X,BoundsCenter.Z + BoundsExtents.Z);
}

void UCameraWorldSubsystem::ClampPositionIntoCameraBounds(FVector& Position)
{
	FVector2D ViewportBoundsMin, ViewportBoundsMax;
	GetViewportBounds(ViewportBoundsMin, ViewportBoundsMax);

	FVector WorldBoundsMin = CalculateWorldPositionFromViewportPosition(ViewportBoundsMin);
	FVector WorldBoundsMax = CalculateWorldPositionFromViewportPosition(ViewportBoundsMax);

	float offsetX = (WorldBoundsMax.X - WorldBoundsMin.X) / 2.f;
	float offsetZ = (WorldBoundsMin.Z - WorldBoundsMax.Z) / 2.f;
	Position.X = FMath::Clamp(Position.X,CameraBoundsMin.X + offsetX,CameraBoundsMax.X - offsetX);
	Position.Z = FMath::Clamp(Position.Z,CameraBoundsMin.Y + offsetZ,CameraBoundsMax.Y - offsetZ);
}

void UCameraWorldSubsystem::GetViewportBounds(FVector2D& OutViewportBoundsMin, FVector2D& OutViewportBoundsMax)
{
	UGameViewportClient* ViewportClient = GetWorld()->GetGameViewport();
	if (ViewportClient == nullptr) return;

	FViewport* Viewport = ViewportClient->Viewport;
	if (Viewport == nullptr) return;

	FIntRect ViewRect(
		Viewport->GetInitialPositionXY(),
		Viewport->GetInitialPositionXY() + Viewport->GetSizeXY()
	);

	FIntRect ViewportRect = Viewport->CalculateViewExtents(CameraMain->AspectRatio,ViewRect);

	OutViewportBoundsMin.X = ViewportRect.Min.X;
	OutViewportBoundsMin.Y = ViewportRect.Min.Y;
	
	OutViewportBoundsMax.X = ViewportRect.Max.X;
	OutViewportBoundsMax.Y = ViewportRect.Max.Y;
}

FVector UCameraWorldSubsystem::CalculateWorldPositionFromViewportPosition(const FVector2D& ViewportPosition)
{
	if (CameraMain == nullptr) return FVector::Zero();

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController == nullptr) return FVector::Zero();

	float YDistanceToCenter = CameraMain->GetOwner()->GetActorLocation().Y - CameraBoundsYProjectionCenter;

	FVector CameraWorldProjectDir;
	FVector WorldPosition;
	UGameplayStatics::DeprojectScreenToWorld(
		PlayerController,
		ViewportPosition,
		WorldPosition,
		CameraWorldProjectDir
		);

	WorldPosition += CameraWorldProjectDir * YDistanceToCenter;

	return WorldPosition;
}

void UCameraWorldSubsystem::TickUpdateCameraPosition(float DeltaTime)
{
	FVector TargetPosition = CalculateAveragePositionBetweenTargets();
	FVector CurrentLocation = CameraMain->GetOwner()->GetActorLocation();
	TargetPosition.Y = CurrentLocation.Y;
	ClampPositionIntoCameraBounds(TargetPosition);
	
	TargetPosition = FMath::Lerp(CurrentLocation,TargetPosition,DeltaTime * CameraSettings->PositionDampingFactor);
	CameraMain->GetOwner()->SetActorLocation(TargetPosition);
}

FVector UCameraWorldSubsystem::CalculateAveragePositionBetweenTargets()
{
	FVector AveragePosition = FVector::ZeroVector;
	int FollowableCount = 0;
	for (UObject* Target : FollowTargets)
	{
		ICameraFollowTarget* FollowTarget = Cast<ICameraFollowTarget>(Target);
		if (FollowTarget && FollowTarget->IsFollowable())
		{
			AveragePosition+= FollowTarget->GetFollowPosition();
			FollowableCount++;
		}
	}

	if (FollowableCount > 0)
		AveragePosition /= FollowableCount;
	return AveragePosition;
}

float UCameraWorldSubsystem::CalculateGreatestDistanceBetweenTargets()
{
	float GreatestDistance = 0.f;
	//FollowTargets
	int i = 0;
	int j;
	while (i < FollowTargets.Num())
	{
		ICameraFollowTarget* FollowTargetOne = Cast<ICameraFollowTarget>(FollowTargets[i]);
		j = i + 1;
		while (j < FollowTargets.Num())
		{
			ICameraFollowTarget* FollowTargetTwo = Cast<ICameraFollowTarget>(FollowTargets[j]);
			if (FollowTargetOne && FollowTargetTwo)
			{
				float distance = FVector::Distance(FollowTargetOne->GetFollowPosition(),FollowTargetTwo->GetFollowPosition());
				if (distance > GreatestDistance)
				{
					GreatestDistance = distance;
				}
			}
			j++;
		}
		i++;
	}
	return GreatestDistance;
}

UCameraComponent* UCameraWorldSubsystem::FindCameraByTag(const FName& Tag) const
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), Tag, FoundActors);
	if (FoundActors.Num() == 0) return nullptr;
	
	UCameraComponent* CameraComponent = FoundActors[0]->GetComponentByClass<UCameraComponent>();
	
	return CameraComponent;
}
