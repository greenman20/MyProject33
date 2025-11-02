#include "BotCharacter.h"
#include "BotAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

ABotCharacter::ABotCharacter()
{
    // Назначаем наш контроллер AI
    AIControllerClass = ABotAIController::StaticClass();
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

    // Настраиваем движение
    GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
    GetCharacterMovement()->JumpZVelocity = 600.0f;
    GetCharacterMovement()->AirControl = 0.35f;
    GetCharacterMovement()->MaxAcceleration = 1200.0f;
    GetCharacterMovement()->BrakingDecelerationWalking = 2000.0f;

    // Настраиваем капсулу
    GetCapsuleComponent()->SetCapsuleHalfHeight(88.0f);
    GetCapsuleComponent()->SetCapsuleRadius(34.0f);

    // Включаем Tick
    PrimaryActorTick.bCanEverTick = true;
}

void ABotCharacter::BeginPlay()
{
    Super::BeginPlay();
}

void ABotCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Отладочная информация
    if (IsPlayerInRange())
    {
        // Рисуем линию к игроку для отладки
        APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
        if (PlayerPawn)
        {
            DrawDebugLine(GetWorld(), GetActorLocation(), PlayerPawn->GetActorLocation(), 
                         FColor::Red, false, 0.1f, 0, 2.0f);
        }
    }
}

void ABotCharacter::StartRunning()
{
    GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
}

void ABotCharacter::StopRunning()
{
    GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void ABotCharacter::MoveToLocation(FVector TargetLocation)
{
    ABotAIController* AIController = Cast<ABotAIController>(GetController());
    if (AIController)
    {
        AIController->MoveToLocation(TargetLocation);
    }
}

bool ABotCharacter::IsPlayerInRange()
{
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (!PlayerPawn)
    {
        return false;
    }

    float DistanceToPlayer = FVector::Dist(GetActorLocation(), PlayerPawn->GetActorLocation());
    return DistanceToPlayer <= DetectionRadius;
}

bool ABotCharacter::CanSeePlayer()
{
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (!PlayerPawn)
    {
        return false;
    }

    // Проверяем расстояние
    if (!IsPlayerInRange())
    {
        return false;
    }

    // Проверяем угол обзора
    FVector BotForward = GetActorForwardVector();
    FVector DirectionToPlayer = (PlayerPawn->GetActorLocation() - GetActorLocation()).GetSafeNormal();
    
    float DotProduct = FVector::DotProduct(BotForward, DirectionToPlayer);
    float AngleToPlayer = FMath::RadiansToDegrees(FMath::Acos(DotProduct));

    if (AngleToPlayer > FieldOfView / 2.0f)
    {
        return false;
    }

    // Проверяем препятствия
    FHitResult HitResult;
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(this);
    QueryParams.AddIgnoredActor(PlayerPawn);

    bool bHit = GetWorld()->LineTraceSingleByChannel(
        HitResult,
        GetActorLocation(),
        PlayerPawn->GetActorLocation(),
        ECC_Visibility,
        QueryParams
    );

    return !bHit;
}