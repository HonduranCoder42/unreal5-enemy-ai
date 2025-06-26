// Fill out your copyright notice in the Description page of Project Settings.

/*
 * @file Sub_Charlie_v1_VM.cpp
 *
 * @brief Provides code to properly set up Charlie by assigning the proper variables.
 *
 *  This file includes functions for properly setting up the Charlie NPC object.
 *  It does this by:
 *  Assigning a Sub variable
 *  Assigning a Behavior Tree variable
 *  Assigning a Patrol Path variable
 *  
 *  @author Victor Mondragon
 *  @date 2025-02-04
 **/

#include "Sub_Charlie_v1_VM.h"

#include "Sub_Submarine_v1_VM.h"
#include "VectorUtil.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ASub_Charlie_v1_VM::ASub_Charlie_v1_VM()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}


ASub_Submarine_v1_VM* ASub_Charlie_v1_VM::GetSub()
{
	return Sub;
}


// Called when the game starts or when spawned
void ASub_Charlie_v1_VM::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void ASub_Charlie_v1_VM::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


// Called to bind functionality to input
void ASub_Charlie_v1_VM::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


UBehaviorTree* ASub_Charlie_v1_VM::GetBehaviorTree() const
{
	return Tree;
}


ASub_PatrolPath_v1_VM* ASub_Charlie_v1_VM::GetPatrolPath() const
{
	return PatrolPath;
}


ASub_AttackPath_v1_VM* ASub_Charlie_v1_VM::GetAttackPath() const
{
	return AttackPath;
}


int ASub_Charlie_v1_VM::FindClosestAttackPoint()
{
	FVector CharlieLocation = this->GetActorLocation();
	int ClosestIndex = 0;
	float MinDistance = FVector::Dist(AttackPath->GetAttackPoint(0), CharlieLocation);
	
	UE_LOG(LogTemp, Warning, TEXT("Beginning FindClosestAttackPoint!"));
	
	for (int i = 1; i < AttackPath->Num(); ++i)
	{
		float CurrentDistance = FVector::Dist(AttackPath->GetAttackPoint(i), CharlieLocation);
	    UE_LOG(LogTemp, Warning, TEXT("Current Distance: %f"), CurrentDistance);
		
		if (CurrentDistance < MinDistance)
		{
			MinDistance = CurrentDistance;

			ClosestIndex = i;
		}
	}

    UE_LOG(LogTemp, Warning, TEXT("Closest Index: %i"), ClosestIndex);
	return ClosestIndex;
}