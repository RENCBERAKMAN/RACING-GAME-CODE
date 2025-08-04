#include "RaceUIWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "MyProjectSportsCar.h"
#include "GameFramework/PawnMovementComponent.h"
#include "TimerManager.h"

void URaceUIWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (Gas)
	{
		Gas->OnPressed.AddDynamic(this, &URaceUIWidget::OnGasPressed);
		Gas->OnReleased.AddDynamic(this, &URaceUIWidget::OnGasReleased);
	}

	if (Break)
	{
		Break->OnPressed.AddDynamic(this, &URaceUIWidget::OnBreakPressed);
		Break->OnReleased.AddDynamic(this, &URaceUIWidget::OnBreakReleased);
	}

	if (Left)
	{
		Left->OnPressed.AddDynamic(this, &URaceUIWidget::OnLeftPressed);
	}

	if (Right)
	{
		Right->OnPressed.AddDynamic(this, &URaceUIWidget::OnRightPressed);
	}

	if (Pause)
	{
		Pause->OnPressed.AddDynamic(this, &URaceUIWidget::OnPausePressed);
	}
}

void URaceUIWidget::OnGasPressed()
{
	if (auto* Arac = Cast<AMyProjectSportsCar>(UGameplayStatics::GetPlayerPawn(this, 0)))
	{
		Arac->SetThrottleInput(1.f);
	}
}

void URaceUIWidget::OnGasReleased()
{
	if (auto* Arac = Cast<AMyProjectSportsCar>(UGameplayStatics::GetPlayerPawn(this, 0)))
	{
		Arac->SetThrottleInput(0.f);
	}
}

void URaceUIWidget::OnBreakPressed()
{
	bIsBreaking = true;

	if (auto* Arac = Cast<AMyProjectSportsCar>(UGameplayStatics::GetPlayerPawn(this, 0)))
	{
		Arac->SetBrakeInput(1.f);
	}

	// Sürekli kontrol baþlasýn (0.5 saniyede bir kontrol)
	GetWorld()->GetTimerManager().SetTimer(CheckReverseTimer, this, &URaceUIWidget::CheckIfReverse, 0.2f, true);
}

void URaceUIWidget::OnBreakReleased()
{
	bIsBreaking = false;

	if (auto* Arac = Cast<AMyProjectSportsCar>(UGameplayStatics::GetPlayerPawn(this, 0)))
	{
		Arac->SetBrakeInput(0.f);
		Arac->SetThrottleInput(0.f); // Geri gitmeyi durdurur
	}

	GetWorld()->GetTimerManager().ClearTimer(CheckReverseTimer);
}

void URaceUIWidget::CheckIfReverse()
{
	if (!bIsBreaking) return;

	if (auto* Arac = Cast<AMyProjectSportsCar>(UGameplayStatics::GetPlayerPawn(this, 0)))
	{
		float Speed = Arac->GetVelocity().Size();

		if (Speed < 10.f) // Araç neredeyse durmuþsa
		{
			Arac->SetBrakeInput(0.f);
			Arac->SetThrottleInput(-1.f); // Geri gitmeye baþla
		}
	}
}

void URaceUIWidget::OnLeftPressed()
{
	if (auto* Arac = Cast<AMyProjectSportsCar>(UGameplayStatics::GetPlayerPawn(this, 0)))
	{
		Arac->SetSteeringInput(-1.f);
	}
}

void URaceUIWidget::OnRightPressed()
{
	if (auto* Arac = Cast<AMyProjectSportsCar>(UGameplayStatics::GetPlayerPawn(this, 0)))
	{
		Arac->SetSteeringInput(1.f);
	}
}

void URaceUIWidget::OnPausePressed()
{
	UGameplayStatics::SetGamePaused(GetWorld(), true);
}
