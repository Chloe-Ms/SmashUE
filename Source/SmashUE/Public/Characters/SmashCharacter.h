// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "SmashCharacterStateID.h"
#include "Camera/CameraFollowTarget.h"
#include "GameFramework/Character.h"
#include "SmashCharacter.generated.h"

class USmashCharacterSettings;
class UInputMappingContext;
class USmashCharacterInputData;
class USmashCharacterState;
class USmashCharacterStateMachine;

UCLASS()
class SMASHUE_API ASmashCharacter : public ACharacter,
									public ICameraFollowTarget
{
private:
	GENERATED_BODY()
#pragma region Unreal Default
public:
	// Sets default values for this character's properties
	ASmashCharacter();

	UPROPERTY(EditAnywhere)
	TMap<ESmashCharacterStateID,TSubclassOf<USmashCharacterState>> OverridenStates;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
#pragma endregion
	
#pragma region Orient
public:
	float GetOrientX() const;
	
	void SetOrientX(float NewOrientX);

protected:
	UPROPERTY(BlueprintReadOnly)
	float OrientX = 1.f;

	void RotateMeshUsingOrientX() const;
	
#pragma endregion

#pragma region State Machine

public:

	void CreateStateMachine();

	void InitStateMachine();

	void TickStateMachine(float DeltaTime) const;
	
protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<USmashCharacterStateMachine> StateMachine;

#pragma endregion

#pragma region Input Data / Mapping Context

public:
	UPROPERTY()
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY()
	TObjectPtr<USmashCharacterInputData> InputData;

protected:
	void SetupMappingContextIntoController() const;
#pragma endregion

#pragma region Input Move X

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInputMoveXEvent, float, InputMoveX);

public:
	float GetInputMoveX() const;

	UPROPERTY()
	FInputMoveXEvent InputMoveXFastEvent;
	
protected:
	UPROPERTY()
	float InputMoveX = 0.f;

private:
	void OnInputMoveX(const FInputActionValue& InputActionValue);
	void OnInputMoveXFast(const FInputActionValue& InputActionValue);
	
	void BindInputMoveXAxisAndActions(UEnhancedInputComponent* EnhancedInputComponent);

#pragma endregion

#pragma region Input Jump
	
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInputJumpEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInputFastFallEvent);

public:
	UPROPERTY()
	FInputJumpEvent InputJumpEvent;

	UPROPERTY()
	FInputFastFallEvent InputFastFallEvent;
	
private:
	void OnInputJump(const FInputActionValue& InputActionValue);
	
	void OnInputFastFall(const FInputActionValue& InputActionValue);

	void BindInputJumpAndActions(UEnhancedInputComponent* EnhancedInputComponent);

#pragma endregion

#pragma region Input Attack
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInputNormalSpecialAttack);
public:
	FInputNormalSpecialAttack InputNormalSpecialAttack;

private:
	void OnInputNormalSpecialAttack(const FInputActionValue& InputActionValue);

	void BindInputAttackAndActions(UEnhancedInputComponent* EnhancedInputComponent);
	
#pragma endregion
	
#pragma region Target
	virtual FVector GetFollowPosition() override;
	
	virtual bool IsFollowable() override;
#pragma endregion
	
};
