#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RaceUIWidget.generated.h"

class UButton;

UCLASS()
class MYPROJECT_API URaceUIWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UButton* Gas;

	UPROPERTY(meta = (BindWidget))
	UButton* Break;

	UPROPERTY(meta = (BindWidget))
	UButton* Left;

	UPROPERTY(meta = (BindWidget))
	UButton* Right;

	UPROPERTY(meta = (BindWidget))
	UButton* Pause;

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
	void OnRightPressed();

	UFUNCTION()
	void OnPausePressed();

	FTimerHandle CheckReverseTimer;

	void CheckIfReverse();

	bool bIsBreaking = false;
};
