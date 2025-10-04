// Confused Minds Inc.


#include "AI/Enemy/AIEnemyBase.h"

AAIEnemyBase::AAIEnemyBase()
{
}

AActor* AAIEnemyBase::SetNewWaypointData()
{
	int32 NextWaypointIndex;
	NextWaypointIndex = CurrentWaypointIndex + 1;
	if (NextWaypointIndex >= Waypoints.Num())
	{
		NextWaypointIndex = 0;
	}

	CurrentWaypointIndex = NextWaypointIndex;
	return Waypoints[CurrentWaypointIndex];
}

void AAIEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	
}

