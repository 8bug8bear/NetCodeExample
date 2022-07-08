// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/NCEEquipmentComponent.h"
#include "Components/NCEHealthComponent.h"
#include "GameFramework/Character.h"
#include "NCECharacter.generated.h"

class USkeletalMeshComponent;
class UCameraComponent;

UCLASS()
class NETCODEEXAMPLE_API ANCECharacter : public ACharacter
{
	GENERATED_BODY()


	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh1P;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, Category = "EqipmantComponent")
	UNCEEquipmentComponent* EquipmentComponent;

	UPROPERTY(VisibleAnywhere, Category = "HealthComponent")
	UNCEHealthComponent* HealthComponent;
	
	float ForwardAxis = 0.0f;
	
	float RightAxis = 0.0f;

public:
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate = 45.f;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate = 45.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Sprint")
	float MaxSprintSpeed = 1000.f;

	float WalkSpeed;

	UPROPERTY(Replicated)
	bool bIsSprinting = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Scope")
	float ScopeFieldAngle  = 45.f;

	float DefaultScopeFieldAngle; 

protected:
	virtual void BeginPlay() override;

	void StartSprinting();

	UFUNCTION(Server, Unreliable)
	void Server_StartSprinting();

	void StopSprinting();

	UFUNCTION(Server, Unreliable)
	void Server_StopSprinting();
	
	void UpdateSprinting();

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);
	
	void FireWeapon();

	void StopFireWeapon();;

	void ScopeWeapon();

	void StopScopeWeapon();
	
	void TurnAtRate(float Rate);
	
	void LookUpAtRate(float Rate);
	
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

public:
	ANCECharacter();

	UCameraComponent* GetCameraComponent() const {return CameraComponent;}

	USkeletalMeshComponent* GetVisibleMesh()const;

	UFUNCTION(BlueprintCallable)
	UNCEHealthComponent* GetHealthComponent() const {return HealthComponent; }

	UFUNCTION(BlueprintCallable)
	UNCEEquipmentComponent* GetEquipmentComponent() const {return EquipmentComponent; }
	
	virtual void Tick(float DeltaTime) override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void OnDeath();
};
