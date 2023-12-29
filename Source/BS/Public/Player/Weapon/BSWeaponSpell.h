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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
	float LifeTime = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell", meta = (ClampMin = 1))
	int32 SizeAddLevel = 5;

private:
	void SetSpellLevelAdd();

};
