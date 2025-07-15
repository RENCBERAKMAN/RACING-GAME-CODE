#include "MyProjectGameMode.h"
#include "MyProjectPlayerController.h"
#include "Components/SplineComponent.h" 

AMyProjectGameMode::AMyProjectGameMode()
{
	PlayerControllerClass = AMyProjectPlayerController::StaticClass();
}

void AMyProjectGameMode::BeginPlay()
{
	Super::BeginPlay();

}