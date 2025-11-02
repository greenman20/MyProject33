// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyProject3GameMode.generated.h"

/**
 *  Simple GameMode for a third person game with AI Bot support
 */
UCLASS(abstract)
class AMyProject3GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	
	/** Constructor */
	AMyProject3GameMode();

protected:
	virtual void BeginPlay() override;

public:
	// Ссылка на класс бота для создания
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Bot Settings")
	TSubclassOf<class ABotCharacter> BotClass;

	// Количество ботов для создания
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Bot Settings")
	int32 NumberOfBots = 2;

	// Радиус размещения ботов вокруг игрока
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Bot Settings")
	float BotSpawnRadius = 800.0f;

	// Минимальное расстояние от игрока для размещения ботов
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Bot Settings")
	float MinSpawnDistance = 300.0f;

	// Включить автоматическое создание ботов при старте
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Bot Settings")
	bool bAutoSpawnBots = true;

	// Функция для создания ботов
	UFUNCTION(BlueprintCallable, Category = "AI Bot")
	void SpawnAIBots();

	// Функция для получения всех ботов на уровне
	UFUNCTION(BlueprintCallable, Category = "AI Bot")
	TArray<class ABotCharacter*> GetAllAIBots();

	// Функция для удаления всех ботов
	UFUNCTION(BlueprintCallable, Category = "AI Bot")
	void RemoveAllAIBots();
};



