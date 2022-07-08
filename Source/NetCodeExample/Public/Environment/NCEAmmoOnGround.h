// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NCEAmmoOnGround.generated.h"

UCLASS()
class NETCODEEXAMPLE_API ANCEAmmoOnGround : public AActor
{
	GENERATED_BODY()
	

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="CollisionBox")
	class UBoxComponent* CollisionBox;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="CollisionBox")
	UStaticMeshComponent* AmmoMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="")
	int32 StoredAmmo = 30;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="")
	float RecoveryTime = 5.f;

	UPROPERTY(ReplicatedUsing = OnRep_bISActive)
	bool bISActive = true;
	
	FTimerHandle RecoveryAmmoTimerHandle;

	UFUNCTION()
	void RecoveryAmmo();
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnRep_bISActive();

public:	
	// Sets default values for this actor's properties
	ANCEAmmoOnGround();

	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
