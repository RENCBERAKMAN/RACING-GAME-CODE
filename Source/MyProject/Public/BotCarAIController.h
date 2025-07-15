#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BotCarAIController.generated.h"

UCLASS()
class MYPROJECT_API ABotCarAIController : public AAIController
{
    GENERATED_BODY()

protected:
    virtual void BeginPlay() override;
};
