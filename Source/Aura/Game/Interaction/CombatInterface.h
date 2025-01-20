// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatInterface.generated.h"

/**
 * UCombatInterface provides a contract or a guideline for classes to implement functionalities
 * that pertain to combat-related behaviors in the system. This interface ensures that all implementing
 * classes adhere to a standardized set of combat functionalities, enabling modular and extensible
 * interactions within the game's combat mechanics.
 *
 * Classes implementing this interface are expected to define their own logic for combat-related behaviors
 * as per the requirements of the interface.
 */
UINTERFACE(MinimalAPI)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * @class ICombatInterface
 * @brief An interface for defining combat-related functionality.
 *
 * This interface is intended to be inherited and implemented by classes
 * that require combat-related functionalities. It provides declarations
 * for methods related to combat, such as retrieving the player level.
 */
class AURA_API ICombatInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	/**
	 * Retrieves the player's level in the context of the combat interface.
	 *
	 * @return The integer level of the player.
	 */
	virtual int32 GetPlayerLevel();
};
