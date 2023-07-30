#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "AsyncNode.generated.h"

UCLASS()
class WELEVEL_API UAsyncNode : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Welevel")
        static UAsyncNode* AsyncListenToBool(class ATargetActor* Target, class AActor* Listener);

    virtual void Activate() override;

    UFUNCTION()
        void OnTheBoolChange();

private:
    UPROPERTY()
        class ATargetActor* Target;
    class AActor* Listener;
};