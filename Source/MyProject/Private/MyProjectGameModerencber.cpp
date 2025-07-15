#include "MyProjectGameModerencber.h"
#include "MyProjectGameMode.h"
#include "RacePlayerController.h"
#include "MyProjectSportsCar.h"


AMyProjectGameModerencber::AMyProjectGameModerencber()
{
    PlayerControllerClass = ARacePlayerController::StaticClass();
    DefaultPawnClass = AMyProjectSportsCar::StaticClass();
}