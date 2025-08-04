#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyProjectPlayerController.generated.h"

// İleri bildirimler
class UInputMappingContext;
class AMyProjectPawn;
class UMyProjectUI;
class AMyProjectSportsCar;

/**
 * Araç kontrolü yapan PlayerController
 */
UCLASS()
class MYPROJECT_API AMyProjectPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	/** Klavye / gamepad input mapping */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;

	/** Direksiyon kontrol sistemi aktif mi */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	bool bUseSteeringWheelControls = false;

	/** Direksiyon input mapping (aktifse) */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (EditCondition = "bUseSteeringWheelControls"))
	UInputMappingContext* SteeringWheelInputMappingContext;

	/** Kontrol edilen araç (base class) */
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AMyProjectPawn> VehiclePawn;

	/** UI Blueprint referansı */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = UI)
	TSubclassOf<UMyProjectUI> VehicleUIClass;

	/** Araç UI instance */
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UMyProjectUI> VehicleUI;

	/** Kontrol edilen araç (SportsCar) */
	UPROPERTY()
	AMyProjectSportsCar* ControlledCar;

protected:
	/** Oyunun başında çalışır */
	virtual void BeginPlay() override;

	/** Input sistemini ayarla */
	virtual void SetupInputComponent() override;

	/** Araç kontrolünü devraldığımızda çalışır */
	virtual void OnPossess(APawn* InPawn) override;

public:
	/** Her frame çalışır */
	virtual void Tick(float DeltaSeconds) override;

	/** UI'dan throttle (gaz) kontrolü */
	UFUNCTION(BlueprintCallable, Category = "Vehicle Input")
	void HandleThrottle(float Value);

	/** UI'dan direksiyon kontrolü */
	UFUNCTION(BlueprintCallable, Category = "Vehicle Input")
	void HandleSteer(float Value);

	/** UI'dan fren kontrolü */
	UFUNCTION(BlueprintCallable, Category = "Vehicle Input")
	void HandleBrake(bool bIsBraking);
};
