#include "RacePlayerController.h"
#include "Blueprint/UserWidget.h"
#include "RaceUIBase.h"
#include "MyProjectSportsCar.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Components/SlateWrapperTypes.h"

void ARacePlayerController::BeginPlay()
{
    Super::BeginPlay();

    // 🎯 Mouse imleci ve input ayarı
    bShowMouseCursor = true;

    FInputModeUIOnly InputMode;
    InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
    InputMode.SetWidgetToFocus(nullptr);
    SetInputMode(InputMode);

    // 🎮 UI oluşturulup ekrana yerleştirilmesi
    if (!RaceUI && RaceUIClass)
    {
        RaceUI = CreateWidget<URaceUIBase>(this, RaceUIClass);
    }

    if (RaceUI && !RaceUI->IsInViewport())
    {
        RaceUI->AddToViewport();
        RaceUI->SetVisibility(ESlateVisibility::Visible);
        RaceUI->SetRenderOpacity(1.0f);
        UE_LOG(LogTemp, Warning, TEXT("BP_MobileRaceUI başarıyla ekrana eklendi."));
    }
    else if (!RaceUI)
    {
        UE_LOG(LogTemp, Error, TEXT("BP_MobileRaceUI yüklenemedi! RaceUIClass atanmamış mı?"));
    }

    // Debug için null kontrolleri
    if (RaceUI)
    {
        if (!RaceUI->SpeedText) UE_LOG(LogTemp, Error, TEXT("SpeedText nullptr! UI'da tanımlı mı?"));
        if (!RaceUI->SpeedBar)  UE_LOG(LogTemp, Error, TEXT("SpeedBar nullptr! UI'da tanımlı mı?"));
    }
}

void ARacePlayerController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    if (AMyProjectSportsCar* Vehicle = Cast<AMyProjectSportsCar>(GetPawn()))
    {
        const float Speed = Vehicle->GetVelocity().Size();
        const float MaxSpeed = 3000.0f;

        if (RaceUI && RaceUI->SpeedText)
        {
            FText SpeedDisplay = FText::FromString(FString::Printf(TEXT("Hız: %.0f km/h"), Speed / 28.0f));
            RaceUI->SpeedText->SetText(SpeedDisplay);
        }

        if (RaceUI && RaceUI->SpeedBar)
        {
            float Ratio = FMath::Clamp(Speed / MaxSpeed, 0.0f, 1.0f);
            RaceUI->SpeedBar->SetPercent(Ratio);

            FLinearColor FillColor =
                Ratio < 0.5f ? FLinearColor::Green :
                Ratio < 0.8f ? FLinearColor::Yellow :
                FLinearColor::Red;

            RaceUI->SpeedBar->SetFillColorAndOpacity(FillColor);
        }
    }
}

// 🔧 GAZ
void ARacePlayerController::GazVer()
{
    if (AMyProjectSportsCar* Vehicle = Cast<AMyProjectSportsCar>(GetPawn()))
    {
        Vehicle->SetThrottleInput(1.0f);
        Vehicle->SetBrakeInput(0.0f);
    }
}

// 🔧 FREN / GERİ
void ARacePlayerController::FrenYap()
{
    if (AMyProjectSportsCar* Vehicle = Cast<AMyProjectSportsCar>(GetPawn()))
    {
        const float ForwardSpeed = Vehicle->GetVelocity().Size();
        if (ForwardSpeed > 5.0f)
        {
            Vehicle->SetBrakeInput(1.0f);
            Vehicle->SetThrottleInput(0.0f);
        }
        else
        {
            Vehicle->SetBrakeInput(0.0f);
            Vehicle->SetThrottleInput(-1.0f); // Geri git
        }
    }
}

// 🔧 SOL
void ARacePlayerController::DireksiyonSol()
{
    if (AMyProjectSportsCar* Vehicle = Cast<AMyProjectSportsCar>(GetPawn()))
    {
        Vehicle->SetSteeringInput(-1.0f);
    }
}

// 🔧 SAĞ
void ARacePlayerController::DireksiyonSag()
{
    if (AMyProjectSportsCar* Vehicle = Cast<AMyProjectSportsCar>(GetPawn()))
    {
        Vehicle->SetSteeringInput(1.0f);
    }
}
