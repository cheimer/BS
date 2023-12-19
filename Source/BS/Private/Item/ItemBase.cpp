// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ItemBase.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Player/BSPlayerCharacter.h"
#include "BSComponent/BSInvenComponent.h"

AItemBase::AItemBase()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("Collision");
	SetRootComponent(CollisionComponent);

	CollisionComponent->SetCollisionProfileName(TEXT("OverlapAll"));

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	MeshComponent->SetupAttachment(CollisionComponent);

	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);


}

void AItemBase::BeginPlay()
{
	Super::BeginPlay();

	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AItemBase::ItemAcquire);

}

void AItemBase::ItemAcquire(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto Player = Cast<ABSPlayerCharacter>(OtherActor);
	if (!Player) return;

	Player->GetItem(this);

}

void AItemBase::SetMaterialAmount(EAttackMaterial SetMaterial, int32 SetAmount)
{
	MaterialType = SetMaterial;
	MaterialAmount = SetAmount;
}

int32 AItemBase::GetMaterial(EAttackMaterial& OutMaterial)
{
	OutMaterial = MaterialType;
	return MaterialAmount;
}
