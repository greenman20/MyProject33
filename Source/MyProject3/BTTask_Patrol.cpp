#include "BTTask_Patrol.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "NavigationSystem.h"
#include "Engine/World.h"

UBTTask_Patrol::UBTTask_Patrol()
{
    NodeName = TEXT("Patrol");
    bNotifyTick = true;
    bNotifyTaskFinished = true;
}

EBTNodeResult::Type UBTTask_Patrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AAIController* AIController = OwnerComp.GetAIOwner();
    if (!AIController)
    {
        return EBTNodeResult::Failed;
    }

    APawn* BotPawn = AIController->GetPawn();
    if (!BotPawn)
    {
        return EBTNodeResult::Failed;
    }

    // Сохраняем стартовую позицию
    StartLocation = BotPawn->GetActorLocation();
    
    // Генерируем случайную точку патрулирования
    UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(AIController->GetWorld());
    if (!NavSys)
    {
        return EBTNodeResult::Failed;
    }

    FNavLocation RandomLocation;
    bool bFoundLocation = NavSys->GetRandomReachablePointInRadius(
        StartLocation,
        PatrolRadius,
        RandomLocation
    );

    if (!bFoundLocation)
    {
        return EBTNodeResult::Failed;
    }

    CurrentPatrolTarget = RandomLocation.Location;
    WaitTimer = 0.0f;
    bIsWaiting = false;

    // Запускаем движение к точке патрулирования
    EPathFollowingRequestResult::Type MoveResult = AIController->MoveToLocation(CurrentPatrolTarget, AcceptableRadius);
    
    if (MoveResult == EPathFollowingRequestResult::Failed)
    {
        return EBTNodeResult::Failed;
    }

    return EBTNodeResult::InProgress;
}

void UBTTask_Patrol::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    AAIController* AIController = OwnerComp.GetAIOwner();
    if (!AIController)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return;
    }

    if (bIsWaiting)
    {
        // Ожидаем
        WaitTimer += DeltaSeconds;
        if (WaitTimer >= WaitTime)
        {
            // Время ожидания истекло, генерируем новую точку патрулирования
            UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(AIController->GetWorld());
            if (NavSys)
            {
                FNavLocation RandomLocation;
                bool bFoundLocation = NavSys->GetRandomReachablePointInRadius(
                    StartLocation,
                    PatrolRadius,
                    RandomLocation
                );

                if (bFoundLocation)
                {
                    CurrentPatrolTarget = RandomLocation.Location;
                    AIController->MoveToLocation(CurrentPatrolTarget, AcceptableRadius);
                    bIsWaiting = false;
                    WaitTimer = 0.0f;
                }
            }
        }
        return;
    }

    // Проверяем статус движения
    EPathFollowingStatus::Type MoveStatus = AIController->GetMoveStatus();
    
    if (MoveStatus == EPathFollowingStatus::Idle)
    {
        // Достигли точки патрулирования, начинаем ожидание
        bIsWaiting = true;
        WaitTimer = 0.0f;
    }
    else if (MoveStatus == EPathFollowingStatus::Waiting)
    {
        // Ждем начала движения
        return;
    }
}


