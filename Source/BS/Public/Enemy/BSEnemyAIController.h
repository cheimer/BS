// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BSEnemyAIController.generated.h"

class UBSAIPerceptionComponent;
class UAISenseConfig_Sight;

UCLASS()
class BS_API ABSEnemyAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ABSEnemyAIController();

protected:
	virtual void Tick(float DeltaTime) override;

	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	UBSAIPerceptionComponent* BSAIPerceptionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FName PlayerKeyName = "PlayerActor";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Perception")
	float AISightRadius = 1500.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Perception")
	float AILoseSightRadius = 1500.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Perception")
	float AIFOV = 180.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Perception")
	float AISightAge = 0.0f;

private:
	AActor* GetPlayerActor() const;

	void SetAISenseSightConfig();

	UAISenseConfig_Sight* SightConfig;

};
