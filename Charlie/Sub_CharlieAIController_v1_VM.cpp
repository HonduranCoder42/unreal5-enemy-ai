// Fill out your copyright notice in the Description page of Project Settings.

/*
 * @file Sub_CharlieAIController_v1_VM.cpp
 *
 * @brief Provides code to properly set up and control Charlie's AI
 *
 *  This file includes functions for properly setting up and assigning the appropriate variables for Charlie.
 *  It assigns all of the necessary variables for Charlie, such as the sub object in the level, whether or
 *  not he can detect the sub, how much damage he can deal, etc. It also contains all of the logic for the
 *  different actions Charlie can take, such as moving, attacking, detecting the sub, etc. 
 *
 *  @author Victor Mondragon
 *  @date 2025-02-04
 **/
 
#include "Sub_CharlieAIController_v1_VM.h"

#include "NavigationSystem.h"
#include "Sub_Charlie_v1_VM.h"
#include "Sub_Submarine_v1_VM.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AIPerceptionComponent.h"

ASub_CharlieAIController_v1_VM::ASub_CharlieAIController_v1_VM(FObjectInitializer const& ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	SenseSub = false;
	DamageDealt  = 25.0f;

	TArray<AActor*> Subs;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASub_Submarine_v1_VM::StaticClass(), Subs);
	TArray<AActor*> Charlies;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASub_Charlie_v1_VM::StaticClass(), Charlies);
    // Iterate through all ASubRoomObject instances in the world
    SubRooms.Empty();
    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASubRoomObject::StaticClass(), FoundActors);
    
    // Add each found ASubRoomObject to the SubRooms array
    for (AActor* Actor : FoundActors)
    {
        ASubRoomObject* SubRoom = Cast<ASubRoomObject>(Actor);
        if (SubRoom)
        {
            SubRooms.Add(SubRoom);
        }
    }
    
    UE_LOG(LogTemp, Log, TEXT("Found %d SubRoom objects in the scene."), SubRooms.Num());

    
	for (AActor* Actor : Subs)
	{
		if (ASub_Submarine_v1_VM* MySub = Cast<ASub_Submarine_v1_VM>(Actor))
		{
			SubmarineObj = MySub;
			UE_LOG(LogTemp, Warning, TEXT("Sub Successfully Assigned"));
			break;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Sub Not Found"));
		}
	}

	for (AActor* Actor : Charlies)
	{
		if (ASub_Charlie_v1_VM* MyCharlie = Cast<ASub_Charlie_v1_VM>(Actor))
		{
			CharlieObj = MyCharlie;
			UE_LOG(LogTemp, Warning, TEXT("Charlie Successfully Assigned"));
			break;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Charlie Not Found"));
		}
	}
}


void ASub_CharlieAIController_v1_VM::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	/*
	if(ASub_Charlie_v1_VM* const npc = Cast<ASub_Charlie_v1_VM>(InPawn))
	{
		if (UBehaviorTree* const tree = npc->GetBehaviorTree())
		{
			UBlackboardComponent* b;
			UseBlackboard(tree->BlackboardAsset, b);
			Blackboard = b;
			RunBehaviorTree(tree);
		}
		CharliePatrolTimer = npc->PatrolTimer;
	}
	BeginPatrolTimer(s); */
}


void ASub_CharlieAIController_v1_VM::StartCharlie()
{
	if (ASub_Charlie_v1_VM* const npc = CharlieObj)
	{
		if(UBehaviorTree* const tree = CharlieObj->GetBehaviorTree())
		{
			UBlackboardComponent* b;
			UseBlackboard(tree->BlackboardAsset, b);
			Blackboard = b;
			RunBehaviorTree(tree);
		}
		CharliePatrolTimer = npc->PatrolTimer;
	}
	BeginPatrolTimer();
}


void ASub_CharlieAIController_v1_VM::BeginPatrolTimer() 
{
	GetWorldTimerManager().SetTimer(DetectTimerHandle, this, &ASub_CharlieAIController_v1_VM::ChangeDetect, CharliePatrolTimer, false);
	UE_LOG(LogTemp, Warning, TEXT("Timer Started"));

}

void ASub_CharlieAIController_v1_VM::PausePatrolTimer()
{
	GetWorldTimerManager().SetTimer(PauseTimerHandle, this, &ASub_CharlieAIController_v1_VM::PauseResumeTimer, 20.0f, false);
	UE_LOG(LogTemp, Warning, TEXT("Timer Paused"));
}

void ASub_CharlieAIController_v1_VM::PauseResumeTimer()
{
	if (DetectTimerHandle.IsValid())
	{
		if (CharlieDistracted)
		{
			GetWorldTimerManager().UnPauseTimer(DetectTimerHandle);
			CharlieDistracted = false;
			UE_LOG(LogTemp, Warning, TEXT("Timer Resumed"));
		}
		else
		{
			GetWorldTimerManager().PauseTimer(DetectTimerHandle);
			CharlieDistracted = true;
			PausePatrolTimer();
		}
	}
}


