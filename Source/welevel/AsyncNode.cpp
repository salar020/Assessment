#include "AsyncNode.h"
#include "TargetActor.h"
#include "Kismet/GameplayStatics.h"

UAsyncNode* UAsyncNode::AsyncListenToBool(class ATargetActor* Target, class AActor* Listener)
{
    UAsyncNode* NewAsyncNode = NewObject<UAsyncNode>();
    NewAsyncNode->Target = Target;
    NewAsyncNode->Listener = Listener;
    NewAsyncNode->SetFlags(RF_StrongRefOnFrame);
    return NewAsyncNode;
}

void UAsyncNode::Activate()
{
    if (Target && Target->IsValidLowLevel())
    {
        
        Target->ED_OnTheBoolChange.AddDynamic(this, &UAsyncNode::OnTheBoolChange);

        UE_LOG(LogTemp, Warning, TEXT("UAsyncNode::Activate - Listening to ED_OnTheBoolChange on actor %s"), *Target->GetName());
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("UAsyncNode::Activate - Invalid actor"));
    }
}

void UAsyncNode::OnTheBoolChange()
{
    RemoveFromRoot();

    if (Listener && Listener->IsValidLowLevel())
    {
        UE_LOG(LogTemp, Warning, TEXT("Destroying listener actor %s"), *Listener->GetName());
        Listener->Destroy();
    }
}