// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/NCEHealthComponent.h"
#include "Character/NCECharacter.h"
#include "Core/NCEGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UNCEHealthComponent::UNCEHealthComponent(){}

void UNCEHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UNCEHealthComponent,Health)
	DOREPLIFETIME(UNCEHealthComponent,CachedCharacterOwner)
}


void UNCEHealthComponent::Heal()
{
	Health = MaxHealth;
}

void UNCEHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if(bISDeath)
	{
		return;
	}
	GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
	
	Health -= Damage;
	
	if(Health<=0.f)
	{
		Health=0.f;
		bISDeath = true;
		
		ANCEGameMode* GameMode = Cast<ANCEGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		if(GameMode)
		{
			CachedCharacterOwner->OnDeath();
			GameMode->PlayerDied(CachedCharacterOwner);
		}
		
		return;
	}
	GetWorld()->GetTimerManager().SetTimer(HealTimerHandle,this,&UNCEHealthComponent::Heal,HealDelay);
}

// Called when the game starts
void UNCEHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	if(GetWorld()->IsServer())
	{
		checkf(GetOwner()->IsA<ANCECharacter>(), TEXT("UNCEHealthComponent::BeginPlay can de used only with ANCECharacter"));
		CachedCharacterOwner = StaticCast<ANCECharacter*>(GetOwner());
		CachedCharacterOwner->OnTakeAnyDamage.AddDynamic(this,&UNCEHealthComponent::OnTakeAnyDamage);

		Health = MaxHealth;
	}
}


