// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/NCEGameMode.h"

#include "Core/NCEGameState.h"
#include "Core/NCEPlayerController.h"
#include "Core/NCEPlayerState.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

class ANCEGameState;
class ANCEPlayerState;

void ANCEGameMode::RestartPlayer(AController* NewPlayer)
{
	if(!bIsStaticSpawnPoints)
	{
		NewPlayer->StartSpot = nullptr;
	}

	if(MatchState != MatchState::InProgress)
	{
		return;
	}
	
	Super::RestartPlayer(NewPlayer);
}

void ANCEGameMode::EndMatch()
{
	if (!IsMatchInProgress())
	{
		return;
	}
	
	for (const APlayerState* PlayerState : GameState->PlayerArray)
	{
		if (APlayerController* PC = PlayerState->GetPlayerController())
		{
			//SetPause(PC);
			ANCEPlayerController* GameplayEPlayerController = Cast<ANCEPlayerController>(PC);
			if (IsValid(GameplayEPlayerController))
			{
				GameplayEPlayerController->Client_OnMatchIsOver();
			}
		}
	}
	
	Super::EndMatch();
}

ANCEGameMode::ANCEGameMode(): Super(){}

void ANCEGameMode::ReportDeathOfPlayer(const AController* Killer, AActor* Weapon, ACharacter* Killed)
{
	if(!IsValid(Killed)) // We are finishing the function, because no one was killed
	{
		return;
	}

	// We destroy the killed pawn, fill in the death statistics, respawn the pawn
	AController* PlayerController = Killed->GetController();
	Killed->Destroy();
	if(IsValid(PlayerController))
	{
		RestartPlayer(PlayerController);
		
		ANCEPlayerState* KilledPlayerState = PlayerController->GetPlayerState<ANCEPlayerState>();
		if(KilledPlayerState)
		{
			KilledPlayerState->AddDeath();
		}
	}

	if(!IsValid(Killer))
	{
		return;
	}

	// Filling out the statistics of kills
	ANCEPlayerState* KillerPlayerState = Killer->GetPlayerState<ANCEPlayerState>();
	if(IsValid(KillerPlayerState))
	{
		KillerPlayerState->AddKill();
	}
}

void ANCEGameMode::BeginPlay()
{
	Super::BeginPlay();

	ANCEGameState* LocalGameState = GetGameState<ANCEGameState>();
	if(LocalGameState )
	{
		LocalGameState->SetMaxGameSessionTime(MaxGameSessionTime);
		LocalGameState->OnGameTimeIsOverDelegate.BindUObject(this, &ANCEGameMode::EndMatch);
	}
	FTimerHandle LocalTimerHandle;
	GetWorldTimerManager().SetTimer(LocalTimerHandle, this, &ANCEGameMode::StartMatch, 1.0f, false);
}
