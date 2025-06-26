// Fill out your copyright notice in the Description page of Project Settings.

/*
 * @file BTTask_FindPathPoint.cpp
 *
 * @brief Provides code to properly find and navigate patrol path
 *
 *  This file includes functions for properly setting up and navigating a patrol path.
 *  It does this by:
 *  Creating a node name that can be placed in the Blackboard
 *  Getting Charlie's AI Controller
 *  Getting the Blackboard
 *  Getting the current patrol path index
 *  Getting Charlie and assigning the appropriate patrol path index
 *
 *  @author Victor Mondragon
 *  @date 2025-02-04
 **/

#include "BTTask_FindPathPoint.h"

#include "Sub_CharlieAIController_v1_VM.h"
#include "Sub_Charlie_v1_VM.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FindPathPoint::UBTTask_FindPathPoint(FObjectInitializer const& ObjectInitializer) :
	UBTTask_BlackboardBase{ObjectInitializer}
{
	NodeName = "Find Path Point";
}

EBTNodeResult::Type UBTTask_FindPathPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// attempt to get Charlie's controller
	if (auto* const cont = Cast<ASub_CharlieAIController_v1_VM>(OwnerComp.GetAIOwner()))
	{
		// attempt to get the blackboard component from the behavior tree
		if (auto* const bc = OwnerComp.GetBlackboardComponent())
		{
			// get the current patrol path index from the blackboard
			auto const index = bc->GetValueAsInt((GetSelectedBlackboardKey()));

			// get Charlie
			if (auto* npc = Cast<ASub_Charlie_v1_VM>(cont->GetPawn()))
			{
				// get the current patrol path vector from Charlie - this is local to the patrol path actor
				auto const Point = npc->GetPatrolPath()->GetPatrolPoint(index);

				// convert the local vector to a global point
				auto const GlobalPoint = npc->GetPatrolPath()->GetActorTransform().TransformPosition(Point);
				bc->SetValueAsVector(PatrolPathVectorKey.SelectedKeyName, GlobalPoint);

				// finish with success
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}
