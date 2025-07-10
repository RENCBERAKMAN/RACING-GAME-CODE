#include "MyProjectSportsCar.h"
#include "MyProjectSportsWheelFront.h"
#include "MyProjectSportsWheelRear.h"
#include "ChaosWheeledVehicleMovementComponent.h"
#include "Components/SplineComponent.h"
#include "EngineUtils.h"
#include "DrawDebugHelpers.h"

AMyProjectSportsCar::AMyProjectSportsCar()
{
	PrimaryActorTick.bCanEverTick = true;

	UChaosWheeledVehicleMovementComponent* Movement = GetChaosVehicleMovement();
	if (!Movement) return;

	// ⚙️ Performans odaklı fizik ve sürüş
	Movement->ChassisHeight = 144.0f;
	Movement->DragCoefficient = 0.28f;
	Movement->bLegacyWheelFrictionPosition = true;
	Movement->WheelSetups.SetNum(4);

	Movement->WheelSetups[0].WheelClass = UMyProjectSportsWheelFront::StaticClass();
	Movement->WheelSetups[0].BoneName = FName("Phys_Wheel_FL");
	Movement->WheelSetups[1].WheelClass = UMyProjectSportsWheelFront::StaticClass();
	Movement->WheelSetups[1].BoneName = FName("Phys_Wheel_FR");
	Movement->WheelSetups[2].WheelClass = UMyProjectSportsWheelRear::StaticClass();
	Movement->WheelSetups[2].BoneName = FName("Phys_Wheel_BL");
	Movement->WheelSetups[3].WheelClass = UMyProjectSportsWheelRear::StaticClass();
	Movement->WheelSetups[3].BoneName = FName("Phys_Wheel_BR");

	// 🔋 Motor
	Movement->EngineSetup.MaxTorque = 1200.0f;
	Movement->EngineSetup.MaxRPM = 7500.0f;
	Movement->EngineSetup.EngineIdleRPM = 900.0f;

	
	Movement->TransmissionSetup.bUseAutomaticGears = true;
	Movement->TransmissionSetup.bUseAutoReverse = true;
	Movement->TransmissionSetup.FinalRatio = 2.8f;
	Movement->TransmissionSetup.ChangeUpRPM = 6800.0f;
	Movement->TransmissionSetup.ChangeDownRPM = 2400.0f;
	Movement->TransmissionSetup.GearChangeTime = 0.15f;
	Movement->TransmissionSetup.TransmissionEfficiency = 0.95f;
	Movement->TransmissionSetup.ForwardGearRatios = {
		5.00f, 2.60f, 1.80f, 1.35f, 1.0f, 0.82f, 0.68f
	};
	Movement->TransmissionSetup.ReverseGearRatios = { 4.04f };

	
	Movement->SteeringSetup.SteeringType = ESteeringType::Ackermann;
	Movement->SteeringSetup.AngleRatio = 0.65f;

	GetMesh()->SetCenterOfMass(FVector(0.f, 0.f, -23.f)); // Alt ağırlık merkezi
	GetMesh()->SetLinearDamping(0.1f);
	GetMesh()->SetAngularDamping(0.f);
}

void AMyProjectSportsCar::BeginPlay()
{
	Super::BeginPlay();
	LastVelocity = FVector::ZeroVector;
	SmoothedTarget = GetActorLocation();

	if (SplineActor)
	{
		SplineComp = SplineActor->FindComponentByClass<USplineComponent>();
	}
}

