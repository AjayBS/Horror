// Confused Minds Inc.


#include "AI/Enemy/AIEnemyBase.h"

AAIEnemyBase::AAIEnemyBase()
{
}

AActor* AAIEnemyBase::SetNewWaypointData()
{
	// Ensure there are waypoints to follow
	if (Waypoints.Num() == 0)
	{
		return nullptr;
	}

	// Determine next index based on direction
	int32 NextWaypointIndex = bMovingUp ? CurrentWaypointIndex + 1 : CurrentWaypointIndex - 1;

	// If we've reached the end, reverse direction
	if (NextWaypointIndex >= Waypoints.Num())
	{
		NextWaypointIndex = Waypoints.Num() - 2;
		bMovingUp = false;
	}
	else if (NextWaypointIndex < 0)
	{
		NextWaypointIndex = 1;
		bMovingUp = true;
	}

	CurrentWaypointIndex = NextWaypointIndex;

	// Return the next waypoint if valid
	return Waypoints.IsValidIndex(CurrentWaypointIndex) ? Waypoints[CurrentWaypointIndex] : nullptr;
}

void AAIEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	
}

