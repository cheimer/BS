// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BSHealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnDeathSignature, AActor*);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BS_API UBSHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBSHealthComponent();

	FOnDeathSignature OnDeathSignature;

	bool IsDead() { return FMath::IsNearlyZero(CurrentHealth); }
	bool IsFullHealth() { return FMath::IsNearlyEqual(CurrentHealth, MaxHealth); }
	float GetHealthPercentage() { return CurrentHealth / MaxHealth; }
	void SetHealthFull();

protected:
	virtual void BeginPlay() override;

private:
	void SetHealth(float NewHealth);

	UFUNCTION()
	void OnTakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
		class AController* InstigatedBy, AActor* DamageCauser);

	float MaxHealth = 0.0f;
	float CurrentHealth = 0.0f;

};