void AMyProjectSportsCar::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);
	TimeSinceLastLaneSwitch += DeltaTime;
	TotalRaceTime += DeltaTime;
	ObstacleAvoidCooldown = FMath::Max(ObstacleAvoidCooldown - DeltaTime, 0.f);

	if (!SplineComp) return;

	const float Speed = GetVelocity().Size();
	DistanceAlongSpline += Speed * DeltaTime;

	const float SplineLength = SplineComp->GetSplineLength();
	if (DistanceAlongSpline > SplineLength)
	{
		DistanceAlongSpline -= SplineLength;
		LapCount++;
	}

	// 📌 İlerideki spline hedefi
	const float ClosestKey = SplineComp->FindInputKeyClosestToWorldLocation(GetActorLocation());
	const float PositionAlongSpline = SplineComp->GetDistanceAlongSplineAtSplineInputKey(ClosestKey);
	const float LookAheadDistance = FMath::Clamp(Speed * 1.5f + 1000.f, 1500.f, 3000.f);
	const float TargetDist = FMath::Clamp(PositionAlongSpline + LookAheadDistance, 0.f, SplineLength - 100.f);

	FVector SplineTarget = SplineComp->GetLocationAtDistanceAlongSpline(TargetDist, ESplineCoordinateSpace::World);
	FVector RightVec = SplineComp->GetRightVectorAtDistanceAlongSpline(TargetDist, ESplineCoordinateSpace::World);
	FVector TargetLoc = SplineTarget + RightVec * LateralOffset;

	// Hedef yumuşat
	SmoothedTarget = FMath::VInterpTo(SmoothedTarget, TargetLoc, DeltaTime, 5.f);
	FVector DesiredDirection = (SmoothedTarget - GetActorLocation()).GetSafeNormal();

	// Sürüş
	float SteeringInput = FVector::CrossProduct(GetActorForwardVector(), DesiredDirection).Z;
	if (FMath::Abs(SteeringInput) < 0.06f)
		SteeringInput = 0.f;

	DebugSplineForward = DesiredDirection;

	DrawDebugLine(GetWorld(), GetActorLocation(), SmoothedTarget, FColor::Green, false, 0.f, 0, 3.f);
	DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + DesiredDirection * 500.f, FColor::Yellow, false, 0.f, 0, 2.f);

	float FinalThrottle = 1.f;
	float FinalBrake = 0.f;



	// 🚘 Önümüzdeki araçtan kaçınma & sollama
	for (TActorIterator<AMyProjectSportsCar> It(GetWorld()); It; ++It)
	{
		AMyProjectSportsCar* Other = *It;
		if (Other == this || !Other->SplineComp) continue;

		float MyDist = LapCount * SplineLength + DistanceAlongSpline;
		float OtherDist = Other->LapCount * SplineLength + Other->DistanceAlongSpline;
		float Gap = OtherDist - MyDist;

		// 💥 Engel öndeyse ve çok yakınsa → sollama başlat
		if (Gap > 0.f && Gap < MinFollowDistance)
		{
			if (ObstacleAvoidCooldown <= 0.f)
			{
				LateralOffset = (FMath::RandBool()) ? -300.f : 300.f;
				ObstacleAvoidCooldown = 2.f;
				UE_LOG(LogTemp, Warning, TEXT("Sollama manevrası başlatıldı."));
			}

			// ❌ Fren yok, sadece sollama pozisyonu alsın
			// ✅ Gaz kesilmesin, agresif sürüş devam etsin
		}
	}

	// 💥 Çarpışma tespiti → savrulmayı engelle
	FVector CurrentVelocity = GetVelocity();
	float VelocityChange = (CurrentVelocity - LastVelocity).Size();
	LastVelocity = CurrentVelocity;

	if (GetVelocity().Z > 400.f)
	{
		FVector Vel = GetMesh()->GetPhysicsLinearVelocity();
		Vel.Z = FMath::Clamp(Vel.Z, -100.f, 100.f);
		GetMesh()->SetPhysicsLinearVelocity(Vel);
	}

	// Sürekli güçlü damping uygula
	GetMesh()->SetLinearDamping(0.2f);
	GetMesh()->SetAngularDamping(1.0f);
	// 🔁 Ters dönüş engelleme → rotayı resetle
	FRotator Rot = GetActorRotation();
	if (FMath::Abs(Rot.Roll) > 25.f || FMath::Abs(Rot.Pitch) > 25.f)
	{
		FRotator UprightRotation = FRotator(0.f, Rot.Yaw, 0.f);
		SetActorRotation(UprightRotation, ETeleportType::TeleportPhysics);
		UE_LOG(LogTemp, Warning, TEXT("Araç dengesizdi, rotasyon sıfırlandı."));
	}

	FinalThrottle = FMath::Clamp(FinalThrottle, 1.0f, 1.0f); // Sabit 1
	FinalBrake = FMath::Clamp(FinalBrake, 0.0f, 0.0f);       // Sabit 0


	GetChaosVehicleMovement()->SetSteeringInput(FMath::Clamp(SteeringInput * 1.75f, -1.f, 1.f));
	GetChaosVehicleMovement()->SetThrottleInput(FinalThrottle);
	GetChaosVehicleMovement()->SetBrakeInput(FinalBrake);

	UE_LOG(LogTemp, Warning, TEXT("Steer: %.2f | Throttle: %.2f | Speed: %.0f | Lap: %d"),
		SteeringInput, FinalThrottle, Speed, LapCount);

}
