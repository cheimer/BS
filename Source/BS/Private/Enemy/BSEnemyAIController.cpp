// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/BSEnemyAIController.h"
#include "Enemy/BSEnemyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

ABSEnemyAIController::ABSEnemyAIController()
{

}

void ABSEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetFocus(GetPlayerActor());
}

void ABSEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (const auto EnemyCharacter = Cast<ABSEnemyCharacter>(InPawn))
	{
		RunBehaviorTree(EnemyCharacter->BehaviorTree);
	}
}

AActor* ABSEnemyAIController::GetPlayerActor() const
{
	if (!GetBlackboardComponent()) return nullptr;

	return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(PlayerKeyName));

}
