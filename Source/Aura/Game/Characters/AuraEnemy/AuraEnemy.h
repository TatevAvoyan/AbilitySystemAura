// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Aura/Game/Characters/CharacterBase/AuraCharacterBase.h"
#include "Aura/Game/Interaction/EnemyInterface.h"
#include "AuraEnemy.generated.h"

/**
 * Represents an enemy character in the Aura game, inheriting base character functionalities and implementing enemy-specific behavior.
 */
UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()
public:
	/**
	 * Default constructor for the AAuraEnemy class.
	 *
	 * Initializes the enemy character by setting up the mesh collision responses,
	 * creating the ability system component, and attribute set, and configuring
	 * their replication settings.
	 *
	 * @return An instance of AAuraEnemy with the default property configurations.
	 */
	AAuraEnemy();

	/**
	 * Toggles the highlighting effect on the actor's meshes by enabling or disabling the custom depth rendering
	 * and adjusting the stencil value for custom depth rendering.
	 *
	 * @param bIsHighlight Specifies whether to enable or disable highlighting. Pass true to enable highlighting, or false to disable it.
	 */
	void ToggleActorHighlighting(bool bIsHighlight) const;

	/**
	 * Configures the body and weapon mesh components for the AuraEnemy.
	 * This method assigns the appropriate mesh components to be used for the enemy's body and weapon.
	 */
	void SetMeshes();

	/**
	 * Enables the highlighting effect on the enemy actor by activating custom depth rendering.
	 * This visual effect is commonly used to emphasize the actor for gameplay or UI purposes.
	 */
	virtual void HighlightActor() override;

	/**
	 * Disables the highlighting effect on the actor's meshes by turning off custom depth rendering.
	 */
	virtual void UnHighlightActor() override;

	/** Combat Interface */

	/**
	 * Retrieves the current level of the player, which represents their progression and determines interactions with game elements.
	 *
	 * @return The player's current level as an integer.
	 */
	virtual int32 GetPlayerLevel() override;
protected:

	/**
	 * Overrides the base class BeginPlay method to initialize the enemy character.
	 * Sets up the enemy-specific meshes and initializes the ability system actor information.
	 */
	virtual void BeginPlay() override;

	/**
	 * Initializes the ability system component by associating it with the current enemy instance.
	 * Sets up ability actor information required for the ability system functionality and triggers
	 * any specific initialization procedures in the enemy's ability system component.
	 */
	virtual void InitAbilityActorInfo() override;

	/**
	 * Represents the character's level in the game, used to determine progression, abilities, scaling, or interactions with game elements.
	 * Configurable in the editor and read-only within Blueprints.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	int32 Level = 1;

	/**
	 * Represents the skeletal mesh component used for the enemy's weapon.
	 * This mesh defines the visual representation and animations associated with the equipped weapon.
	 */
	UPROPERTY()
	TObjectPtr<class USkeletalMeshComponent> WeaponMesh = nullptr;

	/**
	 * Represents the skeletal mesh component used for the enemy's body.
	 * This mesh defines the visual representation and animations associated with the enemy character's body.
	 */
	UPROPERTY()
	TObjectPtr<class USkeletalMeshComponent> BodyMesh = nullptr;
};
