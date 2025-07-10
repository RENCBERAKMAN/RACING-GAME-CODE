#include "BotCar.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/Engine.h" // GEngine için gerekli

ABotCar::ABotCar()
{
    PrimaryActorTick.bCanEverTick = true;

    // Ýsteðe baðlý: Hareket bileþeni eklemek istersen
    // MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));
}

void ABotCar::BeginPlay()
{
    Super::BeginPlay();
}

void ABotCar::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Tick çalýþýyor mu kontrolü
    GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, TEXT("Tick() çalýþýyor"));

    // TargetPoint atanmýþ mý?
    if (!TargetPoint)
    {
        GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("TargetPoint atanmadý!"));
        return;
    }

    FVector CurrentLocation = GetActorLocation();
    FVector TargetLocation = TargetPoint->GetActorLocation();

    FVector Direction = (TargetLocation - CurrentLocation).GetSafeNormal();

    // Yön vektörü kontrolü
    GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::Printf(TEXT("Direction: %s"), *Direction.ToString()));

    FVector DesiredVelocity = Direction * MaxSpeed;

    // Hýzlanma uygulamasý
    CurrentVelocity = FMath::VInterpConstantTo(CurrentVelocity, DesiredVelocity, DeltaTime, Acceleration);

    // Hýz vektörü kontrolü
    GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, FString::Printf(TEXT("Velocity: %s"), *CurrentVelocity.ToString()));

    FVector NewLocation = CurrentLocation + (CurrentVelocity * DeltaTime);

    // Yeni konum kontrolü
    GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Cyan, FString::Printf(TEXT("NewLocation: %s"), *NewLocation.ToString()));

    SetActorLocation(NewLocation);
}

void ABotCar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // Þu anlýk giriþ baðlamýyoruz, ama bu fonksiyon tanýmlý olmalý
}