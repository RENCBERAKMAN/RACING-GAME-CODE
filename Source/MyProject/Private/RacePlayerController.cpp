#include "RacePlayerController.h"

void ARacePlayerController::BeginPlay()
{
    Super::BeginPlay();

    if (RaceUIClass)
    {
        RaceUI = CreateWidget<UUserWidget>(this, RaceUIClass);
        if (RaceUI)
        {
            RaceUI->AddToViewport();
        }
    }
}