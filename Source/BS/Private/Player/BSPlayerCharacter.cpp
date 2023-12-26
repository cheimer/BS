// Fill out your copyright notice in the Description page of Project Settings.

//DEFINE_LOG_CATEGORY(LogSetting);

#include "Player/BSPlayerCharacter.h"
#include "Player/BSPlayerController.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BSComponent/BSHealthComponent.h"
#include "BSComponent/BSPlayerAttackComponent.h"
#include "BSComponent/BSInvenComponent.h"
#include "BSGameModeBase.h"

//EnhancedInput
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputActionValue.h"

ABSPlayerCharacter::ABSPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

	bUseControllerRotationYaw = false;
	SpringArmComponent->TargetArmLength = SpringArmLength;
	SpringArmComponent->SetWorldRotation(FRotator(CameraRotator));
	SpringArmComponent->bDoCollisionTest = false;
	SpringArmComponent->bUsePawnControlRotation = false;
	SpringArmComponent->bInheritPitch = false;
	SpringArmComponent->bInheritYaw = false;
	SpringArmComponent->bInheritRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	GetCharacterMovement()->RotationRate.Yaw = 500.0f;

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	BSHealthComponent = CreateDefaultSubobject<UBSHealthComponent>("BSHealthComponent");
	BSAttackComponent = CreateDefaultSubobject<UBSPlayerAttackComponent>("BSAttackComponent");
	BSInvenComponent = CreateDefaultSubobject<UBSInvenComponent>("BSInvenComponent");

}

void ABSPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (!PlayerInputMapping || !MoveAction)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerInputMapping, MoveAction is NULL"));
	}

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(PlayerInputMapping, 0);
		}
	}

	BSHealthComponent->OnDeathSignature.AddUObject(this, &ABSPlayerCharacter::OnDeath);

}

void ABSPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABSPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABSPlayerCharacter::Move);
		EnhancedInputComponent->BindAction(ChangeMaterialAction, ETriggerEvent::Triggered, this, &ABSPlayerCharacter::ChangeMaterial);
	}

}

void ABSPlayerCharacter::Move(const FInputActionValue& Value)
{
	if (GetController())
	{
		const FVector2D MoveValue = Value.Get<FVector2D>();
		
		if (MoveValue.X != 0.0f)
		{
			AddMovementInput(FVector::YAxisVector, MoveValue.X);
		}
		if (MoveValue.Y != 0.0f)
		{
			AddMovementInput(FVector::XAxisVector, MoveValue.Y);
		}
	}

}

void ABSPlayerCharacter::ChangeMaterial(const FInputActionValue& Value)
{
	if (!GetController()) return;
	if (!Value.Get<bool>()) return;

	BSAttackComponent->ChangeMaterialSequence();

}

void ABSPlayerCharacter::OnDeath(AActor* DeathActor)
{
	if (!DeathActor->IsA(this->StaticClass())) return;

	GetCharacterMovement()->DisableMovement();

	GetMesh()->SetSimulatePhysics(true);

	auto GameMode = Cast<ABSGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return;

	GameMode->PlayerDeath();

}

void ABSPlayerCharacter::GetItem(AItemBase* const Item)
{
	BSInvenComponent->GetItem(Item);
}

void ABSPlayerCharacter::AttackTypeEnforce(EAttackType AttackType)
{
	if (BSInvenComponent->CanAttackTypeEnforce())
	{
		BSAttackComponent->AttackTypeEnforce(AttackType);
		BSInvenComponent->AttackTypeEnforce(AttackType);
	}

}

void ABSPlayerCharacter::AttackMaterialEnforce(EAttackMaterial AttackMaterial)
{
	if (BSInvenComponent->CanAttackMaterialEnforce(AttackMaterial))
	{
		BSAttackComponent->AttackMaterialEnforce(AttackMaterial);
		BSInvenComponent->AttackMaterialEnforce(AttackMaterial);
	}
}

int ABSPlayerCharacter::GetAttackTypeLevel(EAttackType AttackType)
{
	return BSAttackComponent->GetAttackTypeLevel(AttackType);
}

int ABSPlayerCharacter::GetAttackMaterialLevel(EAttackMaterial AttackMaterial)
{
	return BSAttackComponent->GetAttackMaterialLevel(AttackMaterial);
}

int ABSPlayerCharacter::GetAttackMaterialNum(EAttackMaterial AttackMaterial)
{
	return BSInvenComponent->GetAttackMaterialNum(AttackMaterial);
}

int32 ABSPlayerCharacter::GetCoin()
{
	return BSInvenComponent->GetCoin();
}

int32 ABSPlayerCharacter::GetMaterial()
{
	return BSInvenComponent->GetMaterialTotal();
}

float ABSPlayerCharacter::GetHealthPercentage()
{
	return BSHealthComponent->GetHealthPercentage();
}
