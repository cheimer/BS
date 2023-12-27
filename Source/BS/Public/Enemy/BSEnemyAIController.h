// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BSEnemyAIController.generated.h"
UCLASS()
class BS_API ABSEnemyAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ABSEnemyAIController();

protected:
	virtual void Tick(float DeltaTime) override;

	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FName PlayerKeyName = "PlayerActor";

private:
	AActor* GetPlayerActor() const;

};
