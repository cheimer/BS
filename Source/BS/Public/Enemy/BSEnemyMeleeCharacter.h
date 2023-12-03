// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/BSEnemyCharacter.h"
#include "BSEnemyMeleeCharacter.generated.h"

/**
 * 
 */
UCLASS()
class BS_API ABSEnemyMeleeCharacter : public ABSEnemyCharacter
{
	GENERATED_BODY()
	
protected:
	virtual void OnAttack(AActor* Attacker) override;
};
