// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "AuraPlayerState.generated.h"

/**
 * AAuraPlayerState represents the PlayerState in the Aura project, which extends functionality
 * through the implementation of the Ability System Interface. It provides integration with an
 * Ability System Component and an associated Attribute Set for gameplay abilities and attributes.
 */
UCLASS()
class AURA_API AAuraPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

	/**
	 * @brief Default constructor for the AAuraPlayerState class.
	 *
	 * This constructor initializes the AbilitySystemComponent and AttributeSet, setting up
	 * the replicated AbilitySystemComponent with a mixed replication mode. It also sets the
	 * network update frequency for this player state instance.
	 *
	 * @return A new instance of the AAuraPlayerState class.
	 */
	AAuraPlayerState();

public:
	/**
	 * Retrieves the Ability System Component associated with this player state.
	 * This method implements the IAbilitySystemInterface by providing access to the specific AbilitySystemComponent.
	 *
	 * @return A pointer to the UAbilitySystemComponent instance associated with this player state. Returns nullptr if no Ability System Component is assigned.
	 */
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	/**
	 * Retrieves the properties that should be replicated for this actor.
	 * This method is used by Unreal Engine's networking system to determine
	 * which properties require replication.
	 *
	 * @param OutLifetimeProps An array that will be populated with the properties
	 *                         to be replicated.
	 */
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/**
	 * Retrieves the AttributeSet associated with this Player State.
	 *
	 * @return A pointer to the UAttributeSet instance belonging to this Player State.
	 */
	class UAttributeSet* GetAttributeSet() const { return AttributeSet; }

	/**
	 * @brief Retrieves the current level of the player.
	 *
	 * This function returns the player's level as stored in the internal Level property.
	 *
	 * @return The current level of the player.
	 */
	FORCEINLINE int32 GetPLayerLevel() const { return Level; }

protected:
	/**
	 * A reference to the Ability System Component associated with this PlayerState.
	 * This component is responsible for managing gameplay abilities and attributes.
	 * Primarily used in the context of gameplay ability systems, allowing the player
	 * to own and execute abilities and manage attributes tied to the character.
	 */
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UAbilitySystemComponent> AbilitySystemComponent = nullptr;

	/**
	 * A UObject pointer to an instance of the UAttributeSet class.
	 * Represents the attribute set associated with the player state.
	 * Used to define and manage gameplay attributes such as health, mana, strength, etc.
	 * Initialized to nullptr by default.
	 */
	UPROPERTY()
	TObjectPtr<class UAttributeSet> AttributeSet = nullptr;

private:
	/**
	 * Represents the player's current level.
	 *
	 * This variable is replicated across the network to ensure consistency
	 * in multiplayer scenarios and has its value updated on all clients
	 * when a change is detected. The `OnRep_Level` function is called
	 * whenever replication occurs to handle any custom behavior or logic
	 * triggered by the level change.
	 *
	 * Attributes:
	 * - `VisibleAnywhere`: Makes the variable visible in the editor and to other objects, but read-only.
	 * - `ReplicatedUsing=OnRep_Level`: Indicates that the variable is replicated and specifies
	 *   the function `OnRep_Level` to handle changes during replication.
	 *
	 * Default Value: 1
	 */
	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_Level)
	int32 Level = 1;

	/**
	 * Called whenever the replicated 'Level' property changes on the client.
	 *
	 * This function is triggered by the ReplicatedUsing specifier in the 'Level' property
	 * declaration, allowing the game logic to react when the 'Level' variable is updated.
	 *
	 * @param OldLevel The previous value of the 'Level' property before it was updated.
	 */
	UFUNCTION()
	void OnRep_Level(int32 OldLevel);
};
