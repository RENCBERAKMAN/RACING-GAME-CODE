#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "RaceUIBase.h" // Hız UI'sinin sınıfı
#include "RacePlayerController.generated.h"

UCLASS(Blueprintable)
class MYPROJECT_API ARacePlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;

    // 🚗 Oyuncu input fonksiyonları
    UFUNCTION(BlueprintCallable, Category = "Vehicle|Input")
    void GazVer();

    UFUNCTION(BlueprintCallable, Category = "Vehicle|Input")
    void FrenYap();

    UFUNCTION(BlueprintCallable, Category = "Vehicle|Input")
    void DireksiyonSol();

    UFUNCTION(BlueprintCallable, Category = "Vehicle|Input")
    void DireksiyonSag();

protected:
    // 🖥️ UI Widget blueprint sınıfı
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> RaceUIClass;

    // UI referansı
    UPROPERTY()
    URaceUIBase* RaceUI; // Widget’ın tipini RaceUIBase olarak cast ediyoruz
};