// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Deco/BSRangedCheckDeco.h"
#include "Enemy/BSEnemyAIController.h"
#include "Enemy/BSEnemyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBSRangedCheckDeco::UBSRangedCheckDeco()
{
	NodeName = "Can Attack Ranged";
}

bool UBSRangedCheckDeco::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	const auto Controller = OwnerComp.GetAIOwner();
	if (!Controller) return false;

	const auto Blackboard = OwnerComp.GetBlackboardComponent();

	const auto DecoOwner = Cast<ABSEnemyCharacter>(Controller->GetPawn());
	if (!DecoOwner) return false;

	const auto PlayerActor = Blackboard->GetValueAsObject(PlayerActorKey.SelectedKeyName);
	if (!PlayerActor) return false; // Player가 시야 밖으로 사라짐

	const auto PlayerVec = Blackboard->GetValueAsVector(PlayerVecKey.SelectedKeyName);

	double Distance = FVector::Distance(DecoOwner->GetActorLocation(), PlayerVec);	

	if (Distance < DecoOwner->States.AttackRange)
	{
		return true;
	}
	else
	{
		return false;
	}
}
