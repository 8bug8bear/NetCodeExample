// Fill out your copyright notice in the Description page of Project Settings.


#include "Environment/NCEAmmoOnGround.h"
#include "Character/NCECharacter.h"
#include "Components/BoxComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ANCEAmmoOnGround::ANCEAmmoOnGround()
{
 	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(RootComponent);

	AmmoMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AmmoMesh"));
	AmmoMesh->SetupAttachment(RootComponent);

	bReplicates = true;
}

void ANCEAmmoOnGround::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(!HasAuthority() || !bISActive)
	{
		return;
	}
	
	ANCECharacter* Character = Cast<ANCECharacter>(OtherActor);
	if(Character)
	{
		Character->GetEquipmentComponent()->AddAmmoEquipWeapon(StoredAmmo);
		bISActive = false;
		GetWorldTimerManager().SetTimer(RecoveryAmmoTimerHandle,this,&ANCEAmmoOnGround::RecoveryAmmo, RecoveryTime);
	}
}

void ANCEAmmoOnGround::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ANCEAmmoOnGround,bISActive);
}

void ANCEAmmoOnGround::RecoveryAmmo()
{
	bISActive = true;
}

// Called when the game starts or when spawned
void ANCEAmmoOnGround::BeginPlay()
{
	Super::BeginPlay();

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this,&ANCEAmmoOnGround::OnComponentBeginOverlap);
}

void ANCEAmmoOnGround::OnRep_bISActive()
{
	AmmoMesh->SetVisibility(bISActive);
}



