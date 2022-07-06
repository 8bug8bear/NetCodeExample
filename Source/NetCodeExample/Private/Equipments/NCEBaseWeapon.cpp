// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipments/NCEBaseWeapon.h"
#include "Character/NCECharacter.h"
#include "Net/UnrealNetwork.h"



// Sets default values
ANCEBaseWeapon::ANCEBaseWeapon()
{
 	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("WeaponRoot"));

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(RootComponent);

	Barrel = CreateDefaultSubobject<UBarrelComponent>(TEXT("BarrelCpmponent"));
	Barrel->SetupAttachment(WeaponMesh,MuzzelSktName);

	bReplicates = true;
}

void ANCEBaseWeapon::Fire()
{
	if(bCanUse)
	{
		Server_Fire();
	}
}

void ANCEBaseWeapon::Server_Fire_Implementation()
{
	ServerFireEvent();
}

void ANCEBaseWeapon::ServerFireEvent(){}

void ANCEBaseWeapon::StopFire()
{
	Server_StopFire();
}

void ANCEBaseWeapon::Server_StopFire_Implementation()
{
	ServerStopFireEvent();
}

void ANCEBaseWeapon::ServerStopFireEvent(){}

void ANCEBaseWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ANCEBaseWeapon,bCanUse);
	DOREPLIFETIME(ANCEBaseWeapon,CachedCharacterOwner);
}

// Called when the game starts or when spawned
void ANCEBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	if(HasAuthority())
	{
		AActor* OwningCharacter = GetOwner();
		if(OwningCharacter)
		{
			CachedCharacterOwner = StaticCast<ANCECharacter*>(OwningCharacter);
		}

		Barrel->SetDamageAmount(Damage);
	}
	
}

void ANCEBaseWeapon::SetUseDelay()
{
	bCanUse = false;
	GetWorldTimerManager().SetTimer(DelayedReuseTimerHandle, this,&ANCEBaseWeapon::SetCanUseToTrue, DelayedReuse);
}




