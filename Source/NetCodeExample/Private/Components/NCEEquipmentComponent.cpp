// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/NCEEquipmentComponent.h"
#include "Character/NCECharacter.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UNCEEquipmentComponent::UNCEEquipmentComponent(){}

void UNCEEquipmentComponent::DestroyAllWeapon()
{
	if(GetWorld()->IsServer())
	{
		EquipWeapon->Destroy();
	}
}

void UNCEEquipmentComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UNCEEquipmentComponent, EquipWeapon);
	DOREPLIFETIME(UNCEEquipmentComponent,CachedCharacterOwner);
}

// Called when the game starts
void UNCEEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();
	
	if(GetWorld()->IsServer())
	{
		checkf(GetOwner()->IsA<ANCECharacter>(),TEXT("UNCEEquipmentComponent::BeginPlay() can de used only with NCECharacter"));
		CachedCharacterOwner = StaticCast<ANCECharacter*>(GetOwner());
		CreateLodout();
	}
}

void UNCEEquipmentComponent::CreateLodout()
{
	if(!IsValid(LoadoutWeapon))
	{
		return;
	}
	if(GetWorld()->IsServer())
	{
		FActorSpawnParameters WeaponSpanwParameters = FActorSpawnParameters();;
		WeaponSpanwParameters.Owner = GetOwner();
		WeaponSpanwParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		EquipWeapon = GetWorld()->SpawnActor<ANCEBaseWeapon>(LoadoutWeapon,WeaponSpanwParameters);
		EquipWeapon->AttachToActor(CachedCharacterOwner,FAttachmentTransformRules::KeepRelativeTransform);
	}
}

void UNCEEquipmentComponent::OnRep_EquipWeapon()
{
	if(GetWorld()->IsServer())
	{
		return;
	}

	if(IsValid(EquipWeapon) && CachedCharacterOwner)
	{
		FAttachmentTransformRules transformRules(EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, true);
		EquipWeapon->AttachToComponent(CachedCharacterOwner->GetVisibleMesh(),transformRules,EquipWeapon->GetAttachSktName());

	}
}






