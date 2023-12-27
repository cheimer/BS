// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "BSCoreTypes.h"
#include "BSPlayerCharacter.generated.h"


class UCameraComponent;
class USpringArmComponent;
class UInputMappingContext;
class UInputAction;
class UBSHealthComponent;
class UBSPlayerAttackComponent;
class UBSInvenComponent;

UCLASS()
class BS_API ABSPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABSPlayerCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	float GetHealth() { return MaxHealth; }

	void GetItem(class AItemBase* const Item);

	UFUNCTION(BlueprintCallable)
	void AttackTypeEnforce(EAttackType AttackType);
	UFUNCTION(BlueprintCallable)
	void AttackMaterialEnforce(EAttackMaterial AttackMaterial);
	UFUNCTION(BlueprintCallable)
	int GetAttackTypeLevel(EAttackType AttackType);
	UFUNCTION(BlueprintCallable)
	int GetAttackMaterialLevel(EAttackMaterial AttackMaterial);
	UFUNCTION(BlueprintCallable)
	int GetAttackMaterialNum(EAttackMaterial AttackMaterial);

	UFUNCTION(BlueprintCallable)
	int32 GetCoin();
	UFUNCTION(BlueprintCallable)
	int32 GetMaterial();
	UFUNCTION(BlueprintCallable)
	float GetHealthPercentage();

	UFUNCTION(BlueprintCallable)
	void RerollMaterial();

protected:
	virtual void BeginPlay() override;

	void Move(const FInputActionValue& Value);

	void ChangeMaterial(const FInputActionValue& Value);

	UFUNCTION()
	void OnDeath(AActor* DeathActor);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UBSHealthComponent* BSHealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UBSPlayerAttackComponent* BSAttackComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UBSInvenComponent* BSInvenComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera")
	float SpringArmLength = 1000.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera")
	FRotator CameraRotator = FRotator(300.0f, 0.0f, 0.0f);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Move")
	float WalkSpeed = 600.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "State")
	float MaxHealth = 100.0f;

	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput")
	UInputMappingContext* PlayerInputMapping;

	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput")
	UInputAction* MoveAction;

	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput")
	UInputAction* ChangeMaterialAction;
private:

};
