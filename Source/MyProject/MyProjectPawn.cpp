#include "MyProjectPawn.h"
#include "MyProjectWheelFront.h"
#include "MyProjectWheelRear.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "ChaosWheeledVehicleMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#define LOCTEXT_NAMESPACE "VehiclePawn"

DEFINE_LOG_CATEGORY(LogTemplateVehicle);

AMyProjectPawn::AMyProjectPawn()
{
	// Front camera
	FrontSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Front Spring Arm"));
	FrontSpringArm->SetupAttachment(GetMesh());
	FrontSpringArm->TargetArmLength = 0.0f;
	FrontSpringArm->bDoCollisionTest = false;
	FrontSpringArm->bEnableCameraRotationLag = true;
	FrontSpringArm->CameraRotationLagSpeed = 15.0f;
	FrontSpringArm->SetRelativeLocation(FVector(30.0f, 0.0f, 120.0f));

	FrontCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Front Camera"));
	FrontCamera->SetupAttachment(FrontSpringArm);
	FrontCamera->bAutoActivate = false;

	// Back camera
	BackSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Back Spring Arm"));
	BackSpringArm->SetupAttachment(GetMesh());
	BackSpringArm->TargetArmLength = 650.0f;
	BackSpringArm->SocketOffset.Z = 150.0f;
	BackSpringArm->bDoCollisionTest = false;
	BackSpringArm->bInheritPitch = false;
	BackSpringArm->bInheritRoll = false;
	BackSpringArm->bEnableCameraRotationLag = true;
	BackSpringArm->CameraRotationLagSpeed = 2.0f;
	BackSpringArm->CameraLagMaxDistance = 50.0f;

	BackCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Back Camera"));
	BackCamera->SetupAttachment(BackSpringArm);

	// Physics
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetCollisionProfileName(FName("Vehicle"));

	// Movement
	ChaosVehicleMovement = CastChecked<UChaosWheeledVehicleMovementComponent>(GetVehicleMovement());
}

void AMyProjectPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* Enhanced = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		Enhanced->BindAction(SteeringAction, ETriggerEvent::Triggered, this, &AMyProjectPawn::Steering);
		Enhanced->BindAction(SteeringAction, ETriggerEvent::Completed, this, &AMyProjectPawn::Steering);
		Enhanced->BindAction(ThrottleAction, ETriggerEvent::Triggered, this, &AMyProjectPawn::Throttle);
		Enhanced->BindAction(ThrottleAction, ETriggerEvent::Completed, this, &AMyProjectPawn::Throttle);
		Enhanced->BindAction(BrakeAction, ETriggerEvent::Triggered, this, &AMyProjectPawn::Brake);
		Enhanced->BindAction(BrakeAction, ETriggerEvent::Started, this, &AMyProjectPawn::StartBrake);
		Enhanced->BindAction(BrakeAction, ETriggerEvent::Completed, this, &AMyProjectPawn::StopBrake);
		Enhanced->BindAction(HandbrakeAction, ETriggerEvent::Started, this, &AMyProjectPawn::StartHandbrake);
		Enhanced->BindAction(HandbrakeAction, ETriggerEvent::Completed, this, &AMyProjectPawn::StopHandbrake);
		Enhanced->BindAction(LookAroundAction, ETriggerEvent::Triggered, this, &AMyProjectPawn::LookAround);
		Enhanced->BindAction(ToggleCameraAction, ETriggerEvent::Triggered, this, &AMyProjectPawn::ToggleCamera);
		Enhanced->BindAction(ResetVehicleAction, ETriggerEvent::Triggered, this, &AMyProjectPawn::ResetVehicle);
	}
	else
	{
		UE_LOG(LogTemplateVehicle, Error, TEXT("'%s' Missing Enhanced Input Component!"), *GetName());
	}
}

void AMyProjectPawn::Tick(float Delta)
{
	Super::Tick(Delta);

	const bool bOnGround = ChaosVehicleMovement->IsMovingOnGround();
	GetMesh()->SetAngularDamping(bOnGround ? 0.0f : 3.0f);

	float CameraYaw = BackSpringArm->GetRelativeRotation().Yaw;
	CameraYaw = FMath::FInterpTo(CameraYaw, 0.0f, Delta, 1.0f);
	BackSpringArm->SetRelativeRotation(FRotator(0.0f, CameraYaw, 0.0f));
}

void AMyProjectPawn::Steering(const FInputActionValue& Value)
{
	if (ChaosVehicleMovement)
		ChaosVehicleMovement->SetSteeringInput(Value.Get<float>());
}

void AMyProjectPawn::Throttle(const FInputActionValue& Value)
{
	if (ChaosVehicleMovement)
		ChaosVehicleMovement->SetThrottleInput(Value.Get<float>());
}

void AMyProjectPawn::Brake(const FInputActionValue& Value)
{
	if (ChaosVehicleMovement)
		ChaosVehicleMovement->SetBrakeInput(Value.Get<float>());
}

void AMyProjectPawn::StartBrake(const FInputActionValue&)
{
	BrakeLights(true);
}

void AMyProjectPawn::StopBrake(const FInputActionValue&)
{
	BrakeLights(false);
	if (ChaosVehicleMovement)
		ChaosVehicleMovement->SetBrakeInput(0.f);
}

void AMyProjectPawn::StartHandbrake(const FInputActionValue&)
{
	if (ChaosVehicleMovement)
		ChaosVehicleMovement->SetHandbrakeInput(true);
	BrakeLights(true);
}

void AMyProjectPawn::StopHandbrake(const FInputActionValue&)
{
	if (ChaosVehicleMovement)
		ChaosVehicleMovement->SetHandbrakeInput(false);
	BrakeLights(false);
}
void AMyProjectPawn::BrakeLights_Implementation(bool bBraking)
{
	// Şu anlık boş. Blueprint üzerinden ışıkları kontrol edebilirsin.
}
void AMyProjectPawn::LookAround(const FInputActionValue& Value)
{
	const float LookValue = Value.Get<float>();
	BackSpringArm->AddLocalRotation(FRotator(0.f, LookValue, 0.f));
}

void AMyProjectPawn::ToggleCamera(const FInputActionValue&)
{
	bFrontCameraActive = !bFrontCameraActive;
	FrontCamera->SetActive(bFrontCameraActive);
	BackCamera->SetActive(!bFrontCameraActive);
}

void AMyProjectPawn::ResetVehicle(const FInputActionValue&)
{
	const FVector ResetLocation = GetActorLocation() + FVector(0.f, 0.f, 50.f);
	FRotator ResetRotation = GetActorRotation();
	ResetRotation.Pitch = 0.f;
	ResetRotation.Roll = 0.f;

	SetActorTransform(FTransform(ResetRotation, ResetLocation), false, nullptr, ETeleportType::TeleportPhysics);

	GetMesh()->SetPhysicsAngularVelocityInDegrees(FVector::ZeroVector);
	GetMesh()->SetPhysicsLinearVelocity(FVector::ZeroVector);

	UE_LOG(LogTemplateVehicle, Warning, TEXT("Vehicle Reset"));

}