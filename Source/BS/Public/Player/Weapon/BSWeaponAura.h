// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/Weapon/BSPlayerWeapon.h"
#include "BSWeaponAura.generated.h"

/**
 * 
 */
UCLASS()
class BS_API ABSWeaponAura : public ABSPlayerWeapon
{
	GENERATED_BODY()
	
public:
	ABSWeaponAura();

protected:
	void SetDefaultOption() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arrow")
	float LifeTime = 1.0f;

};
