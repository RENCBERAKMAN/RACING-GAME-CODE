#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RaceUIBase.generated.h"

class UTextBlock;
class UProgressBar;

UCLASS()
class MYPROJECT_API URaceUIBase : public UUserWidget
{
    GENERATED_BODY()

public:
    // 🕹️ Blueprint'teki UI öğeleriyle eşleşecek
    UPROPERTY(meta = (BindWidget))
    UTextBlock* SpeedText;

    UPROPERTY(meta = (BindWidget))
    UProgressBar* SpeedBar;
};