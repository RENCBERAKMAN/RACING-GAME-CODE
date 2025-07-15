#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MyProjectGameModerencber.generated.h" // ← Bu en son include olmalı

UCLASS()
class MYPROJECT_API AMyProjectGameModerencber : public AGameMode
{
    GENERATED_BODY()

public:
    AMyProjectGameModerencber();
};