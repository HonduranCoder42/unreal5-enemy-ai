// Fill out your copyright notice in the Description page of Project Settings.


#include "DN_AIDirector_v1_VM.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
ADN_AIDirector_v1_VM::ADN_AIDirector_v1_VM()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADN_AIDirector_v1_VM::BeginPlay()
{
	Super::BeginPlay();
	AssignRoomObjects();
	AssignCharlie();
	AssignCharlieController();
}

void ADN_AIDirector_v1_VM::AssignRoomObjects()
{
	PrimaryActorTick.bCanEverTick = true;

	// Iterate through all ASubRoomObject instances in the world
	RoomObjects.Empty();
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASubRoomObject::StaticClass(), FoundActors);
    
	// Add each found ASubRoomObject to the SubRooms array
	for (AActor* Actor : FoundActors)
	{ 
		ASubRoomObject* SubRoom = Cast<ASubRoomObject>(Actor);
		if (SubRoom)
		{
			RoomObjects.Add(SubRoom);
		}
	}
    
	UE_LOG(LogTemp, Log, TEXT("Found %d SubRoom objects in the scene. (DIRECTOR)"), RoomObjects.Num()); 
}

void ADN_AIDirector_v1_VM::AssignCharlie()
{
	PrimaryActorTick.bCanEverTick = true;
	
	TArray<AActor*> Charlies;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASub_Charlie_v1_VM::StaticClass(), Charlies);
	TArray<AActor*> FoundActors;
    
	for (AActor* Actor : Charlies)
	{
		if (ASub_Charlie_v1_VM* MyCharlie = Cast<ASub_Charlie_v1_VM>(Actor))
		{
			Charlie = MyCharlie;
			UE_LOG(LogTemp, Warning, TEXT("Charlie Successfully Assigned (DIRECTOR)"));
			break;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Charlie Not Found (DIRECTOR)"));
		}
	}
}

void ADN_AIDirector_v1_VM::AssignCharlieController()
{
	PrimaryActorTick.bCanEverTick = true;
	
	TArray<AActor*> CharlieControllers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASub_CharlieAIController_v1_VM::StaticClass(), CharlieControllers);
	TArray<AActor*> FoundActors;
    
	for (AActor* Actor : CharlieControllers)
	{
		if (ASub_CharlieAIController_v1_VM* MyCharlieController = Cast<ASub_CharlieAIController_v1_VM>(Actor))
		{
			CharlieController = MyCharlieController;
			UE_LOG(LogTemp, Warning, TEXT("CharlieController Successfully Assigned (DIRECTOR)"));
			break;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("CharlieController Not Found (DIRECTOR)"));
		}
	}
}

void ADN_AIDirector_v1_VM::BeginUpdateTimer()
{
	GetWorldTimerManager().SetTimer(UpdateTimerHandle, this, &ADN_AIDirector_v1_VM::UpdateDifficulty, UpdateDifficultyInterval, false);
	UE_LOG(LogTemp, Warning, TEXT("UpdateDifficulty Timer Started (DIRECTOR)"));
}

void ADN_AIDirector_v1_VM::BeginTimeDifficultyTimer()
{
	GetWorldTimerManager().SetTimer(UpdateTimeDifficultyHandle, this, &ADN_AIDirector_v1_VM::UpdateTimeDifficulty, 120, false);
	UE_LOG(LogTemp, Warning, TEXT("UpdateTimeDifficulty Timer Started (DIRECTOR)"));

}

void ADN_AIDirector_v1_VM::StartDirector()
{
	BeginUpdateTimer();
	BeginTimeDifficultyTimer();
	UE_LOG(LogTemp, Warning, TEXT("Director Started (DIRECTOR)"));
}

int ADN_AIDirector_v1_VM::GetCurrentRoomDifficulty()
{
	int RoomDifficulty = 0;

	int NumDamagedRooms = 0;

	for (ASubRoomObject* SubRoom : RoomObjects)
	{
		if (SubRoom->hasBeenAttacked == true)
		{
			++NumDamagedRooms;
		}
	}

	if (NumDamagedRooms <= 1)
	{
		RoomDifficulty = 1;
	}
	else if (NumDamagedRooms == 2)
	{
		RoomDifficulty = 2;
	}
	else if (NumDamagedRooms == 3)
	{
		RoomDifficulty = 3;
	}
	else if (NumDamagedRooms == 4)
	{
		RoomDifficulty = 4;
	}
	else
	{
		RoomDifficulty = 5;
	}

    UE_LOG(LogTemp, Warning, TEXT("The current room difficulty is : %d (DIRECTOR)"), RoomDifficulty);
	return RoomDifficulty;
	
}

void ADN_AIDirector_v1_VM::UpdateTimeDifficulty()
{
	++TimeDifficulty;
	UE_LOG(LogTemp, Warning, TEXT("The current distance difficulty is : %d (DIRECTOR)"), TimeDifficulty);
	BeginTimeDifficultyTimer();
}

void ADN_AIDirector_v1_VM::AdjustDifficulty()
{
	CurrentDifficulty = 1;
	int RoomDiff = GetCurrentRoomDifficulty();
	if (RoomDiff == 1)
	{
		CurrentDifficulty = 5;
	}
	else if (RoomDiff == 2)
	{
		CurrentDifficulty = 4;
	}
	else if (RoomDiff == 3)
	{
		CurrentDifficulty = 3;
	}
	else if (RoomDiff == 4)
	{
		CurrentDifficulty = 2;
	}
	else
	{
		CurrentDifficulty = 1;
	}
	UE_LOG(LogTemp, Warning, TEXT("Room Difficulty: %d"), RoomDiff);
	UE_LOG(LogTemp, Warning, TEXT("The current difficulty is: %d (DIRECTOR)"), CurrentDifficulty);

}

void ADN_AIDirector_v1_VM::AdjustValues()
{
	switch(CurrentDifficulty)
	{
		case 1:
			CharlieController->CharliePatrolTimer = 50.0;
			break; 
		case 2:
			CharlieController->CharliePatrolTimer = 42.5;
			break;
		case 3:
			CharlieController->CharliePatrolTimer = 35.0;
			break;
		case 4:
			CharlieController->CharliePatrolTimer = 27.5;
			break;
		default:
			CharlieController->CharliePatrolTimer = 20.0;
			break;
	}
	UE_LOG(LogTemp, Warning, TEXT("The updated Patrol Timer is now: %f (DIRECTOR)"), CharlieController->CharliePatrolTimer);
}

void ADN_AIDirector_v1_VM::UpdateDifficulty()
{
    UE_LOG(LogTemp, Warning, TEXT("Updating Difficulty (DIRECTOR)"));
	AdjustDifficulty();
	AdjustValues();
	BeginUpdateTimer();
}



