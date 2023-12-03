// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "BSAttackAnimNotify.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnAttackNotifySignature, AActor*);

UCLASS()
class BS_API UBSAttackAnimNotify : public UAnimNotify
{
	GENERATED_BODY()

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	FOnAttackNotifySignature OnAttackNotifySignature;
};
