// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Deco/BSAttackDelayDeco.h"
#include "Enemy/BSEnemyCharacter.h"
#include "Enemy/BSEnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"


UBSAttackDelayDeco::UBSAttackDelayDeco()
{
	NodeName = "Attack Delay";
}

bool UBSAttackDelayDeco::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const auto Controller = OwnerComp.GetAIOwner();
	if (!Controller) return false;

	const auto DecoOwner = Cast<ABSEnemyCharacter>(Controller->GetPawn());
	if (!DecoOwner) return false;

	float AttackDelay = DecoOwner->States.AttackDelay;

	FBTCooldownDecoratorMemory* DecoratorMemory = CastInstanceNodeMemory<FBTCooldownDecoratorMemory>(NodeMemory);
	const double TimePassed = (OwnerComp.GetWorld()->GetTimeSeconds() - DecoratorMemory->LastUseTimestamp);
	return TimePassed >= AttackDelay;

}
