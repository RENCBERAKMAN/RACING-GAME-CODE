#include "MyProjectUI.h"
#include "MyProjectPlayerController.h"
#include "Kismet/GameplayStatics.h"

void UMyProjectUI::NativeConstruct()
{
    Super::NativeConstruct();

    if (Gas)
    {
        Gas->OnPressed.AddDynamic(this, &UMyProjectUI::OnGasPressed);
        Gas->OnReleased.AddDynamic(this, &UMyProjectUI::OnGasReleased);
    }

    if (Break)
    {
        Break->OnPressed.AddDynamic(this, &UMyProjectUI::OnBreakPressed);
        Break->OnReleased.AddDynamic(this, &UMyProjectUI::OnBreakReleased);
    }

    if (Left)
    {
        Left->OnPressed.AddDynamic(this, &UMyProjectUI::OnLeftPressed);
        Left->OnReleased.AddDynamic(this, &UMyProjectUI::OnLeftReleased);
    }

    if (Right)
    {
        Right->OnPressed.AddDynamic(this, &UMyProjectUI::OnRightPressed);
        Right->OnReleased.AddDynamic(this, &UMyProjectUI::OnRightReleased);
    }
}

// 🎮 Gaz
void UMyProjectUI::OnGasPressed()
{
    if (auto* PC = Cast<AMyProjectPlayerController>(UGameplayStatics::GetPlayerController(this, 0)))
    {
        PC->HandleThrottle(1.0f);
    }
}

void UMyProjectUI::OnGasReleased()
{
    if (auto* PC = Cast<AMyProjectPlayerController>(UGameplayStatics::GetPlayerController(this, 0)))
    {
        PC->HandleThrottle(0.0f);
    }
}

// 🛑 Fren
void UMyProjectUI::OnBreakPressed()
{
    if (auto* PC = Cast<AMyProjectPlayerController>(UGameplayStatics::GetPlayerController(this, 0)))
    {
        PC->HandleBrake(true);
    }
}

void UMyProjectUI::OnBreakReleased()
{
    if (auto* PC = Cast<AMyProjectPlayerController>(UGameplayStatics::GetPlayerController(this, 0)))
    {
        PC->HandleBrake(false);
    }
}

// ↪️ Sol
void UMyProjectUI::OnLeftPressed()
{
    if (auto* PC = Cast<AMyProjectPlayerController>(UGameplayStatics::GetPlayerController(this, 0)))
    {
        PC->HandleSteer(-1.0f);
    }
}

void UMyProjectUI::OnLeftReleased()
{
    if (auto* PC = Cast<AMyProjectPlayerController>(UGameplayStatics::GetPlayerController(this, 0)))
    {
        PC->HandleSteer(0.0f);
    }
}

// ↩️ Sağ
void UMyProjectUI::OnRightPressed()
{
    if (auto* PC = Cast<AMyProjectPlayerController>(UGameplayStatics::GetPlayerController(this, 0)))
    {
        PC->HandleSteer(1.0f);
    }
}

void UMyProjectUI::OnRightReleased()
{
    if (auto* PC = Cast<AMyProjectPlayerController>(UGameplayStatics::GetPlayerController(this, 0)))
    {
        PC->HandleSteer(0.0f);
    }
}