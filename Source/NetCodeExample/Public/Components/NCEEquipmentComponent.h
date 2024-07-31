// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Equipments/NCEBaseWeapon.h"
#include "NCEEquipmentComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NETCODEEXAMPLE_API UNCEEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(ReplicatedUsing=OnRep_EquipWeapon)
	ANCEBaseWeapon* EquipWeapon;

	UPROPERTY(Replicated)
	ANCEBaseWeapon* FirstWeaponPtr;

	UPROPERTY(Replicated)
	ANCEBaseWeapon* SecondWeaponPtr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Loadout ")
	TSubclassOf<ANCEBaseWeapon> FirstLoadoutWeaponClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Loadout ")
	TSubclassOf<ANCEBaseWeapon> SecondLoadoutWeaponClass;

	UPROPERTY(Replicated)
	ANCECharacter* CachedCharacterOwner;
	
	// Called when the game starts
	virtual void BeginPlay() override;

	void CreateLoadout();

	UFUNCTION()
	void OnRep_EquipWeapon();
	
public:
	UNCEEquipmentComponent();

	ANCEBaseWeapon* GetEquippedWeapon()const {return EquipWeapon;}

	UFUNCTION(Server,Unreliable)
	void Server_EquipFirstWeapon();

	UFUNCTION(Server,Unreliable)
	void Server_EquipSecondWeapon();

	void DestroyAllWeapon();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable)
	int32 GetNumberAmmoEquipWeapon();

	UFUNCTION(BlueprintCallable)
	void AddAmmoToEquipWeapon(int32 AdditionalAmmo);
	
};
