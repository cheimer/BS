// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Deco/BSAttackAnimPlayDeco.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/BSEnemyCharacter.h"

UBSAttackAnimPlayDeco::UBSAttackAnimPlayDeco()
{
	NodeName = "Is Playing Anim";
}

bool UBSAttackAnimPlayDeco::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	const auto Blackboard = OwnerComp.GetBlackboardComponent();

	const auto EnemyActor = Blackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName);
	if (!EnemyActor) return false;

	const auto Enemy = Cast<ABSEnemyCharacter>(EnemyActor);
	if (!Enemy) return false;

	if (Enemy->GetMesh()->GetAnimInstance()->IsAnyMontagePlaying())
	{
		return true;
	}
	else
	{
		return false;
	}

}
