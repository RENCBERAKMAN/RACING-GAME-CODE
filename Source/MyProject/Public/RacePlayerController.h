#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "RacePlayerController.generated.h"

UCLASS()
class MYPROJECT_API ARacePlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    virtual void BeginPlay() override;

protected:
    // UI widget blueprint sýnýfý
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> RaceUIClass;

    // Oluþturulan widget örneði
    UPROPERTY()
    UUserWidget* RaceUI;
};