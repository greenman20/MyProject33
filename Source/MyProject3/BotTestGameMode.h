#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BotTestGameMode.generated.h"

UCLASS()
class MYPROJECT3_API ABotTestGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    ABotTestGameMode();

protected:
    virtual void BeginPlay() override;

    // Ссылка на бота для тестирования
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bot Test")
    TSubclassOf<class ABotCharacter> BotClass;

    // Количество ботов для создания
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bot Test")
    int32 NumberOfBots = 1;

    // Радиус размещения ботов
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bot Test")
    float SpawnRadius = 500.0f;

    // Функция для создания ботов
    UFUNCTION(BlueprintCallable, Category = "Bot Test")
    void SpawnTestBots();

    // Функция для получения всех ботов на уровне
    UFUNCTION(BlueprintCallable, Category = "Bot Test")
    TArray<class ABotCharacter*> GetAllBots();
};


