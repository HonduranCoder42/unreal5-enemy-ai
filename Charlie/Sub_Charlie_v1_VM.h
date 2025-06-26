// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Sub_PatrolPath_v1_VM.h"
#include "Sub_Submarine_v1_VM.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameFramework/Character.h"
#include "Sub_AttackPath_v1_VM.h"
#include "Sub_Charlie_v1_VM.generated.h"

UCLASS()
class SUBMERGED_API ASub_Charlie_v1_VM : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASub_Charlie_v1_VM();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
	ASub_Submarine_v1_VM* Sub;

	UPROPERTY(EditAnywhere)
	float PatrolTimer = 30.0f;
	
	UFUNCTION(BlueprintCallable)
	ASub_Submarine_v1_VM* GetSub();

	UBehaviorTree* GetBehaviorTree() const;
	
	ASub_PatrolPath_v1_VM* GetPatrolPath() const;
	ASub_AttackPath_v1_VM* GetAttackPath() const;

	int FindClosestAttackPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta=(AllowPrivateAccess=true))
	UBehaviorTree* Tree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta=(AllowPrivateAccess=true))
	ASub_PatrolPath_v1_VM* PatrolPath;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta=(AllowPrivateAccess=true))
	ASub_AttackPath_v1_VM* AttackPath;

};