// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Service/BSFindPlayerPosService.h"
#include "Enemy/BSEnemyAIController.h"
#include "Enemy/BSEnemyCharacter.h"
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

	ABSEnemyCharacter* Enemy = GetServicedEnemy(OwnerComp);

	if (!GetWorld()->GetFirstPlayerController()) return;
	const auto Player = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!Player || !Enemy) return;

	if (FVector::Dist(Player->GetActorLocation(), Enemy->GetActorLocation()) > Enemy->States.SearchRange) return;

	Blackboard->SetValueAsObject(PlayerActorKey.SelectedKeyName, Player);
	Blackboard->SetValueAsVector(PlayerVecKey.SelectedKeyName, Player->GetActorLocation());

}

ABSEnemyCharacter* UBSFindPlayerPosService::GetServicedEnemy(UBehaviorTreeComponent& OwnerComp)
{
	const auto Controller = OwnerComp.GetAIOwner();
	if (!Controller) return nullptr;

	const auto Enemy = Cast<ABSEnemyCharacter>(Controller->GetPawn());
	if (!Enemy) return nullptr;

	return Enemy;
}
