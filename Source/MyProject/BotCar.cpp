#include "BotCar.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/Engine.h" // GEngine i�in gerekli

ABotCar::ABotCar()
{
    PrimaryActorTick.bCanEverTick = true;

    // �ste�e ba�l�: Hareket bile�eni eklemek istersen
    // MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));
}

void ABotCar::BeginPlay()
{
    Super::BeginPlay();
}

void ABotCar::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Tick �al���yor mu kontrol�
    GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, TEXT("Tick() �al���yor"));

    // TargetPoint atanm�� m�?
    if (!TargetPoint)
    {
        GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("TargetPoint atanmad�!"));
        return;
    }

    FVector CurrentLocation = GetActorLocation();
    FVector TargetLocation = TargetPoint->GetActorLocation();

    FVector Direction = (TargetLocation - CurrentLocation).GetSafeNormal();

    // Y�n vekt�r� kontrol�
    GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::Printf(TEXT("Direction: %s"), *Direction.ToString()));

    FVector DesiredVelocity = Direction * MaxSpeed;

    // H�zlanma uygulamas�
    CurrentVelocity = FMath::VInterpConstantTo(CurrentVelocity, DesiredVelocity, DeltaTime, Acceleration);

    // H�z vekt�r� kontrol�
    GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, FString::Printf(TEXT("Velocity: %s"), *CurrentVelocity.ToString()));

    FVector NewLocation = CurrentLocation + (CurrentVelocity * DeltaTime);

    // Yeni konum kontrol�
    GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Cyan, FString::Printf(TEXT("NewLocation: %s"), *NewLocation.ToString()));

    SetActorLocation(NewLocation);
}

void ABotCar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // �u anl�k giri� ba�lam�yoruz, ama bu fonksiyon tan�ml� olmal�
}