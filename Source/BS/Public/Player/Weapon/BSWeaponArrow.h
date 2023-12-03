// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/Weapon/BSPlayerWeapon.h"
#include "BSWeaponArrow.generated.h"

/**
 * 
 */
UCLASS()
class BS_API ABSWeaponArrow : public ABSPlayerWeapon
{
	GENERATED_BODY()
	
public:
	ABSWeaponArrow();

protected:
	void SetDefaultOption() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arrow")
	float ArrowSpeed = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arrow")
	float LifeTime = 5.0f;

};
