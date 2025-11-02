#include "BTTask_CheckPlayerVisibility.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "BotCharacter.h"
#include "BotAIController.h"

UBTTask_CheckPlayerVisibility::UBTTask_CheckPlayerVisibility()
{
    NodeName = TEXT("Check Player Visibility");
}

EBTNodeResult::Type UBTTask_CheckPlayerVisibility::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AAIController* AIController = OwnerComp.GetAIOwner();
    if (!AIController)
    {
        return EBTNodeResult::Failed;
    }

    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
    if (!BlackboardComp)
    {
        return EBTNodeResult::Failed;
    }

    // Получаем ссылку на бота
    ABotCharacter* BotCharacter = Cast<ABotCharacter>(AIController->GetPawn());
    if (!BotCharacter)
    {
        return EBTNodeResult::Failed;
    }

    // Проверяем, видим ли мы игрока
    bool bCanSeePlayer = BotCharacter->CanSeePlayer();
    BlackboardComp->SetValueAsBool(CanSeePlayerKey.SelectedKeyName, bCanSeePlayer);

    if (bCanSeePlayer)
    {
        // Если видим игрока, обновляем его местоположение
        AActor* PlayerActor = Cast<AActor>(BlackboardComp->GetValueAsObject(PlayerKey.SelectedKeyName));
        if (PlayerActor)
        {
            FVector PlayerLocation = PlayerActor->GetActorLocation();
            BlackboardComp->SetValueAsVector(LastKnownPlayerLocationKey.SelectedKeyName, PlayerLocation);
        }
    }

    return EBTNodeResult::Succeeded;
}


