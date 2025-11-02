#include "BotTestGameMode.h"
#include "BotCharacter.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"

ABotTestGameMode::ABotTestGameMode()
{
    // Настраиваем класс игрока по умолчанию
    DefaultPawnClass = nullptr; // Используем стандартный ThirdPersonCharacter
}

void ABotTestGameMode::BeginPlay()
{
    Super::BeginPlay();

    // Автоматически создаем ботов при запуске
    SpawnTestBots();
}

void ABotTestGameMode::SpawnTestBots()
{
    if (!BotClass)
    {
        UE_LOG(LogTemp, Warning, TEXT("BotTestGameMode: BotClass не установлен!"));
        return;
    }

    UWorld* World = GetWorld();
    if (!World)
    {
        return;
    }

    // Получаем Navigation System
    UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(World);
    if (!NavSys)
    {
        UE_LOG(LogTemp, Warning, TEXT("BotTestGameMode: Navigation System не найден!"));
        return;
    }

    // Получаем позицию игрока как центр для размещения ботов
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(World, 0);
    FVector SpawnCenter = PlayerPawn ? PlayerPawn->GetActorLocation() : FVector::ZeroVector;

    for (int32 i = 0; i < NumberOfBots; ++i)
    {
        // Генерируем случайную позицию в радиусе
        FVector RandomDirection = FMath::VRand();
        RandomDirection.Z = 0; // Оставляем только горизонтальное направление
        RandomDirection.Normalize();
        
        FVector SpawnLocation = SpawnCenter + RandomDirection * FMath::RandRange(200.0f, SpawnRadius);
        SpawnLocation.Z += 100.0f; // Поднимаем немного вверх

        // Проверяем, что позиция доступна для навигации
        FNavLocation NavLocation;
        bool bFoundLocation = NavSys->GetRandomReachablePointInRadius(
            SpawnLocation,
            200.0f,
            NavLocation
        );

        if (bFoundLocation)
        {
            SpawnLocation = NavLocation.Location;
        }

        // Создаем бота
        FActorSpawnParameters SpawnParams;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
        
        ABotCharacter* NewBot = World->SpawnActor<ABotCharacter>(BotClass, SpawnLocation, FRotator::ZeroRotator, SpawnParams);
        
        if (NewBot)
        {
            UE_LOG(LogTemp, Log, TEXT("BotTestGameMode: Создан бот %d в позиции %s"), i + 1, *SpawnLocation.ToString());
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("BotTestGameMode: Не удалось создать бота %d"), i + 1);
        }
    }
}

TArray<ABotCharacter*> ABotTestGameMode::GetAllBots()
{
    TArray<ABotCharacter*> AllBots;
    
    UWorld* World = GetWorld();
    if (World)
    {
        for (TActorIterator<ABotCharacter> ActorItr(World); ActorItr; ++ActorItr)
        {
            ABotCharacter* Bot = *ActorItr;
            if (Bot)
            {
                AllBots.Add(Bot);
            }
        }
    }
    
    return AllBots;
}


