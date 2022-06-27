// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipments/NCEBaseWeapon.h"
#include "Character/NCECharacter.h"

// Sets default values
ANCEBaseWeapon::ANCEBaseWeapon()
{
 	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("WeaponRoot"));

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(RootComponent);

	Barrel = CreateDefaultSubobject<UBarrelComponent>(TEXT("BarrelCpmponent"));
	Barrel->SetupAttachment(WeaponMesh,MuzzelSktName);
}

void ANCEBaseWeapon::Fire(){}

void ANCEBaseWeapon::StopFire(){}

// Called when the game starts or when spawned
void ANCEBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	AActor* OwningCharacter = GetOwner();
	if(OwningCharacter)
	{
		CachedCharacterOwner = StaticCast<ANCECharacter*>(OwningCharacter);
	}

	Barrel->SetDamageAmount(Damage);
}

void ANCEBaseWeapon::SetUseDelay()
{
	bCanUse = false;
	GetWorldTimerManager().SetTimer(DelayedReuseTimerHandle, this,&ANCEBaseWeapon::SetCanUseToTrue, DelayedReuse);
}




