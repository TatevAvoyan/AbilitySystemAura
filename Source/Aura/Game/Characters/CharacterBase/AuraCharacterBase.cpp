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

void AAuraCharacterBase::InitializePrimaryAttributes() const
{
	if (UAbilitySystemComponent* L_AbilitySystemComponent = GetAbilitySystemComponent();
		IsValid(L_AbilitySystemComponent) && IsValid(DefaultPrimaryAttributes))
	{
		const FGameplayEffectContextHandle ContextHandle = L_AbilitySystemComponent->MakeEffectContext();
		const FGameplayEffectSpecHandle SpecHandle = L_AbilitySystemComponent->MakeOutgoingSpec(DefaultPrimaryAttributes, 1.f, ContextHandle);

		L_AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(),  L_AbilitySystemComponent);
	}
}
