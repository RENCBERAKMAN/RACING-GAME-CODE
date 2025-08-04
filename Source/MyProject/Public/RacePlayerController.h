#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "RaceUIBase.h"
#include "RacePlayerController.generated.h"

UCLASS()
class MYPROJECT_API ARacePlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;

    // 🚗 Oyuncu input fonksiyonları (BP_RaceUI'den çağrılacak)
    UFUNCTION(BlueprintCallable, Category = "Vehicle|Input")
    void GazVer();

    UFUNCTION(BlueprintCallable, Category = "Vehicle|Input")
    void FrenYap();

    UFUNCTION(BlueprintCallable, Category = "Vehicle|Input")
    void DireksiyonSol();

    UFUNCTION(BlueprintCallable, Category = "Vehicle|Input")
    void DireksiyonSag();

protected:
    // 🖥️ UI Widget blueprint sınıfı (Editör üzerinden atanır)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    TSubclassOf<URaceUIBase> RaceUIClass;

    // Oluşturulan widget referansı
    UPROPERTY()
    URaceUIBase* RaceUI;
};
