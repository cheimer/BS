// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Service/BSStopMoveService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/BSEnemyCharacter.h"
#include "Player/BSPlayerCharacter.h"


UBSStopMoveService::UBSStopMoveService()
{
	NodeName = "StopMoveNode";
}

void UBSStopMoveService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (PlayerInRange(OwnerComp))
	{
		//TEMP 밑의 코드가 작동 안됨. 
		//OwnerComp.RequestExecution(EBTNodeResult::Aborted);
		OwnerComp.RestartLogic();
	}
	
}

bool UBSStopMoveService::PlayerInRange(UBehaviorTreeComponent& OwnerComp)
{
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Blackboard) return false;

	const auto Controller = OwnerComp.GetAIOwner();
	if (!Controller) return false;

	auto PlayerActor = Blackboard->GetValueAsObject(PlayerActorKey.SelectedKeyName);
	auto Player = Cast<ABSPlayerCharacter>(PlayerActor);

	auto EnemyActor = Blackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName);
	auto Enemy = Cast<ABSEnemyCharacter>(EnemyActor);
	if (!Player || !Enemy) return false;

	float Distance = Enemy->GetDistanceTo(Player);

	if (Enemy->States.AttackRange > Distance)
		return true;
	else
		return false;

}
