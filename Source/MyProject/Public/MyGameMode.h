#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BotCar.h"
#include "MyGameMode.generated.h"

UCLASS()
class MYPROJECT_API AMyGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    AMyGameMode();

protected:
    virtual void BeginPlay() override;

public:
    // Spawn edece�imiz bot arac�n s�n�f�
    UPROPERTY(EditDefaultsOnly, Category = "Bot")
    TSubclassOf<APawn> BotCarClass;
};
