#include "RacePlayerController.h"
#include "Blueprint/UserWidget.h"
#include "RaceUIBase.h"
#include "MyProjectSportsCar.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Components/SlateWrapperTypes.h" // Renk değiştirme için gerekli

void ARacePlayerController::BeginPlay()
{
    Super::BeginPlay();

    // Eğer UI henüz oluşturulmadıysa, oluştur
    if (!RaceUI && RaceUIClass)
    {
        RaceUI = CreateWidget<URaceUIBase>(this, RaceUIClass);
    }

    // Ekranda değilse ekle
    if (RaceUI && !RaceUI->IsInViewport())
    {
        RaceUI->AddToViewport();
        UE_LOG(LogTemp, Warning, TEXT("BP_MobileRaceUI başarıyla ekrana eklendi."));
    }
    else if (!RaceUI)
    {
        UE_LOG(LogTemp, Error, TEXT("BP_MobileRaceUI yüklenemedi! RaceUIClass atanmamış mı veya cast başarısız mı?"));
    }
    if (RaceUI)
{
    if (!RaceUI->SpeedText) UE_LOG(LogTemp, Error, TEXT("SpeedText nullptr! UI'da tanımlı mı?"));
    if (!RaceUI->SpeedBar) UE_LOG(LogTemp, Error, TEXT("SpeedBar nullptr! UI'da tanımlı mı?"));
}
    if (RaceUI)
    {
        if (!RaceUI->SpeedText) UE_LOG(LogTemp, Error, TEXT("SpeedText nullptr! UI'da tanımlı mı?"));
        if (!RaceUI->SpeedBar) UE_LOG(LogTemp, Error, TEXT("SpeedBar nullptr! UI'da tanımlı mı?"));
    }
    if (RaceUI)
    {
        RaceUI->AddToViewport();
        RaceUI->SetVisibility(ESlateVisibility::Visible);
        RaceUI->SetRenderOpacity(1.0f); // Tam görünürlük

        UE_LOG(LogTemp, Warning, TEXT("UI zorla görünür hale getirildi"));
    }
    UE_LOG(LogTemp, Warning, TEXT("BP_MobileRaceUI ekrana eklendi!"));
}


void ARacePlayerController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    if (AMyProjectSportsCar* Vehicle = Cast<AMyProjectSportsCar>(GetPawn()))
    {
        const float Speed = Vehicle->GetVelocity().Size();
        const float MaxSpeed = 3000.0f; // Ayarlanabilir

        // 📝 SpeedText güncellemesi
        if (RaceUI && RaceUI->SpeedText)
        {
            FText SpeedDisplay = FText::FromString(FString::Printf(TEXT("Hız: %.0f km/h"), Speed / 28.0f));
            RaceUI->SpeedText->SetText(SpeedDisplay);
        }

        // 📊 SpeedBar doluluk ve renk geçişi
        if (RaceUI && RaceUI->SpeedBar)
        {
            float Ratio = FMath::Clamp(Speed / MaxSpeed, 0.0f, 1.0f);
            RaceUI->SpeedBar->SetPercent(Ratio);

            // Renk geçişi ekle
            FLinearColor FillColor;

            if (Ratio < 0.5f)
            {
                FillColor = FLinearColor::Green;
            }
            else if (Ratio < 0.8f)
            {
                FillColor = FLinearColor::Yellow;
            }
            else
            {
                FillColor = FLinearColor::Red;
            }

            RaceUI->SpeedBar->SetFillColorAndOpacity(FillColor);
        }
    }
}

void ARacePlayerController::GazVer()
{
    if (AMyProjectSportsCar* Vehicle = Cast<AMyProjectSportsCar>(GetPawn()))
    {
        Vehicle->SetThrottleInput(1.0f);
        Vehicle->SetBrakeInput(0.0f);
    }
}

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
            Vehicle->SetThrottleInput(-1.0f);
        }
    }
}

void ARacePlayerController::DireksiyonSol()
{
    if (AMyProjectSportsCar* Vehicle = Cast<AMyProjectSportsCar>(GetPawn()))
    {
        Vehicle->SetSteeringInput(-1.0f);
    }
}

void ARacePlayerController::DireksiyonSag()
{
    if (AMyProjectSportsCar* Vehicle = Cast<AMyProjectSportsCar>(GetPawn()))
    {
        Vehicle->SetSteeringInput(1.0f);
    }
}