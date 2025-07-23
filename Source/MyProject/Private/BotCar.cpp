#include "BotCar.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/Engine.h"

ABotCar::ABotCar()
{
    PrimaryActorTick.bCanEverTick = true;
    // MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));
}

void ABotCar::BeginPlay()
{
    Super::BeginPlay();
}

void ABotCar::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    FVector CurrentLocation = GetActorLocation();
    FVector TargetLocation = TargetPoint->GetActorLocation();

    FVector Direction = (TargetLocation - CurrentLocation).GetSafeNormal();

    GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::Printf(TEXT("Direction: %s"), *Direction.ToString()));

    FVector DesiredVelocity = Direction * MaxSpeed;

    CurrentVelocity = FMath::VInterpConstantTo(CurrentVelocity, DesiredVelocity, DeltaTime, Acceleration);

    GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, FString::Printf(TEXT("Velocity: %s"), *CurrentVelocity.ToString()));

    FVector NewLocation = CurrentLocation + (CurrentVelocity * DeltaTime);

    GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Cyan, FString::Printf(TEXT("NewLocation: %s"), *NewLocation.ToString()));

    SetActorLocation(NewLocation);
}

void ABotCar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

// ✅ Hız bilgisini döndüren BlueprintCallable fonksiyon
float ABotCar::GetSpeed() const
{
    return CurrentVelocity.Size(); // Scalar (float) hız
}