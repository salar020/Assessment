#include "TargetActor.h"
#include "Kismet/GameplayStatics.h"

ATargetActor::ATargetActor()
{
    
    TheBool = false;

    
    SetReplicates(true);
    SetReplicateMovement(false);
}

void ATargetActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    
    DOREPLIFETIME(ATargetActor, TheBool);
}

void ATargetActor::OnRep_TheBool()
{
   

    UE_LOG(LogTemp, Warning, TEXT("OnRep_TheBool called. TheBool: %s"), TheBool ? TEXT("true") : TEXT("false"));

    
    Server_DestroyActor();
}

void ATargetActor::SetTheBool(bool NewValue)
{
    if (GetLocalRole() == ROLE_Authority)
    {
       
        if (TheBool != NewValue)
        {
            Server_SetTheBool(NewValue);
        }
    }
    else
    {
       
        if (TheBool != NewValue)
        {
            bool bOldValue = TheBool; 
            TheBool = NewValue;

            
            if (bOldValue != TheBool)
            {
                OnRep_TheBool();
            }
        }
    }
}

void ATargetActor::Server_SetTheBool_Implementation(bool NewValue)
{
    

    TheBool = NewValue;

    UE_LOG(LogTemp, Warning, TEXT("Server_SetTheBool called. TheBool set to: %s"), TheBool ? TEXT("true") : TEXT("false"));

    
    OnRep_TheBool();
}

bool ATargetActor::Server_SetTheBool_Validate(bool NewValue)
{
    
    return true;
}

void ATargetActor::Multicast_DestroyActor_Implementation()
{
    ED_OnTheBoolChange.Broadcast();
    
}

bool ATargetActor::Server_DestroyActor_Validate()
{
    return true;
}

void ATargetActor::Server_DestroyActor_Implementation()
{
    
        Multicast_DestroyActor();
    
}