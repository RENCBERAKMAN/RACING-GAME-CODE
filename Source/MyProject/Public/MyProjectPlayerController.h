#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyProjectPlayerController.generated.h"

class UInputMappingContext;
class AMyProjectPawn;
class UMyProjectUI;
class AMyProjectSportsCar;

UCLASS()
class MYPROJECT_API AMyProjectPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	bool bUseSteeringWheelControls = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (EditCondition = "bUseSteeringWheelControls"))
	UInputMappingContext* SteeringWheelInputMappingContext;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AMyProjectPawn> VehiclePawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = UI)
	TSubclassOf<UMyProjectUI> VehicleUIClass;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UMyProjectUI> VehicleUI;

	// 👇 Eklendi: kontrol edilen aracı referanslamak için
	UPROPERTY()
	AMyProjectSportsCar* ControlledCar;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* InPawn) override;

public:
	virtual void Tick(float DeltaSeconds) override;

	// 👇 Eklendi: UI'dan çağrılacak input fonksiyonları
	void HandleThrottle(float Value);
	void HandleSteer(float Value);
	void HandleBrake(bool bIsBraking);
};