// Fill out your copyright notice in the Description page of Project Settings.


#include "BSAttackAnimNotify.h"

void UBSAttackAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	OnAttackNotifySignature.Broadcast(MeshComp->GetOwner());
}