void ASub_CharlieAIController_v1_VM::ChangeDetect()
{
	UE_LOG(LogTemp, Warning, TEXT("Timer Finished!"));
	SenseSub = !SenseSub;
	UE_LOG(LogTemp, Warning, TEXT("SenseSub changed to %s"), SenseSub ? TEXT("true") : TEXT("false"));
	OnTargetDetected();
}


void ASub_CharlieAIController_v1_VM::OnTargetDetected()
{
	UE_LOG(LogTemp, Warning, TEXT("OnTargetDetected Ran"));
	if (SenseSub == true)
	{ 
		/*	int32 RandomValue = FMath::RandRange(0, 10);
			UE_LOG(LogTemp, Warning, TEXT("RandomValue == %d"), RandomValue);
			
			GetBlackboardComponent()->SetValueAsBool("SubDetected", true);
			if (RandomValue % 2 == 0)
			{
				UE_LOG(LogTemp, Warning, TEXT("AttackSub Selected!"));
				MoveToSub(SubmarineObj);
			}
			else if (RandomValue % 2 == 1)
			{
				UE_LOG(LogTemp, Warning, TEXT("PassSub Selected!"));
				MoveOverSub(SubmarineObj);
			} */
		UE_LOG(LogTemp, Warning, TEXT("SenseSub is TRUE"));
		GetBlackboardComponent()->SetValueAsBool("SubDetected", true);
		//GetWorldTimerManager().SetTimer(DetectTimerHandle, this, &ASub_CharlieAIController_v1_VM::AttackSub, 7.0f, false);
		AttackSub();
	}
	else
	{
		GetBlackboardComponent()->SetValueAsBool("SubDetected", false);
	}
}


void ASub_CharlieAIController_v1_VM::AttackSub()
{
   bool selectedRoom = false;
	bool skipRoom = false;
	int iterativeCheck = 0;
	for(int i = 0; i < SubRooms.Num() -1; i++)
	{
		if(SubRooms[i]->hasBeenAttacked == true)
		{
			iterativeCheck++;
		}
	}

	if(iterativeCheck == SubRooms.Num())
	{
		skipRoom = true;
	}
	
	if(skipRoom == false)
	{
		while(!selectedRoom){
			int randNum = FMath::RandRange(0, SubRooms.Num() - 1);
    	
			if(SubRooms[randNum]->hasBeenAttacked == true){
				selectedRoom = false;
			}else if(SubRooms[randNum]->hasBeenAttacked == false){
				SubRooms[randNum]->onAttackCalled();
				selectedRoom = true;
			}
		}
	}

    
    
	UE_LOG(LogTemp, Warning, TEXT("Damage Dealt!"));
	SubmarineObj->DamageSub(DamageDealt);
	SubmarineObj->playCharlieDamageSound();
	UE_LOG(LogTemp, Warning, TEXT("Timer Finished!"));
	SenseSub = !SenseSub;
	UE_LOG(LogTemp, Warning, TEXT("SenseSub changed to %s"), SenseSub ? TEXT("true") : TEXT("false"));
	OnTargetDetected();
	BeginPatrolTimer();
}


void ASub_CharlieAIController_v1_VM::PassSub()
{
	UE_LOG(LogTemp, Warning, TEXT("Sub Passed!"));
	UE_LOG(LogTemp, Warning, TEXT("Timer Finished!"));
	SenseSub = !SenseSub;
	UE_LOG(LogTemp, Warning, TEXT("SenseSub changed to %s"), SenseSub ? TEXT("true") : TEXT("false"));
	OnTargetDetected();
	BeginPatrolTimer();
}


void ASub_CharlieAIController_v1_VM::MoveToSub(ASub_Submarine_v1_VM* TargetSub)
{
	if (TargetSub == nullptr)
	{
		return;
	}

	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn == nullptr)
	{
		return;
	}

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	if (NavSystem == nullptr)
	{
		return;
	}

	FNavLocation Destination;
	if (NavSystem->GetRandomPointInNavigableRadius(TargetSub->GetActorLocation(), 100.f, Destination))
	{
		MoveToLocation(Destination.Location, 50.f, true, true, false, false);
		GetWorldTimerManager().SetTimer(DetectTimerHandle, this, &ASub_CharlieAIController_v1_VM::AttackSub, 22.0f, false);
	}
	
}


void ASub_CharlieAIController_v1_VM::MoveOverSub(ASub_Submarine_v1_VM* TargetSub)
{
	if (TargetSub == nullptr)
	{
		return;
	}

	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn == nullptr)
	{
		return;
	}

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	if (NavSystem == nullptr)
	{
		return;
	}

	FNavLocation Destination;
	if (NavSystem->GetRandomPointInNavigableRadius(TargetSub->GetActorLocation(), 100.f, Destination))
	{
		MoveToLocation(Destination.Location, 50.f, false, true, false, false);
		GetWorldTimerManager().SetTimer(DetectTimerHandle, this, &ASub_CharlieAIController_v1_VM::PassSub, 22.0f, false);
	}
}


