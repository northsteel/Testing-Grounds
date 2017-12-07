// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PatrolRoute.h"
#include "Runtime/AIModule/Classes/AIController.h"

// PRESUMPTIONS		Blackboard asset is set in the behavior tree
//					Array of patrol points on UPatrolRoute component instance is valid
EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* blackboardComp = OwnerComp.GetBlackboardComponent();
	//UE_LOG(LogTemp, Warning, TEXT("Waypoint index: %i"), index);

	UPatrolRoute* patrolRouteComp = OwnerComp.GetAIOwner()->GetPawn()->FindComponentByClass<UPatrolRoute>();
	if (!ensure(patrolRouteComp))
	{
		return EBTNodeResult::Failed;
	}
	patrolPoints = patrolRouteComp->GetPatrolPoints();
	if (patrolPoints.Num() > 0)
	{
		int32 index = blackboardComp->GetValueAsInt(nextWaypointIndex.SelectedKeyName);
		AActor* nextWaypoint = patrolPoints[index];
		blackboardComp->SetValueAsObject(this->nextWaypoint.SelectedKeyName, nextWaypoint);
		index = ++index % patrolPoints.Num();
		blackboardComp->SetValueAsInt(nextWaypointIndex.SelectedKeyName, index);
	}

	return EBTNodeResult::Succeeded;
}