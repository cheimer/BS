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

	if (!DefaultMapping || !MoveAction)
	{
		UE_LOG(LogTemp, Warning, TEXT("DefaultMapping, MoveAction is NULL"));
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

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(DefaultMapping, 0);
		}
	}

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

}

void ABSPlayerCharacter::GetItem(AItemBase* const Item)
{
	BSInvenComponent->GetItem(Item);

}

void ABSPlayerCharacter::AttackTypeEnforce(EAttackType AttackType)
{
	BSAttackComponent->AttackTypeEnforce(AttackType);
}

void ABSPlayerCharacter::AttackMaterialEnforce(EAttackMaterial AttackMaterial)
{
	BSAttackComponent->AttackMaterialEnforce(AttackMaterial);
}
