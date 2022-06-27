// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NCEHealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NETCODEEXAMPLE_API UNCEHealthComponent : public UActorComponent
{
	GENERATED_BODY()


protected:
	bool bISDeath = false;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Health", meta=(ClampMin=0.f,UIMin=0.f))
	float MaxHealth = 100.f;

	float Health;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Health", meta=(ClampMin=1.f,UIMin=1.f))
	float HealDelay = 5.f;

	TWeakObjectPtr<class ANCECharacter> CachedCharacterOwner;

	FTimerHandle HealTimerHandle;

	UFUNCTION()
	void Heal();
	
	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
	
	virtual void BeginPlay() override;

public:	
	UNCEHealthComponent();
};
