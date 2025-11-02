#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_CheckPlayerVisibility.generated.h"

UCLASS()
class MYPROJECT3_API UBTTask_CheckPlayerVisibility : public UBTTaskNode
{
    GENERATED_BODY()

public:
    UBTTask_CheckPlayerVisibility();

protected:
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

    // Ключи Blackboard
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
    FBlackboardKeySelector PlayerKey;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
    FBlackboardKeySelector CanSeePlayerKey;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
    FBlackboardKeySelector LastKnownPlayerLocationKey;
};


