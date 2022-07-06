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
	if(bCanUse)
	{
		GetWorldTimerManager().SetTimer(PlayFireEffectTimerHandle, this, &ANCEAutoWeapon::PlayFireEffect,AutoFireDelay,true,0.f);
	}
}


void ANCEAutoWeapon::ServerFireEvent()
{
	Super::ServerFireEvent();
	
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
	Barrel->Shoot(ShootStatr,ShootDirecrion,Controller,CachedCharacterOwner);
	Multicast_PlayFireEffect();
}

void ANCEAutoWeapon::StopFire()
{
	Super::StopFire();

	GetWorldTimerManager().ClearTimer(PlayFireEffectTimerHandle);
}

void ANCEAutoWeapon::ServerStopFireEvent()
{
	Super::ServerStopFireEvent();
	
	GetWorldTimerManager().ClearTimer(AutoFireTimerHandle);
}

void ANCEAutoWeapon::PlayFireEffect()
{
	WeaponMesh->PlayAnimation(FireAnimMontage,false);
}

void ANCEAutoWeapon::Multicast_PlayFireEffect_Implementation()
{
	if(!CachedCharacterOwner->IsLocallyControlled())
	{
		PlayFireEffect();
	}
}
