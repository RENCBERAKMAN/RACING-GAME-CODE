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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	AActor* TargetPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	FVector CurrentVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float Acceleration = 500.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float MaxSpeed = 1200.f;
};
