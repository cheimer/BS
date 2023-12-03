// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/Weapon/BSPlayerWeapon.h"
#include "BSWeaponSpell.generated.h"

/**
 * 
 */
UCLASS()
class BS_API ABSWeaponSpell : public ABSPlayerWeapon
{
	GENERATED_BODY()
	
public:
	ABSWeaponSpell();

protected:
	void SetDefaultOption() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arrow")
	float LifeTime = 2.0f;

};
