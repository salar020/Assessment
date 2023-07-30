#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Net/UnrealNetwork.h"
#include "TargetActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTheBoolChange);

UCLASS()
class WELEVEL_API ATargetActor : public AActor
{
    GENERATED_BODY()

public:
    ATargetActor();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated, Category = "Custom")
        bool TheBool;

    UPROPERTY(BlueprintAssignable, Category = "Custom")
        FOnTheBoolChange ED_OnTheBoolChange;

    UFUNCTION(BlueprintCallable, Category = "Custom")
        void SetTheBool(bool NewValue);

    UFUNCTION(NetMulticast, Reliable)
        void Multicast_DestroyActor();

    UFUNCTION(Server, Reliable, WithValidation)
        void Server_DestroyActor();

protected:
    UFUNCTION()
        void OnRep_TheBool();

    UFUNCTION(Server, Reliable, WithValidation)
        void Server_SetTheBool(bool NewValue);

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};