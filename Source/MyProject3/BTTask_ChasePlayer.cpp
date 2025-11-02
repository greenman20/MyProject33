#include "BTTask_ChasePlayer.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "BotCharacter.h"
#include "BotAIController.h"

UBTTask_ChasePlayer::UBTTask_ChasePlayer()
{
    NodeName = TEXT("Chase Player");
    bNotifyTick = true;
    bNotifyTaskFinished = true;
}

EBTNodeResult::Type UBTTask_ChasePlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
    if (!BlackboardComp)
    {
        return EBTNodeResult::Failed;
    }

    // Получаем игрока
    AActor* PlayerActor = Cast<AActor>(BlackboardComp->GetValueAsObject(PlayerKey.SelectedKeyName));
    if (!PlayerActor)
    {
        return EBTNodeResult::Failed;
    }

    // Проверяем, видим ли мы игрока
    bool bCanSeePlayer = BlackboardComp->GetValueAsBool(CanSeePlayerKey.SelectedKeyName);
    
    FVector TargetLocation;
    if (bCanSeePlayer)
    {
        // Если видим игрока, преследуем его напрямую
        TargetLocation = PlayerActor->GetActorLocation();
        BlackboardComp->SetValueAsVector(LastKnownPlayerLocationKey.SelectedKeyName, TargetLocation);
    }
    else if (bUseLastKnownLocation)
    {
        // Если не видим, идем к последнему известному местоположению
        TargetLocation = BlackboardComp->GetValueAsVector(LastKnownPlayerLocationKey.SelectedKeyName);
        
        // Если нет последнего известного местоположения, возвращаем неудачу
        if (TargetLocation.IsZero())
        {
            return EBTNodeResult::Failed;
        }
    }
    else
    {
        return EBTNodeResult::Failed;
    }

    // Запускаем движение к цели
    EPathFollowingRequestResult::Type MoveResult = AIController->MoveToLocation(TargetLocation, AcceptableRadius);
    
    if (MoveResult == EPathFollowingRequestResult::Failed)
    {
        return EBTNodeResult::Failed;
    }

    return EBTNodeResult::InProgress;
}

void UBTTask_ChasePlayer::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    AAIController* AIController = OwnerComp.GetAIOwner();
    if (!AIController)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return;
    }

    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
    if (!BlackboardComp)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return;
    }

    // Проверяем статус движения
    EPathFollowingStatus::Type MoveStatus = AIController->GetMoveStatus();
    
    if (MoveStatus == EPathFollowingStatus::Idle)
    {
        // Движение завершено
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
        return;
    }
    
    if (MoveStatus == EPathFollowingStatus::Waiting)
    {
        // Ждем начала движения
        return;
    }

    // Обновляем цель, если видим игрока
    bool bCanSeePlayer = BlackboardComp->GetValueAsBool(CanSeePlayerKey.SelectedKeyName);
    if (bCanSeePlayer)
    {
        AActor* PlayerActor = Cast<AActor>(BlackboardComp->GetValueAsObject(PlayerKey.SelectedKeyName));
        if (PlayerActor)
        {
            FVector PlayerLocation = PlayerActor->GetActorLocation();
            FVector CurrentLocation = AIController->GetPawn()->GetActorLocation();
            
            // Если игрок значительно переместился, обновляем цель
            if (FVector::Dist(PlayerLocation, CurrentLocation) > AcceptableRadius * 2.0f)
            {
                AIController->MoveToLocation(PlayerLocation, AcceptableRadius);
                BlackboardComp->SetValueAsVector(LastKnownPlayerLocationKey.SelectedKeyName, PlayerLocation);
            }
        }
    }
}


