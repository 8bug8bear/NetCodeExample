// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/BarrelComponent.h"
#include "Pluggable/Definitions.h"

// Sets default values for this component's properties
UBarrelComponent::UBarrelComponent(){}




void UBarrelComponent::SetDamageAmount(float NewDamage)
{
	if(NewDamage>1.f)
	{
		DamageAmount = NewDamage;
	}
}

void UBarrelComponent::Shoot(FVector Start, FVector Direction, AController* Controller, AActor* IgnoreActor)
{
	FVector ShootEnd = Direction*FireRange+Start;
	FHitResult ShootResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(IgnoreActor);
	if(GetWorld()->LineTraceSingleByChannel(ShootResult,Start,ShootEnd, COLLISION_WEAPON, Params))
	{
		ShootEnd = ShootResult.ImpactPoint;
		AActor* HitActor = ShootResult.GetActor();
		if(IsValid(HitActor))
		{
			HitActor->TakeDamage(DamageAmount,FDamageEvent{},Controller ,GetOwner());
		}
	}
}




