// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraCharacterBase.h"

#include "AbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AAuraCharacterBase::AAuraCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArmComponent->SetupAttachment(GetMesh());

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComponent->SetupAttachment(SpringArmComponent);

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

UAbilitySystemComponent* AAuraCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AAuraCharacterBase::InitAbilityActorInfo()
{
}

void AAuraCharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const
{
	if (UAbilitySystemComponent* L_AbilitySystemComponent = GetAbilitySystemComponent();
		IsValid(L_AbilitySystemComponent) && IsValid(GameplayEffectClass))
	{
		FGameplayEffectContextHandle ContextHandle = L_AbilitySystemComponent->MakeEffectContext();
		ContextHandle.AddSourceObject(this);
		const FGameplayEffectSpecHandle SpecHandle = L_AbilitySystemComponent->MakeOutgoingSpec(GameplayEffectClass, Level, ContextHandle);

		L_AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(),  L_AbilitySystemComponent);
	}
}

void AAuraCharacterBase::InitializeDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultPrimaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultSecondaryAttributes, 1.f);
}
