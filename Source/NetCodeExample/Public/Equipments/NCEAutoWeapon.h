// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Equipments/NCEBaseWeapon.h"
#include "NCEAutoWeapon.generated.h"

/**
 * 
 */
UCLASS()
class NETCODEEXAMPLE_API ANCEAutoWeapon : public ANCEBaseWeapon
{
	GENERATED_BODY()

	
protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Fire")
	float FireRate = 600.f;

	float AutoFireDelay;

	FTimerHandle AutoFireTimerHandle;

	virtual void BeginPlay() override;
public:
	ANCEAutoWeapon();

	virtual void Fire() override;

	void Shot();

	virtual void StopFire() override;
};
