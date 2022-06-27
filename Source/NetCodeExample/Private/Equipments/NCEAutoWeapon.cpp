// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipments/NCEAutoWeapon.h"
#include "Character/NCECharacter.h"

void ANCEAutoWeapon::BeginPlay()
{
	Super::BeginPlay();

	AutoFireDelay = 60.f/FireRate;
}

ANCEAutoWeapon::ANCEAutoWeapon(){}

void ANCEAutoWeapon::Fire()
{
	Super::Fire();

	if(!CachedCharacterOwner.IsValid() || !bCanUse)
	{
		return;
	}

	SetUseDelay();
	GetWorldTimerManager().SetTimer(AutoFireTimerHandle, this, &ANCEAutoWeapon::Shot,AutoFireDelay,true,0.f);
}

void ANCEAutoWeapon::Shot()
{
	AController* Controller = CachedCharacterOwner->GetController();
	FVector ShootStatr;
	FRotator ShootRotation;
	FVector ShootDirecrion;

	Controller->GetPlayerViewPoint(ShootStatr,ShootRotation);
	ShootDirecrion = ShootRotation.RotateVector(FVector::ForwardVector);
	Barrel->Shoot(ShootStatr,ShootDirecrion,Controller,CachedCharacterOwner.Get());
	WeaponMesh->PlayAnimation(FireAnimMontage,false);
}

void ANCEAutoWeapon::StopFire()
{
	Super::StopFire();

	GetWorldTimerManager().ClearTimer(AutoFireTimerHandle);
}
