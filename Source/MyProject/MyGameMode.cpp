#include "MyGameMode.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

AMyGameMode::AMyGameMode()
{
    // BotCar Blueprint'i bul ve s�n�fa at
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

    // Oyuncunun ara� pozisyonunu al
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(World, 0);
    if (!PlayerPawn) return;

    FVector PlayerLocation = PlayerPawn->GetActorLocation();

    float XSpacing = 350.f; // �eritler aras� mesafe (sa�-sol)
    float YSpacing = -600.f; // Ara� s�ralar� aras� mesafe (�n-arka)

    // �n s�rada 3 bot, oyuncunun solunda olacak (sen en sa�das�n)
    for (int32 i = 1; i <= 3; i++)
    {
        FVector SpawnLocation = PlayerLocation + FVector(0.f, -XSpacing * i, 0.f);
        World->SpawnActor<APawn>(BotCarClass, SpawnLocation, FRotator::ZeroRotator);
    }

    // Arkanda 4 bot ara� (bir s�ra halinde)
    for (int32 i = 0; i < 4; i++)
    {
        FVector SpawnLocation = PlayerLocation + FVector(YSpacing, -XSpacing * i, 0.f);
        World->SpawnActor<APawn>(BotCarClass, SpawnLocation, FRotator::ZeroRotator);
    }
}
