#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BotAIController.generated.h"

UCLASS()
class MYPROJECT3_API ABotAIController : public AAIController
{
    GENERATED_BODY()

public:
    ABotAIController();

protected:
    virtual void BeginPlay() override;
    virtual void OnPossess(APawn* InPawn) override;

public:
    // Компоненты AI
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
    class UBehaviorTreeComponent* BehaviorTreeComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
    class UBlackboardComponent* BlackboardComponent;

    // Ключи Blackboard
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI")
    FName PlayerKey;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI")
    FName CanSeePlayerKey;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI")
    FName LastKnownPlayerLocationKey;

    // Behavior Tree и Blackboard Asset
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI")
    class UBehaviorTree* BotBehaviorTree;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI")
    class UBlackboardData* BotBlackboardAsset;

    // Функции для обнаружения игрока
    UFUNCTION(BlueprintCallable, Category = "AI")
    void SetPlayerDetected(bool bDetected);

    UFUNCTION(BlueprintCallable, Category = "AI")
    void SetLastKnownPlayerLocation(FVector Location);

    UFUNCTION(BlueprintCallable, Category = "AI")
    bool CanSeePlayer();

    // Компонент восприятия
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
    class UAIPerceptionComponent* AIPerceptionComponent;

    // Конфигурация зрения
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
    class UAISenseConfig_Sight* SightConfig;

    // Переопределение для обнаружения игрока
    virtual void Tick(float DeltaTime) override;
};