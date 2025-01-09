// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AuraAbilitySystemLibrary.generated.h"

/**
 * @brief UAttributeMenuWidgetController class.
 *
 * This class is part of the Aura Ability System and is responsible for managing the attribute menu widget.
 * It handles the interactions between the game's player controller, player state, ability system component,
 * and attribute set to facilitate the display and updates of attributes in the user interface.
 */
class UAttributeMenuWidgetController;

/**
 * @brief Controller class for managing the overlay widget in the Aura game.
 *
 * The UOverlayWidgetController class is responsible for handling the interactions
 * between the overlay widget and other game systems. It provides functionality
 * to update the widget based on game state and player actions.
 *
 * It's usually retrieved via the UAuraAbilitySystemLibrary and interacts
 * closely with AAuraHUD to define and update widget properties.
 */
class UOverlayWidgetController;

/**
 * @brief Library containing utility functions for interacting with Aura's ability system widgets.
 */
UCLASS()
class AURA_API UAuraAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	 * @brief Retrieves the Overlay Widget Controller.
	 *
	 * This function gets the Overlay Widget Controller for the specified world context.
	 * It retrieves the player controller from the world context, checks its validity,
	 * casts the HUD to AAuraHUD, and checks the validity of the player's state.
	 * If all checks pass, it retrieves the ability system component and attribute set,
	 * constructs a widget controller parameters struct, and gets the overlay widget
	 * controller from the HUD.
	 *
	 * @param WorldContextObject The context object for the world from which the player controller
	 *        and other components are retrieved.
	 * @return A pointer to the UOverlayWidgetController if successful, otherwise nullptr.
	 */
	UFUNCTION(BlueprintPure, Category="AuraAbilitySystemLibrary|WidgetController")
	static UOverlayWidgetController* GetOverlayWidgetController(const UObject* WorldContextObject);

	/**
	 * @brief Retrieves the Attribute Menu Widget Controller for the provided world context object.
	 *
	 * This function looks up the player controller, player state, ability system component, and attribute set associated
	 * with the provided world context object, and uses these to get the Attribute Menu Widget Controller from the player's HUD.
	 *
	 * @param WorldContextObject The context object that the world belongs to. This is typically a UObject derived class.
	 * @return UAttributeMenuWidgetController* The Attribute Menu Widget Controller instance if found, otherwise nullptr.
	 */
	UFUNCTION(BlueprintPure, Category="AuraAbilitySystemLibrary|WidgetController")
	static UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const UObject* WorldContextObject);
};
