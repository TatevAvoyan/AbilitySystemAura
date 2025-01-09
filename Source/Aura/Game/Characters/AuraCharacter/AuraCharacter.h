// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Aura/Game/Characters/CharacterBase/AuraCharacterBase.h"
#include "AuraCharacter.generated.h"

/**
 * @brief AAuraCharacter class serves as the main character class in the Aura game,
 * derived from the AAuraCharacterBase and implements custom functionalities.
 */
UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()

public:
	/**
	 * @brief Default constructor for AAuraCharacter.
	 *
	 * @note This constructor initializes the character's movement component to orient rotation to movement,
	 *       sets the rotation rate, constrains the character to a plane, and sets snapping to the plane at start.
	 *       Additionally, it disables the use of the controller's rotation for pitch, roll, and yaw.
	 */
	AAuraCharacter();

	/**
	 * @brief Called when the character is possessed by a new controller.
	 *
	 * This function is overridden to initialize the ability actor info
	 * for the server and add character-specific abilities when the character
	 * is possessed by a new controller.
	 *
	 * @param NewController The new controller that is possessing this character.
	 */
	virtual void PossessedBy(AController* NewController) override;

	/**
	 * @brief Handler for when the player state is replicated.
	 *
	 * This function is called when the player state is replicated from the server to the client.
	 * It initializes the ability actor information for the client side, ensuring that the ability system
	 * and attribute set are properly set up and ready for use.
	 */
	virtual void OnRep_PlayerState() override;

	/**
	 * @brief Initializes the ability actor information for the character.
	 *
	 * This method sets up the ability system component and attribute set for the character
	 * by retrieving them from the associated player state. It ensures that the ability actor
	 * information is properly initialized both on the server and client sides. Additionally,
	 * it initializes the HUD overlay with relevant ability system and attribute details.
	 */
	virtual void InitAbilityActorInfo() override;

	/**
	 * @brief Retrieves the player's level.
	 *
	 * This function returns the current level of the player by accessing the player state.
	 *
	 * @return The current level of the player as an integer.
	 */
	virtual int32 GetPlayerLevel() override;
	/** end Combat Interface */
};
