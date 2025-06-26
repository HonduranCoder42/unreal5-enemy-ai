// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SubmergedGameMode.h"
#include "SubmergedGameState.h"
#include "Sub_CharlieAIController_v1_VM.h"
#include "GameFramework/Actor.h"
#include "Sub_Charlie_v1_VM.h"
#include "TimerManager.h"
#include "DN_AIDirector_v1_VM.generated.h"

UCLASS()
class SUBMERGED_API ADN_AIDirector_v1_VM : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADN_AIDirector_v1_VM();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	float MaxStimulusTime_Patrol = 60.0f;
	float UpdateDifficultyInterval = 30.0f;
	int CurrentDifficulty = 1;
	int TimeDifficulty = 1;

	FTimerHandle UpdateTimerHandle;
	FTimerHandle UpdateTimeDifficultyHandle;
	TArray<ASubRoomObject*> RoomObjects;
	ASub_Charlie_v1_VM* Charlie;
	ASub_CharlieAIController_v1_VM* CharlieController;

public:	

	UFUNCTION()
	void AssignRoomObjects();
	
	UFUNCTION()
	void AssignCharlie();

	UFUNCTION()
	void AssignCharlieController();

	UFUNCTION()
	void BeginUpdateTimer();

	UFUNCTION()
	void BeginTimeDifficultyTimer();

	UFUNCTION(BlueprintCallable)
	void StartDirector();
	
	UFUNCTION()
	int GetCurrentRoomDifficulty();

/*	UFUNCTION()
	int GetCurrentIntegrityDifficulty();*/

	UFUNCTION()
	void UpdateTimeDifficulty();
	
	UFUNCTION()
	void AdjustDifficulty();
	
	UFUNCTION()
	void AdjustValues();

	UFUNCTION()
	void UpdateDifficulty();

};
