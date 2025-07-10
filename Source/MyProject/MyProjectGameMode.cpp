// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyProjectGameMode.h"
#include "MyProjectPlayerController.h"
#include "MyProjectSportsCar.h"              // Araç sınıfı
#include "Components/SplineComponent.h"      // Spline bileşeni

AMyProjectGameMode::AMyProjectGameMode()
{
    PlayerControllerClass = AMyProjectPlayerController::StaticClass();
}

void AMyProjectGameMode::BeginPlay()
{
    Super::BeginPlay();

    // 🚗 Araç spawn konumu ve yönü
    FVector SpawnLocation = FVector(0, 0, 100);
    FRotator SpawnRotation = FRotator::ZeroRotator;

    // ✅ Araç spawn işlemi
    AMyProjectSportsCar* SpawnedCar = GetWorld()->SpawnActor<AMyProjectSportsCar>(
        AMyProjectSportsCar::StaticClass(),
        SpawnLocation,
        SpawnRotation
    );

    // 🔗 Spline bağlantısı varsa, araca referansı at
    if (SpawnedCar && SplineActor)
    {
        // Aktör içindeki spline bileşenini bul ve Cast et
        USplineComponent* FoundSpline = Cast<USplineComponent>(
            SplineActor->GetComponentByClass(USplineComponent::StaticClass())
        );

        // Araç içine aktar
        SpawnedCar->SplineActor = SplineActor;
        SpawnedCar->SplineComp = FoundSpline;
    }
}