// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/CameraWorldSubsystem.h"

#include "Kismet/GameplayStatics.h"

void UCameraWorldSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	CameraMain = FindCameraByTag(TEXT("CameraMain"));
}

void UCameraWorldSubsystem::PostInitialize()
{
	Super::PostInitialize();
}

void UCameraWorldSubsystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TickUpdateCameraPosition(DeltaTime);
}

void UCameraWorldSubsystem::AddFollowTarget(AActor* FollowTarget)
{
	FollowTargets.Add(FollowTarget);
}

void UCameraWorldSubsystem::RemoveFollowTarget(AActor* FollowTarget)
{
	FollowTargets.Remove(FollowTarget);
}

void UCameraWorldSubsystem::TickUpdateCameraPosition(float DeltaTime)
{
	FVector TargetPosition = CalculateAveragePositionBetweenTargets();
	FVector CurrentLocation = CameraMain->GetOwner()->GetActorLocation();
	TargetPosition.Y = CurrentLocation.Y;
	CameraMain->GetOwner()->SetActorLocation(TargetPosition);
}

FVector UCameraWorldSubsystem::CalculateAveragePositionBetweenTargets()
{
	FVector AveragePosition = FVector::ZeroVector;

	for (AActor* target : FollowTargets)
	{
		AveragePosition += target->GetActorLocation();
	}

	AveragePosition /= FollowTargets.Num();
	return AveragePosition;
}

UCameraComponent* UCameraWorldSubsystem::FindCameraByTag(const FName& Tag) const
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), Tag, FoundActors);
	if (FoundActors.Num() == 0) return nullptr;
	
	UCameraComponent* CameraComponent = FoundActors[0]->GetComponentByClass<UCameraComponent>();
	
	return CameraComponent;
}
