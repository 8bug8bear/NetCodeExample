// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/NCECharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ANCECharacter::ANCECharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	CameraComponent->SetupAttachment(GetCapsuleComponent());
	CameraComponent->bUsePawnControlRotation = true;

	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(CameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	
	EquipmentComponent = CreateDefaultSubobject<UNCEEquipmentComponent>(TEXT("EquipmentComponent"));

	HealthComponent = CreateDefaultSubobject<UNCEHealthComponent>(TEXT("HealthComponent"));
}

// Called when the game starts or when spawned
void ANCECharacter::BeginPlay()
{
	Super::BeginPlay();

	Mesh1P->SetHiddenInGame(false, true);
	
	WalkSpeed = GetCharacterMovement()->MaxWalkSpeed;

	DefaultScopeFieldAngle = CameraComponent->FieldOfView;
}

void ANCECharacter::StartSprinting()
{
	if(bIsSprinting)
	{
		return;
	}

	StopFireWeapon();
	StopScopeWeapon();
	bIsSprinting = true;
	GetCharacterMovement()->MaxWalkSpeed = MaxSprintSpeed;
}

void ANCECharacter::StopSprinting()
{
	if(!bIsSprinting)
	{
		return;
	}

	bIsSprinting = false;

	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void ANCECharacter::UpdateSprinting()
{
	if(RightAxis != 0.f)
	{
		StopSprinting();
		return;
	}

	if(ForwardAxis < 0.5f)
	{
		StopSprinting();
		return;
	}
}

void ANCECharacter::MoveForward(float Value)
{
	ForwardAxis = Value;
	if (Value != 0.0f)
	{
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void ANCECharacter::MoveRight(float Value)
{
	RightAxis = Value;
	if (Value != 0.0f)
	{
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void ANCECharacter::FireWeapon()
{
	if(!bIsSprinting)
	{
		EquipmentComponent->GetEquippedWeapon()->Fire();
	}
}

void ANCECharacter::StopFireWeapon()
{
	EquipmentComponent->GetEquippedWeapon()->StopFire();
}

void ANCECharacter::ScopeWeapon()
{
	if(EquipmentComponent->GetEquippedWeapon()->GetCanAim() && !bIsSprinting)
	{
		CameraComponent->FieldOfView = ScopeFieldAngle;
	}
}

void ANCECharacter::StopScopeWeapon()
{
	if(EquipmentComponent->GetEquippedWeapon()->GetCanAim())
	{
		CameraComponent->FieldOfView = DefaultScopeFieldAngle;
	}
}

void ANCECharacter::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ANCECharacter::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}



USkeletalMeshComponent* ANCECharacter::GetMesh() const
{
	if(IsLocallyControlled())
	{
		return Mesh1P;
	}
	
	return GetMesh();
}

// Called every frame
void ANCECharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(bIsSprinting)
	{
		UpdateSprinting();
	}
}

// Called to bind functionality to input
void ANCECharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ANCECharacter::StartSprinting);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ANCECharacter::StopSprinting);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ANCECharacter::FireWeapon);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &ANCECharacter::StopFireWeapon);

	PlayerInputComponent->BindAction("Scope", IE_Pressed, this, &ANCECharacter::ScopeWeapon);
	PlayerInputComponent->BindAction("Scope", IE_Released, this, &ANCECharacter::StopScopeWeapon);

	PlayerInputComponent->BindAxis("MoveForward", this, &ANCECharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ANCECharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ANCECharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ANCECharacter::LookUpAtRate);
}

