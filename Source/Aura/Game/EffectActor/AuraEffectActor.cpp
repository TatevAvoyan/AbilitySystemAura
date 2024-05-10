// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraEffectActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "Aura/Game/AbilitySystem/AttributeSet/AuraAttributeSet.h"
#include "Components/SphereComponent.h"

// Sets default values
AAuraEffectActor::AAuraEffectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");

	SphereComponent = CreateDefaultSubobject<USphereComponent>("Sphere");
	SphereComponent->SetupAttachment(Mesh);
}

// Called when the game starts or when spawned
void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();

	SphereComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &AAuraEffectActor::OnOverlap);
	SphereComponent->OnComponentEndOverlap.AddUniqueDynamic(this, &AAuraEffectActor::OnEndOverlap);
	
}

void AAuraEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// TODO: Change this to apply a Gameplay Effect. For now, using Const_Cast as a hack!
	if (const IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		const UAuraAttributeSet* L_AuraAttributeSet = Cast<UAuraAttributeSet>(
			ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UAuraAttributeSet::StaticClass()));

		UAuraAttributeSet* MutableAuraAttributeSet = const_cast<UAuraAttributeSet*>(L_AuraAttributeSet);

		if (bIsMana)
		{
			const float L_AddingValue = bIsAddMana ? L_AuraAttributeSet->GetMana() + 25.f : L_AuraAttributeSet->GetMana() - 25.f;
			MutableAuraAttributeSet->SetMana(L_AddingValue);
		}

		if (bIsHealth)
		{
			const float L_AddingValue = bIsAddHealth ? L_AuraAttributeSet->GetHealth() + 25.f : L_AuraAttributeSet->GetHealth() - 25.f;
			MutableAuraAttributeSet->SetHealth(L_AddingValue);
		}
		
		Destroy();
	}
}

void AAuraEffectActor::OnEndOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}
