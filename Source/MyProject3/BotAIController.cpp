#include "BotAIController.h"
#include "BotCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "GameFramework/Character.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

ABotAIController::ABotAIController()
{
    // Создаем компоненты AI
    BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
    BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));

    // Создаем компонент восприятия для обнаружения игрока
    AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));

    // Настраиваем зрение
    SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
    SightConfig->SightRadius = 1000.0f;
    SightConfig->LoseSightRadius = 1200.0f;
    SightConfig->PeripheralVisionAngleDegrees = 90.0f;
    SightConfig->SetMaxAge(5.0f);
    SightConfig->AutoSuccessRangeFromLastSeenLocation = 520.0f;
    SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
    SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
    SightConfig->DetectionByAffiliation.bDetectEnemies = true;

    // Добавляем зрение к компоненту восприятия
    AIPerceptionComponent->SetDominantSense(*SightConfig->GetSenseImplementation());
    AIPerceptionComponent->ConfigureSense(*SightConfig);

    // Настраиваем ключи Blackboard
    PlayerKey = FName("Player");
    CanSeePlayerKey = FName("CanSeePlayer");
    LastKnownPlayerLocationKey = FName("LastKnownPlayerLocation");

    // Настраиваем поведение
    bWantsPlayerState = false;
}

void ABotAIController::BeginPlay()
{
    Super::BeginPlay();

    // Инициализируем Blackboard
    if (BlackboardComponent && BotBlackboardAsset)
    {
        BlackboardComponent->InitializeBlackboard(*BotBlackboardAsset);
    }

    // Запускаем Behavior Tree
    if (BehaviorTreeComponent && BotBehaviorTree)
    {
        BehaviorTreeComponent->StartTree(*BotBehaviorTree);
    }
}

void ABotAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    // Получаем ссылку на игрока
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (PlayerPawn && BlackboardComponent)
    {
        BlackboardComponent->SetValueAsObject(PlayerKey, PlayerPawn);
    }
}

void ABotAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Проверяем, видим ли мы игрока
    bool bCanSeePlayer = CanSeePlayer();
    if (BlackboardComponent)
    {
        BlackboardComponent->SetValueAsBool(CanSeePlayerKey, bCanSeePlayer);
        
        if (bCanSeePlayer)
        {
            APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
            if (PlayerPawn)
            {
                SetLastKnownPlayerLocation(PlayerPawn->GetActorLocation());
            }
        }
    }
}

void ABotAIController::SetPlayerDetected(bool bDetected)
{
    if (BlackboardComponent)
    {
        BlackboardComponent->SetValueAsBool(CanSeePlayerKey, bDetected);
    }
}

void ABotAIController::SetLastKnownPlayerLocation(FVector Location)
{
    if (BlackboardComponent)
    {
        BlackboardComponent->SetValueAsVector(LastKnownPlayerLocationKey, Location);
    }
}

bool ABotAIController::CanSeePlayer()
{
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (!PlayerPawn || !GetPawn())
    {
        return false;
    }

    // Проверяем расстояние до игрока
    float DistanceToPlayer = FVector::Dist(GetPawn()->GetActorLocation(), PlayerPawn->GetActorLocation());
    if (DistanceToPlayer > SightConfig->SightRadius)
    {
        return false;
    }

    // Проверяем, находится ли игрок в поле зрения
    FVector BotLocation = GetPawn()->GetActorLocation();
    FVector PlayerLocation = PlayerPawn->GetActorLocation();
    FVector BotForward = GetPawn()->GetActorForwardVector();
    
    FVector DirectionToPlayer = (PlayerLocation - BotLocation).GetSafeNormal();
    float DotProduct = FVector::DotProduct(BotForward, DirectionToPlayer);
    float AngleToPlayer = FMath::RadiansToDegrees(FMath::Acos(DotProduct));

    if (AngleToPlayer > SightConfig->PeripheralVisionAngleDegrees / 2.0f)
    {
        return false;
    }

    // Проверяем, нет ли препятствий между ботом и игроком
    FHitResult HitResult;
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(GetPawn());
    QueryParams.AddIgnoredActor(PlayerPawn);

    bool bHit = GetWorld()->LineTraceSingleByChannel(
        HitResult,
        BotLocation,
        PlayerLocation,
        ECC_Visibility,
        QueryParams
    );

    return !bHit;
}