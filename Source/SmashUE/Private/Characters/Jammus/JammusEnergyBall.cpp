// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Jammus/JammusEnergyBall.h"


// Sets default values
AJammusEnergyBall::AJammusEnergyBall()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AJammusEnergyBall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AJammusEnergyBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

