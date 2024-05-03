// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "AuraCharacterBase.generated.h"

UCLASS()
class AURA_API AAuraCharacterBase : public ACharacter, public IAbilitySystemInterface 
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAuraCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	class UAttributeSet* GetAttributeSet() const { return AttributeSet; }

protected:
	// Components

	UPROPERTY(EditAnywhere, Category="Camera")
	TObjectPtr<class USpringArmComponent> SpringArmComponent = nullptr;

	UPROPERTY(EditAnywhere, Category="Camera")
	TObjectPtr<class UCameraComponent> CameraComponent = nullptr;
	
	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<class USkeletalMeshComponent> Weapon = nullptr;

	UPROPERTY()
	TObjectPtr<class UAbilitySystemComponent> AbilitySystemComponent = nullptr;

	UPROPERTY()
	TObjectPtr<class UAttributeSet> AttributeSet = nullptr;
};
