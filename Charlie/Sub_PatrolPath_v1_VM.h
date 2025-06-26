// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sub_PatrolPath_v1_VM.generated.h"

UCLASS()
class SUBMERGED_API ASub_PatrolPath_v1_VM : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASub_PatrolPath_v1_VM();
	
	FVector GetPatrolPoint(int const index) const;
	int Num() const;
	
private:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (MakeEditWidget="true", AllowPrivateAccess = "true"))
    TArray<FVector> PatrolPoints;

};
