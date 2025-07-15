#include "MyGameMode.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

AMyGameMode::AMyGameMode()
{
    // BotCar Blueprint'i bul ve sýnýfa at
    static ConstructorHelpers::FClassFinder<APawn> BotCarBPClass(TEXT("/Game/VehicleTemplate/Blueprints/SportsCar/BP_BotCar.BP_BotCar_C"));

    if (BotCarBPClass.Succeeded())
    {
        BotCarClass = BotCarBPClass.Class;
    }
}

void AMyGameMode::BeginPlay()
{
    Super::BeginPlay();

    if (!BotCarClass) return;

    UWorld* World = GetWorld();
    if (!World) return;

    // Oyuncunun araç pozisyonunu al
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(World, 0);
    if (!PlayerPawn) return;

    FVector PlayerLocation = PlayerPawn->GetActorLocation();

    float XSpacing = 200.f; // Þeritler arasý mesafe (sað-sol)
    float YSpacing = -600.f; 

    for (int32 i = 1; i <= 3; i++)
    {
        FVector SpawnLocation = PlayerLocation + FVector(0.f, -XSpacing * i, 0.f);
        World->SpawnActor<APawn>(BotCarClass, SpawnLocation, FRotator::ZeroRotator);
    }

    
    for (int32 i = 0; i < 3; i++)
    {
        FVector SpawnLocation = PlayerLocation + FVector(YSpacing, -XSpacing * i, 0.f);
        World->SpawnActor<APawn>(BotCarClass, SpawnLocation, FRotator::ZeroRotator);
    }
}
