#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Patrol.generated.h"

UCLASS()
class MYPROJECT3_API UBTTask_Patrol : public UBTTaskNode
{
    GENERATED_BODY()

public:
    UBTTask_Patrol();

protected:
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
    virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

    // Настройки патрулирования
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
    float PatrolRadius = 500.0f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
    float WaitTime = 2.0f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
    float AcceptableRadius = 100.0f;

private:
    FVector StartLocation;
    FVector CurrentPatrolTarget;
    float WaitTimer;
    bool bIsWaiting;
};


