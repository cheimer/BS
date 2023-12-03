// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Service/BSFindPlayerPosService.h"
#include "Enemy/BSEnemyAIController.h"
#include "BSComponent/BSAIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

UBSFindPlayerPosService::UBSFindPlayerPosService()
{
	NodeName = "Find Player Pos";
}

void UBSFindPlayerPosService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Blackboard) return;

	const auto Controller = OwnerComp.GetAIOwner();
	if (!Controller) return;

	const auto PerceptionComp = Controller->FindComponentByClass<UBSAIPerceptionComponent>();
	if (!PerceptionComp) return;

	Blackboard->SetValueAsObject(PlayerActorKey.SelectedKeyName, PerceptionComp->GetPlayerActor());

	if (!PerceptionComp->GetPlayerActor()) return; // nullptr일 경우 위는 nullptr 입력, 아래는 입력X
	Blackboard->SetValueAsVector(PlayerVecKey.SelectedKeyName, PerceptionComp->GetPlayerActor()->GetActorLocation());

}
