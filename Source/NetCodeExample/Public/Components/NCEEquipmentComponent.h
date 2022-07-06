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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Loadout ")
	TSubclassOf<ANCEBaseWeapon> LoadoutWeapon;

	UPROPERTY(Replicated)
	ANCECharacter* CachedCharacterOwner;
	
	// Called when the game starts
	virtual void BeginPlay() override;

	void CreateLodout();

	UFUNCTION()
	void OnRep_EquipWeapon();
	
public:	
	UNCEEquipmentComponent();

	ANCEBaseWeapon* GetEquippedWeapon()const {return EquipWeapon;}

	void DestroyAllWeapon();

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
