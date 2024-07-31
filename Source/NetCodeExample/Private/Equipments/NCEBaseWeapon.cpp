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
	Barrel->SetupAttachment(WeaponMesh,MuzzleSktName);

	bReplicates = true;
}

void ANCEBaseWeapon::Fire()
{
	if(bCanUse)
	{
		Server_Fire();
		OnClientShot();
	}
}

void ANCEBaseWeapon::Server_Fire_Implementation()
{
	ServerFireEvent();
}

void ANCEBaseWeapon::ServerFireEvent()
{
	Shot();
}

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
	DOREPLIFETIME(ANCEBaseWeapon,Ammo);
}

void ANCEBaseWeapon::AddAmmo(int32 AdditionalAmmo)
{
	if(AdditionalAmmo>0)
	{
		Ammo+=AdditionalAmmo;
	}
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

void ANCEBaseWeapon::Shot()
{
	Ammo--;
	AController* Controller = CachedCharacterOwner->GetController();
	FVector ShootStart;
	FRotator ShootRotation;

	Controller->GetPlayerViewPoint(ShootStart,ShootRotation);
	const FVector ShootDirection = ShootRotation.RotateVector(FVector::ForwardVector);
	Barrel->Shoot(ShootStart,ShootDirection,Controller,CachedCharacterOwner);
	Multicast_PlayFireEffect();
}

void ANCEBaseWeapon::PlayFireEffect() const
{
	WeaponMesh->PlayAnimation(FireAnimMontage,false);
}

void ANCEBaseWeapon::OnClientShot()
{
	PlayFireEffect();
	PlayRecoil();
}

void ANCEBaseWeapon::Multicast_PlayFireEffect_Implementation()
{
	if(!CachedCharacterOwner->IsLocallyControlled())
	{
		PlayFireEffect();
	}
}
