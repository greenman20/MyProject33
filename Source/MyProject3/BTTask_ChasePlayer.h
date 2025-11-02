#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_ChasePlayer.generated.h"

UCLASS()
class MYPROJECT3_API UBTTask_ChasePlayer : public UBTTaskNode
{
    GENERATED_BODY()

public:
    UBTTask_ChasePlayer();

protected:
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
    virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

    // Ключи Blackboard
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
    FBlackboardKeySelector PlayerKey;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
    FBlackboardKeySelector CanSeePlayerKey;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
    FBlackboardKeySelector LastKnownPlayerLocationKey;

    // Настройки преследования
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
    float AcceptableRadius = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
    bool bUseLastKnownLocation = true;
};


