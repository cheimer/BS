// Fill out your copyright notice in the Description page of Project Settings.

//DEFINE_LOG_CATEGORY(LogSetting);

#include "Enemy/BSEnemyCharacter.h"
#include "Enemy/BSEnemyAIController.h"
#include "Player/BSPlayerCharacter.h"
#include "Animation/BSAttackAnimNotify.h"
#include "BSComponent/BSHealthComponent.h"
#include "BSComponent/BSItemDropComponent.h"
#include "BSGameModeBase.h"
#include "BSCoreTypes.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/DamageEvents.h"
#include "Engine/DataTable.h"
#include "BrainComponent.h"


ABSEnemyCharacter::ABSEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	AIControllerClass = ABSEnemyAIController::StaticClass();

	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate.Yaw = 500.0f;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Enemy"));

	HealthComponent = CreateDefaultSubobject<UBSHealthComponent>("HealthComponent");
	ItemDropComponent = CreateDefaultSubobject<UBSItemDropComponent>("ItemDropComponent");

}

void ABSEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (!AttackAnims.Num() || !DeathAnim)
	{
		UE_LOG(LogTemp, Warning, TEXT("AttackAnim, DeathAnim Is NULL"));
	}

	check(BehaviorTree);

	for (auto AttackAnim : AttackAnims)
	{
		auto AttackNotify = AnimUtils::FindNotifyByClass<UBSAttackAnimNotify>(AttackAnim);
		if (!AttackNotify) continue;

		AttackNotify->OnAttackNotifySignature.AddUObject(this, &ABSEnemyCharacter::OnAttack);
	}

	if (bUseDataTableEnemy)
	{
		check(DTEnemy);
		SetEnemyDefault();
	}

	HealthComponent->OnDeathSignature.AddUObject(this, &ABSEnemyCharacter::OnDeath);

	GetCharacterMovement()->MaxWalkSpeed = States.Speed;
	
}

void ABSEnemyCharacter::PlayAttackAnim()
{
	for (int i = 0; i < AttackAnims.Num(); i++)
	{
		if (GetMesh()->GetAnimInstance()->Montage_IsPlaying(AttackAnims[i]))
			return;
		else if (GetMesh()->GetAnimInstance()->Montage_IsPlaying(DeathAnim))
			return;
	}

	int32 AnimsNum = AttackAnims.Num();
	int32 RandNum = rand() % AnimsNum;

	SetActorRotationPlayer();

	PlayAnimMontage(AttackAnims[RandNum]);

}

void ABSEnemyCharacter::OnDeath(AActor* DeathActor)
{
	if (!DeathActor->IsA(this->StaticClass())) return;

	PlayAnimMontage(DeathAnim);

	ItemDropComponent->ItemDropStart(States.DefaultDropCoin * States.DropMultiplier, States.DefaultDropMaterial * States.DropMultiplier);

	GetCharacterMovement()->DisableMovement();
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	SetLifeSpan(3.0f);

	const auto EnemyController = Cast<AAIController>(GetController());
	if (EnemyController && EnemyController->BrainComponent)
	{
		EnemyController->BrainComponent->Cleanup();
	}

	FTimerHandle TimerHandler;
	GetWorld()->GetTimerManager().SetTimer(TimerHandler, this, &ABSEnemyCharacter::DeathAnimEnd, DeathAnim->GetPlayLength() * 0.8f, false);

}

bool ABSEnemyCharacter::IsDead()
{
	return HealthComponent->IsDead();
}

void ABSEnemyCharacter::DeathAnimEnd()
{
	GetMesh()->GetAnimInstance()->Montage_SetPlayRate(DeathAnim, 0.0f);
}

float ABSEnemyCharacter::GetDistancePlayer() const
{
	if (!GetWorld()) return 0.0f;

	const auto GameMode = Cast<ABSGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return 0.0f;

	const auto Player = GameMode->GetBSPlayerCharacter();
	if (!Player) return 0.0f;

	FVector PlayerLocation = Player->GetActorLocation();
	FVector EnemyLocation = GetActorLocation();

	float Distance = FVector::Distance(PlayerLocation, EnemyLocation);

	return Distance;
}

void ABSEnemyCharacter::OnAttack(AActor* Attacker)
{
	
}

void ABSEnemyCharacter::SetActorRotationPlayer()
{
	if (!GetWorld()) return;

	const auto GameMode = Cast<ABSGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return;

	const auto Player = GameMode->GetBSPlayerCharacter();
	if (!Player) return;

	FVector PlayerLocation = Player->GetActorLocation();
	FRotator NewRotation = (PlayerLocation - GetActorLocation()).Rotation();
	SetActorRotation(NewRotation);
}

void ABSEnemyCharacter::SetEnemyDefault()
{
	if (EnemyName.IsEqual("")) return;

	FEnemyState* DTEnemyState = DTEnemy->FindRow<FEnemyState>(EnemyName, "");
	if (!DTEnemyState) return;

	States.AttackDelay = DTEnemyState->AttackDelay;
	States.AttackRange = DTEnemyState->AttackRange;
	States.AttackType = DTEnemyState->AttackType;
	States.Damage = DTEnemyState->Damage;
	States.DefaultDropCoin = DTEnemyState->DefaultDropCoin;
	States.DefaultDropMaterial = DTEnemyState->DefaultDropMaterial;
	States.DropMultiplier = DTEnemyState->DropMultiplier;
	States.Health = DTEnemyState->Health;
	States.SearchRange = DTEnemyState->SearchRange;
	States.Speed = DTEnemyState->Speed;

}
