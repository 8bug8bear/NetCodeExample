// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BarrelComponent.h"
#include "GameFramework/Actor.h"
#include "NCEBaseWeapon.generated.h"

UCLASS()
class NETCODEEXAMPLE_API ANCEBaseWeapon : public AActor
{
	GENERATED_BODY()


protected:
	UPROPERTY(VisibleDefaultsOnly, Category="WeaponMesh")
	USkeletalMeshComponent* WeaponMesh;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="UsingWeapon", meta=(ClampMin=1.f,UIMin=1.f))
	float DelayedReuse = 0.3f;

	bool bCanUse = true;

	FTimerHandle DelayedReuseTimerHandle;

	// The name of the socket to which this weapon should be attached
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="SocketName")
	FName AttachSktName;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="SocketName")
	FName MuzzelSktName;

	UPROPERTY(VisibleDefaultsOnly,BlueprintReadOnly, Category="WeaponComponents")
	UBarrelComponent* Barrel;

	// AnimMontage played by the owner when attacking with this weapon
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="VisualEffects")
	UAnimMontage* FireAnimMontage;

	TWeakObjectPtr<class ANCECharacter> CachedCharacterOwner;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category="VisualEffects")
	bool bCanAim = true;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Fire")
	float Damage = 40.f;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetUseDelay();

	UFUNCTION()
	void SetCanUseToTrue(){bCanUse = true;}
	
public:
	// Sets default values for this actor's properties
	ANCEBaseWeapon();

	FName GetAttachSktName() const {return AttachSktName;}

	virtual void Fire();

	virtual void StopFire();

	bool GetCanAim()const{return bCanAim;}
};
