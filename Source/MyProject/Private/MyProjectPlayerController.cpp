#include "MyProjectPlayerController.h"
#include "MyProjectSportsCar.h"
#include "Kismet/GameplayStatics.h"

void AMyProjectPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Kontrol edilen aracın referansını al
	ControlledCar = Cast<AMyProjectSportsCar>(GetPawn());
}

void AMyProjectPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ControlledCar = Cast<AMyProjectSportsCar>(InPawn);
}

void AMyProjectPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// (Input bağlama işlemleri varsa buraya gelir)
}

void AMyProjectPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// Gerekirse her frame işlem yapılabilir
}

void AMyProjectPlayerController::HandleThrottle(float Value)
{
	if (ControlledCar)
	{
		ControlledCar->ApplyThrottle(Value);
	}
}

void AMyProjectPlayerController::HandleSteer(float Value)
{
	if (ControlledCar)
	{
		ControlledCar->ApplySteer(Value);
	}
}

void AMyProjectPlayerController::HandleBrake(bool bIsBraking)
{
	if (ControlledCar)
	{
		ControlledCar->ApplyBrake(bIsBraking);
	}
}