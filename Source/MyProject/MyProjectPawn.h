#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "ChaosWheeledVehicleMovementComponent.h"
#include "InputAction.h"
#include "InputActionValue.h"

#include "MyProjectPawn.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateVehicle, Log, All);

/**
 *  Vehicle Pawn class
 *  Handles common functionality for all vehicle types,
 *  including input handling and camera management.
 *  Specific vehicle configurations are handled in subclasses.
 */
UCLASS(abstract)
class AMyProjectPawn : public AWheeledVehiclePawn
{
	GENERATED_BODY()

	/** Spring Arm for the front camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* FrontSpringArm;

	/** Front Camera component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FrontCamera;

	/** Spring Arm for the back camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* BackSpringArm;

	/** Back Camera component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* BackCamera;

	/** Reference to Chaos Vehicle Movement */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UChaosWheeledVehicleMovementComponent> ChaosVehicleMovement;

protected:

	/** Input mappings */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* SteeringAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* ThrottleAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* BrakeAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* HandbrakeAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* LookAroundAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* ToggleCameraAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* ResetVehicleAction;

	/** Camera state */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	bool bFrontCameraActive = false;

public:
	AMyProjectPawn();

	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	virtual void Tick(float DeltaTime) override;

protected:
	void Steering(const FInputActionValue& Value);
	void Throttle(const FInputActionValue& Value);
	void Brake(const FInputActionValue& Value);
	void StartBrake(const FInputActionValue& Value);
	void StopBrake(const FInputActionValue& Value);
	void StartHandbrake(const FInputActionValue& Value);
	void StopHandbrake(const FInputActionValue& Value);
	void LookAround(const FInputActionValue& Value);
	void ToggleCamera(const FInputActionValue& Value);
	void ResetVehicle(const FInputActionValue& Value);

	/** Brake light toggle — usable in Blueprint or C++ */
	UFUNCTION(BlueprintNativeEvent, Category = "Vehicle")
	void BrakeLights(bool bBraking);

public:

	/** Direct access to the movement component (no Cast needed) */
	UFUNCTION(BlueprintCallable, Category = "Vehicle")
	UChaosWheeledVehicleMovementComponent* GetSafeVehicleMovement() const
	{
		return ChaosVehicleMovement;
	}

	/** Getters */
	FORCEINLINE USpringArmComponent* GetFrontSpringArm() const { return FrontSpringArm; }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FrontCamera; }
	FORCEINLINE USpringArmComponent* GetBackSpringArm() const { return BackSpringArm; }
	FORCEINLINE UCameraComponent* GetBackCamera() const { return BackCamera; }
	FORCEINLINE UChaosWheeledVehicleMovementComponent* GetMovementComponent() const { return ChaosVehicleMovement; }
	FORCEINLINE UChaosWheeledVehicleMovementComponent* GetChaosVehicleMovement() const { return ChaosVehicleMovement; }
};