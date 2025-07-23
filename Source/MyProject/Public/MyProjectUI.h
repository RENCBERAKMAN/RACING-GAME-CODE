#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "MyProjectUI.generated.h"

UCLASS()
class MYPROJECT_API UMyProjectUI : public UUserWidget
{
    GENERATED_BODY()

protected:

    // BP_RaceUI'daki butonlar
    UPROPERTY(meta = (BindWidget))
    UButton* Gas;

    UPROPERTY(meta = (BindWidget))
    UButton* Break;

    UPROPERTY(meta = (BindWidget))
    UButton* Left;

    UPROPERTY(meta = (BindWidget))
    UButton* Right;

    // Eventler için fonksiyonlar
    UFUNCTION()
    void OnGasPressed();

    UFUNCTION()
    void OnGasReleased();

    UFUNCTION()
    void OnBreakPressed();

    UFUNCTION()
    void OnBreakReleased();

    UFUNCTION()
    void OnLeftPressed();

    UFUNCTION()
    void OnLeftReleased();

    UFUNCTION()
    void OnRightPressed();

    UFUNCTION()
    void OnRightReleased();

    virtual void NativeConstruct() override;
};