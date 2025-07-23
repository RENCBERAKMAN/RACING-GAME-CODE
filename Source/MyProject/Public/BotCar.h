#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BotCar.generated.h"

UCLASS()
class MYPROJECT_API ABotCar : public APawn
{
	GENERATED_BODY()

public:
	ABotCar();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// ✅ Widget / Blueprint üzerinden atanabilir hedef noktası
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	AActor* TargetPoint;

	// ✅ Güncel hız vektörü
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	FVector CurrentVelocity;

	// ✅ Hızlanma değeri (birim/sn²)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float Acceleration = 500.f;

	// ✅ Maksimum hız limiti (birim/sn)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float MaxSpeed = 1200.f;

	// ✅ Blueprint tarafından çağrılabilir hız fonksiyonu
	UFUNCTION(BlueprintCallable, Category = "Speed")
	float GetSpeed() const;
};