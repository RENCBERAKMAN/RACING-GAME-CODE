// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyProjectGameMode.generated.h"



UCLASS(MinimalAPI)
class AMyProjectGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    // Constructor
    AMyProjectGameMode();

    // Oyun başladığında çağrılan fonksiyon
    virtual void BeginPlay() override;

    // Spline yolu referansı (editörde atanabilir olmalı)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline Setup")
    AActor* SplineActor;
};