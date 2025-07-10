#include "BotCarAIController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"

void ABotCarAIController::BeginPlay()
{
    Super::BeginPlay();

    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (PlayerPawn)
    {
        MoveToActor(PlayerPawn, 100.f); // Oyuncuyu 100 birim yakýnlýkta takip eder
    }
}
