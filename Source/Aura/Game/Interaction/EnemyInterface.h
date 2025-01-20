// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EnemyInterface.generated.h"

/**
 * @class UEnemyInterface
 * @brief An interface class providing the contract for entities that are considered enemies.
 *
 * This is a marker interface used to denote and allow specific implementation of methods
 * for objects designated as enemies within the game system.
 *
 * UEnemyInterface serves as a contract for classes that need to implement enemy-specific behavior.
 * Classes implementing this interface must adhere to its structure and define the required functionality.
 *
 * Use UEnemyInterface to provide a consistent API for interacting with enemy objects.
 */
UINTERFACE(MinimalAPI)
class UEnemyInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface for enemy actors, providing functionalities related to highlighting for interactable or visual feedback in the game.
 */
class AURA_API IEnemyInterface
{
	GENERATED_BODY()

public:
	/**
	 * @brief Abstract method to highlight the actor implementing the IEnemyInterface.
	 *
	 * Classes inheriting from IEnemyInterface should provide a specific implementation
	 * to visually indicate that the actor is highlighted, for example, to distinguish
	 * it during gameplay interactions.
	 *
	 * @note This method is expected to be implemented by any class inheriting
	 * the interface to provide the desired highlighting behavior.
	 */
	virtual void HighlightActor() = 0;

	/**
	 * @brief Virtual method to remove the highlight effect from an actor.
	 *
	 * This method should be implemented by any class inheriting from the IEnemyInterface.
	 * It is intended to remove any highlighting effect that was applied to the actor,
	 * signaling that the actor is no longer selected or targeted.
	 */
	virtual void UnHighlightActor() = 0;
};
