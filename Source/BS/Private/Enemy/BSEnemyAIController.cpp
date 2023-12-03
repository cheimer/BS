// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/BSEnemyAIController.h"
#include "Enemy/BSEnemyCharacter.h"
#include "BSComponent/BSAIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionComponent.h"

ABSEnemyAIController::ABSEnemyAIController()
{
	BSAIPerceptionComponent = CreateDefaultSubobject<UBSAIPerceptionComponent>("BSAIPerceptionComp");
	SetPerceptionComponent(*BSAIPerceptionComponent);
	SetAISenseSightConfig();
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

void ABSEnemyAIController::SetAISenseSightConfig()
{
	SightConfig = CreateOptionalDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));

	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	SightConfig->SightRadius = AISightRadius;
	SightConfig->LoseSightRadius = AILoseSightRadius;
	SightConfig->PeripheralVisionAngleDegrees = AIFOV;
	SightConfig->SetMaxAge(AISightAge);

	GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
	GetPerceptionComponent()->ConfigureSense(*SightConfig);

}
