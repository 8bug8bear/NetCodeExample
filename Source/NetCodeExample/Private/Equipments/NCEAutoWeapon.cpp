// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipments/NCEAutoWeapon.h"
#include "Character/NCECharacter.h"

void ANCEAutoWeapon::BeginPlay()
{
	Super::BeginPlay();

	AutoFireDelay = 60.f/FireRate;
}

void ANCEAutoWeapon::OnClientShot()
{
	if(Ammo<1)
	{
		GetWorldTimerManager().ClearTimer(PlayFireEffectTimerHandle);
		return;
	}
	Super::OnClientShot();
}

void ANCEAutoWeapon::Shot()
{
	if(Ammo<1)
	{
		GetWorldTimerManager().ClearTimer(AutoFireTimerHandle);
		return;
	}
	
	Super::Shot();
}

ANCEAutoWeapon::ANCEAutoWeapon(){}

void ANCEAutoWeapon::Fire()
{
	Super::Fire();
	if(bCanUse)
	{
		GetWorldTimerManager().SetTimer(PlayFireEffectTimerHandle, this, &ANCEAutoWeapon::OnClientShot,AutoFireDelay,true, AutoFireDelay);
	}
}

void ANCEAutoWeapon::ServerFireEvent()
{
	Super::ServerFireEvent();
	
	SetUseDelay();
	GetWorldTimerManager().SetTimer(AutoFireTimerHandle, this, &ANCEAutoWeapon::Shot,AutoFireDelay,true,AutoFireDelay);
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


