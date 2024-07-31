// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/NCEEquipmentComponent.h"

#include "AudioMixerDevice.h"
#include "Character/NCECharacter.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UNCEEquipmentComponent::UNCEEquipmentComponent(){}

void UNCEEquipmentComponent::Server_EquipFirstWeapon_Implementation()
{
	if(GetWorld()->IsNetMode(NM_DedicatedServer) && IsValid(FirstWeaponPtr))
	{
		EquipWeapon = FirstWeaponPtr;
	}
}

void UNCEEquipmentComponent::Server_EquipSecondWeapon_Implementation()
{
	if(GetWorld()->IsNetMode(NM_DedicatedServer) && IsValid(SecondWeaponPtr))
	{
		EquipWeapon = SecondWeaponPtr;
	}
}

void UNCEEquipmentComponent::DestroyAllWeapon()
{
	if(GetWorld()->IsNetMode(NM_DedicatedServer))
	{
		EquipWeapon = nullptr;

		FirstWeaponPtr->Destroy();
		FirstWeaponPtr = nullptr;

		SecondWeaponPtr->Destroy();
		SecondWeaponPtr = nullptr;
	}
}

void UNCEEquipmentComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UNCEEquipmentComponent, EquipWeapon);
	DOREPLIFETIME(UNCEEquipmentComponent, FirstWeaponPtr)
	DOREPLIFETIME(UNCEEquipmentComponent, SecondWeaponPtr)
	DOREPLIFETIME(UNCEEquipmentComponent,CachedCharacterOwner);
}

int32 UNCEEquipmentComponent::GetNumberAmmoEquipWeapon()
{
	if(EquipWeapon)
	{
		return EquipWeapon->GetAmmo();
	}
	
	return -1;
}

void UNCEEquipmentComponent::AddAmmoToEquipWeapon(const int32 AdditionalAmmo)
{
	EquipWeapon->AddAmmo(AdditionalAmmo);
}

// Called when the game starts
void UNCEEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();
	
	if(GetWorld()->IsNetMode(NM_DedicatedServer))
	{
		checkf(GetOwner()->IsA<ANCECharacter>(),TEXT("UNCEEquipmentComponent::BeginPlay() can de used only with NCECharacter"));
		CachedCharacterOwner = StaticCast<ANCECharacter*>(GetOwner());
		CreateLoadout();
	}
}

void UNCEEquipmentComponent::CreateLoadout()
{
	if(!IsValid(FirstLoadoutWeaponClass) || !IsValid(SecondLoadoutWeaponClass) || !GetWorld()->IsNetMode(NM_DedicatedServer))
	{
		return;
	}
	
	FActorSpawnParameters WeaponSpawnParameters = FActorSpawnParameters();;
	WeaponSpawnParameters.Owner = GetOwner();
	WeaponSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	FirstWeaponPtr = GetWorld()->SpawnActor<ANCEBaseWeapon>(FirstLoadoutWeaponClass,WeaponSpawnParameters);
	FirstWeaponPtr->AttachToActor(CachedCharacterOwner, FAttachmentTransformRules::KeepRelativeTransform);

	SecondWeaponPtr = GetWorld()->SpawnActor<ANCEBaseWeapon>(SecondLoadoutWeaponClass,WeaponSpawnParameters);
	SecondWeaponPtr->AttachToActor(CachedCharacterOwner, FAttachmentTransformRules::KeepRelativeTransform);
	
	EquipWeapon = FirstWeaponPtr;
}

void UNCEEquipmentComponent::OnRep_EquipWeapon()
{
	if(GetWorld()->IsNetMode(NM_DedicatedServer))
	{
		return;
	}

	if(IsValid(EquipWeapon) && CachedCharacterOwner)
	{
		const FAttachmentTransformRules TransformRules(EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, true);
		EquipWeapon->AttachToComponent(CachedCharacterOwner->GetVisibleMesh(),TransformRules,EquipWeapon->GetAttachSktName());
		
		if(EquipWeapon != FirstWeaponPtr && IsValid(FirstWeaponPtr))
		{
			FirstWeaponPtr->AttachToComponent(CachedCharacterOwner->GetVisibleMesh(),TransformRules,FirstWeaponPtr->GetDetachSktName());
		}
		
		if(EquipWeapon != SecondWeaponPtr && IsValid(SecondWeaponPtr))
		{
			SecondWeaponPtr->AttachToComponent(CachedCharacterOwner->GetVisibleMesh(),TransformRules,SecondWeaponPtr->GetDetachSktName());
		}
	}
}






