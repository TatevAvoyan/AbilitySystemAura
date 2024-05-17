// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraEffectActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"

// Sets default values
AAuraEffectActor::AAuraEffectActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	 SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
}

// Called when the game starts or when spawned
void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
}

void AAuraEffectActor::ApplyEffectToTarget(AActor* InTargetActor, TSubclassOf<UGameplayEffect> InGameplayEffectClass)
{
	if (InGameplayEffectClass)
	{
		if (UAbilitySystemComponent* L_TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InTargetActor);
			IsValid(L_TargetASC))
		{
			FGameplayEffectContextHandle EffectContextHandle = L_TargetASC->MakeEffectContext();
			EffectContextHandle.AddSourceObject(this);
			const FGameplayEffectSpecHandle EffectSpecHandle = L_TargetASC->MakeOutgoingSpec(
				InGameplayEffectClass, 1.f, EffectContextHandle);

			L_TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());

			Destroy();
		}
	}
}
