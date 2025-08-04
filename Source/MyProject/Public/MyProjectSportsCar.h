#pragma once

#include "CoreMinimal.h"
#include "MyProjectPawn.h"
#include "Components/SplineComponent.h"
#include "Components/SpotLightComponent.h"
#include "MyProjectSportsCar.generated.h"  

UCLASS()
class MYPROJECT_API AMyProjectSportsCar : public AMyProjectPawn
{
	GENERATED_BODY()

public:
	AMyProjectSportsCar();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	// Input bileşeni override'u (buraya eklemen lazım)
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// UI üzerinden manuel kontrol fonksiyonları
	UFUNCTION(BlueprintCallable)
	void ApplyThrottle(float Value);

	UFUNCTION(BlueprintCallable)
	void ApplySteer(float Value);

	UFUNCTION(BlueprintCallable)
	void ApplyBrake(bool bIsBraking);

	// Fren input fonksiyonları
	void OnBrakePressed();
	void OnBrakeReleased();

	// Spline atama fonksiyonu
	UFUNCTION(BlueprintCallable)
	void AssignSpline(AActor* InSplineActor);

	// Farlar
	UPROPERTY(VisibleAnywhere)
	USpotLightComponent* BotLeftHeadlight;

	UPROPERTY(VisibleAnywhere)
	USpotLightComponent* BotRightHeadlight;

	// Spline yolu referansı
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	AActor* SplineActor;

	// Spline bileşeni
	UPROPERTY(VisibleInstanceOnly, Category = "AI")
	USplineComponent* SplineComp;

	// Spline üzerindeki konum
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float DistanceAlongSpline = 0.f;

	// Hedef spline ilerleme hızı (başlangıç referansı)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float SplineSpeed = 1000.f;

	// Yan şerit ofseti
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float LateralOffset = 0.f;

	// Takip ve sollama zekası
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float Aggression = 1.f;

	// Ara mesafe kontrolü
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float MinFollowDistance = 400.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float LaneSwitchCooldown = 1.5f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	float TimeSinceLastLaneSwitch = 0.f;

	// Tur verisi
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	int32 LapCount = 0;

	// Yarış başlangıç süresi takip
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Race")
	float TotalRaceTime = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Race")
	float RaceStartDelay = 2.f;

	// Debug spline yönü
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI Debug")
	FVector DebugSplineForward = FVector::ForwardVector;

	// Fiziksel denge ve sollama için ek değişkenler
	FVector LastVelocity = FVector::ZeroVector;
	FVector SmoothedTarget = FVector::ZeroVector;
	float ObstacleAvoidCooldown = 0.f;
};
