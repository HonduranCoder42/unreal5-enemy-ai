// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "DN_GameMode_v1_VM.h"
#include "SubRoomObject.h"
#include "Sub_Charlie_v1_VM.h"
#include "Sub_CharlieAIController_v1_VM.generated.h"

/**
 * 
 */ 
UCLASS()
class SUBMERGED_API ASub_CharlieAIController_v1_VM : public AAIController
{
	GENERATED_BODY()
	
public:

	FTimerHandle DetectTimerHandle;
	FTimerHandle PauseTimerHandle;
	bool CharlieDistracted = false;
	ASub_Submarine_v1_VM* SubmarineObj;
	ASub_Charlie_v1_VM* CharlieObj;
	float DamageDealt;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timer")
	bool SenseSub;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timer")
	float CharliePatrolTimer;
	
	
	explicit ASub_CharlieAIController_v1_VM(FObjectInitializer const& ObjectInitializer);

	
	UFUNCTION(BlueprintCallable)
	void StartCharlie();
	

    UFUNCTION()
    void BeginPatrolTimer();

	UFUNCTION()
	void PausePatrolTimer();

	UFUNCTION(BlueprintCallable)
	void PauseResumeTimer();

	UFUNCTION()
	void ChangeDetect();

	UFUNCTION()
	void AttackSub();

	UFUNCTION()
	void PassSub();
	
	UFUNCTION()
	void MoveToSub(ASub_Submarine_v1_VM* TargetSub);

	UFUNCTION()
	void MoveOverSub(ASub_Submarine_v1_VM* TargetSub);
	
	UPROPERTY()
	TArray<ASubRoomObject*> SubRooms;

protected:
	virtual void OnPossess(APawn* InPawn) override;

private:
	UFUNCTION()
	void OnTargetDetected();

};

