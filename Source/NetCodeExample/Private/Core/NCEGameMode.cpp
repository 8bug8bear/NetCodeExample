// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/NCEGameMode.h"
#include "GameFramework/Character.h"

void ANCEGameMode::RestartPlayer(AController* NewPlayer)
{
	Super::RestartPlayer(NewPlayer);
}

ANCEGameMode::ANCEGameMode(): Super(){}

void ANCEGameMode::PlayerDied(ACharacter* Character)
{
	AController* PlayerController = Character->GetController();
	Character->Destroy();
	RestartPlayer(PlayerController);
}
