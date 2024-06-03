// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Aura/Game/Characters/CharacterBase/AuraCharacterBase.h"
#include "Aura/Game/Interaction/EnemyInterface.h"
#include "AuraEnemy.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

	AAuraEnemy();

	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfo() override;

	void ToggleActorHighlighting(bool bIsHighlight) const;
	
	virtual void HighlightActor() override;

	virtual void UnHighlightActor() override;

private:
	void SetMeshes();

	UPROPERTY()
	TObjectPtr<class USkeletalMeshComponent> WeaponMesh = nullptr;

	UPROPERTY()
	TObjectPtr<class USkeletalMeshComponent> BodyMesh = nullptr;
};
