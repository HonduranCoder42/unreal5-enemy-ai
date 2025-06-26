// Fill out your copyright notice in the Description page of Project Settings.

/*
 * @file BTTask_IncrementPathIndex.cpp
 *
 * @brief Provides code to properly increment through the indexes of a patrol path
 *
 *  This file includes functions for properly navigating through the different indexes of a patrol path.
 *  It does this by:
 *  Creating a node name that can be placed in the Blackboard
 *  Getting Charlie's AI controller and Charlie
 *  Getting the Blackboard
 *  Getting the number of patrol points and the min/max indices
 *  Changing direction depending if currently at first/last index or in bidirectional mode
 *  Writing the new index value to the blackboard
 *
 *  @author Victor Mondragon
 *  @date 2025-02-04
 **/

#include "BTTask_IncrementPathIndex.h"

#include "Sub_CharlieAIController_v1_VM.h"
#include "Sub_Charlie_v1_VM.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_IncrementPathIndex::UBTTask_IncrementPathIndex(const FObjectInitializer& ObjectInitializer) :
	UBTTask_BlackboardBase{ObjectInitializer}
{
    NodeName = TEXT("IncrementPathIndex");
}

EBTNodeResult::Type UBTTask_IncrementPathIndex::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// try and get the AI controller
	if (auto* const Cont = Cast<ASub_CharlieAIController_v1_VM>(OwnerComp.GetAIOwner()))
	{
		// try and get the NPC
		if (auto* const NPC = Cast<ASub_Charlie_v1_VM>(Cont->GetPawn()))
		{
			// try and get the blackboard
			if (auto* const BC = OwnerComp.GetBlackboardComponent())
			{
				// get number of patrol points and min and max indices
				auto const NoOfPoints = NPC->GetPatrolPath()->Num();
				auto const MinIndex = 0;
				auto const MaxIndex = NoOfPoints - 1;
				auto Index = BC->GetValueAsInt(GetSelectedBlackboardKey());

				// change direction if we are at the first or last index if we are in bidirectional mode
				if (bBiDirectional)
				{
					if (Index >= MaxIndex && Direction == EDirectionType::Forward)
					{
						Direction = EDirectionType::Reverse;
					}
					else if (Index == MinIndex && Direction == EDirectionType::Reverse)
					{
						Direction = EDirectionType::Forward;
					}
				}
				// write new value of index to blackboard
				BC->SetValueAsInt(GetSelectedBlackboardKey(),
					(Direction == EDirectionType::Forward ? ++Index : --Index) % NoOfPoints);

				// finish with success
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}
	}
	// something went wrong so failure
	return EBTNodeResult::Failed;
}
