#include "MyProjectPlayerController.h"
#include "MyProjectSportsCar.h"
#include "ChaosWheeledVehicleMovementComponent.h"
#include "Kismet/GameplayStatics.h"

void AMyProjectPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Başlangıçta kontrol edilen aracı yakala
	ControlledCar = Cast<AMyProjectSportsCar>(GetPawn());
}

void AMyProjectPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	// Yeni aracı kontrol etmeye başladığımızda referansı güncelle
	ControlledCar = Cast<AMyProjectSportsCar>(InPawn);
}

void AMyProjectPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// İstersen buraya input bağlama işlemleri ekleyebilirsin
}

void AMyProjectPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (ControlledCar && !ControlledCar->IsPlayerControlled())
	{
		// Bot kontrolündeki araç için hız kontrolü Tick'te yapılmaz
		return;
	}

	if (ControlledCar)
	{
		UChaosWheeledVehicleMovementComponent* Movement = ControlledCar->GetChaosVehicleMovement();
		if (Movement)
		{
			float CurrentSpeed = ControlledCar->GetVelocity().Size();
			const float TargetSpeed = 270.f;

			// Hız düşükse tam gaz ver
			if (CurrentSpeed < TargetSpeed)
			{
				Movement->SetThrottleInput(1.0f);
				ControlledCar->GetMesh()->AddForce(ControlledCar->GetActorForwardVector() * 200000.f);
			}
			else
			{
				Movement->SetThrottleInput(1.0f);
			}

			// Çok hızlı ise hafif fren uygula
			if (CurrentSpeed > TargetSpeed + 50.f)
			{
				Movement->SetBrakeInput(0.2f);
			}
			else
			{
				Movement->SetBrakeInput(0.0f);
			}
		}
	}
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
