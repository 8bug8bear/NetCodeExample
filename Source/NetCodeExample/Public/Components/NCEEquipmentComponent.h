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
	UPROPERTY()
	ANCEBaseWeapon* EquipWeapon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Loadout ")
	TSubclassOf<ANCEBaseWeapon> LoadoutWeapon;

	TWeakObjectPtr<class ANCECharacter> CachedCharacterOwner;
	
	// Called when the game starts
	virtual void BeginPlay() override;

	void CreateLodout();

public:	
	UNCEEquipmentComponent();

	ANCEBaseWeapon* GetEquippedWeapon()const {return EquipWeapon;}
};
