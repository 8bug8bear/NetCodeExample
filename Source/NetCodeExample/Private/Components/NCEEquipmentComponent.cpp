// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/NCEEquipmentComponent.h"
#include "Character/NCECharacter.h"

// Sets default values for this component's properties
UNCEEquipmentComponent::UNCEEquipmentComponent(){}


// Called when the game starts
void UNCEEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();

	checkf(GetOwner()->IsA<ANCECharacter>(),TEXT("UNCEEquipmentComponent::BeginPlay() can de used only with NCECharacter"));
	CachedCharacterOwner = StaticCast<ANCECharacter*>(GetOwner());
	CreateLodout();
}

void UNCEEquipmentComponent::CreateLodout()
{
	if(!IsValid(LoadoutWeapon))
	{
		return;
	}

	FActorSpawnParameters WeaponSpanwParameters = FActorSpawnParameters();;
	WeaponSpanwParameters.Owner = GetOwner();
	EquipWeapon = GetWorld()->SpawnActor<ANCEBaseWeapon>(LoadoutWeapon,WeaponSpanwParameters);
	//EquipWeapon->SetOwner(GetOwner());
	EquipWeapon->AttachToComponent(CachedCharacterOwner->GetMesh(),FAttachmentTransformRules::SnapToTargetNotIncludingScale,EquipWeapon->GetAttachSktName());

}



