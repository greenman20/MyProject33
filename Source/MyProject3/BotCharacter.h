#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BotCharacter.generated.h"

UCLASS()
class MYPROJECT3_API ABotCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    ABotCharacter();

protected:
    virtual void BeginPlay() override;

public:
    // Скорость движения бота
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bot Settings")
    float RunSpeed = 600.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bot Settings")
    float WalkSpeed = 300.0f;

    // Радиус обнаружения игрока
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bot Settings")
    float DetectionRadius = 1000.0f;

    // Угол обзора
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bot Settings")
    float FieldOfView = 90.0f;

    // Функции для управления движением
    UFUNCTION(BlueprintCallable, Category = "Bot Movement")
    void StartRunning();

    UFUNCTION(BlueprintCallable, Category = "Bot Movement")
    void StopRunning();

    UFUNCTION(BlueprintCallable, Category = "Bot Movement")
    void MoveToLocation(FVector TargetLocation);

    // Функции для обнаружения
    UFUNCTION(BlueprintCallable, Category = "Bot Detection")
    bool IsPlayerInRange();

    UFUNCTION(BlueprintCallable, Category = "Bot Detection")
    bool CanSeePlayer();

    // Переопределение для обновления логики
    virtual void Tick(float DeltaTime) override;
};