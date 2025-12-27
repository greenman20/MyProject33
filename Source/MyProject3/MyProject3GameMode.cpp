// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyProject3GameMode.h"
#include "BotCharacter.h"
#include "EngineUtils.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"
#include "Engine/Engine.h"

AMyProject3GameMode::AMyProject3GameMode()
{
	// stub
}

void AMyProject3GameMode::BeginPlay()
{
	Super::BeginPlay();

	// Автоматически создаем ботов при запуске, если включено
	if (bAutoSpawnBots)
	{
		// Небольшая задержка, чтобы игрок успел заспавниться
		FTimerHandle SpawnTimer;
		GetWorldTimerManager().SetTimer(SpawnTimer, this, &AMyProject3GameMode::SpawnAIBots, 2.0f, false);
	}
}

void AMyProject3GameMode::SpawnAIBots()
{
	if (!BotClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("MyProject3GameMode: BotClass не установлен!"));
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
		UE_LOG(LogTemp, Warning, TEXT("MyProject3GameMode: Navigation System не найден!"));
		return;
	}

	// Получаем позицию игрока как центр для размещения ботов
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(World, 0);
	if (!PlayerPawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("MyProject3GameMode: Игрок не найден!"));
		return;
	}

	FVector SpawnCenter = PlayerPawn->GetActorLocation();
	int32 SuccessfullySpawned = 0;

	for (int32 i = 0; i < NumberOfBots; ++i)
	{
		// Генерируем случайную позицию в радиусе
		FVector RandomDirection = FMath::VRand();
		RandomDirection.Z = 0; // Оставляем только горизонтальное направление
		RandomDirection.Normalize();
		
		// Используем минимальное расстояние для избежания слишком близкого размещения
		float SpawnDistance = FMath::RandRange(MinSpawnDistance, BotSpawnRadius);
		FVector SpawnLocation = SpawnCenter + RandomDirection * SpawnDistance;
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
			SuccessfullySpawned++;
			UE_LOG(LogTemp, Log, TEXT("MyProject3GameMode: Создан бот %d в позиции %s"), i + 1, *SpawnLocation.ToString());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("MyProject3GameMode: Не удалось создать бота %d"), i + 1);
		}
	}

	UE_LOG(LogTemp, Log, TEXT("MyProject3GameMode: Успешно создано %d ботов из %d запланированных"), SuccessfullySpawned, NumberOfBots);
}

TArray<ABotCharacter*> AMyProject3GameMode::GetAllAIBots()
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

void AMyProject3GameMode::RemoveAllAIBots()
{
	TArray<ABotCharacter*> AllBots = GetAllAIBots();
	
	for (ABotCharacter* Bot : AllBots)
	{
		if (Bot)
		{
			Bot->Destroy();
		}
	}
	
	UE_LOG(LogTemp, Log, TEXT("MyProject3GameMode: Удалено %d ботов"), AllBots.Num());
}
