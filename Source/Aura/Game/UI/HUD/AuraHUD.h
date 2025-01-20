// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AuraHUD.generated.h"

class UAttributeMenuWidgetController;
class UAttributeSet;
class UAbilitySystemComponent;
class UOverlayWidgetController;
struct FWidgetControllerParams;
/**
 * @class AAuraHUD
 * @brief Represents the custom HUD for the Aura game, responsible for managing and initializing UI elements such as overlays and attribute menus.
 *
 * This class extends AHUD and is designed to manage specific widgets and their respective controllers,
 * facilitating interaction between gameplay elements and the user interface.
 */
UCLASS()
class AURA_API AAuraHUD : public AHUD
{
	GENERATED_BODY()

public:
	/**
	 * @brief Retrieves and initializes the Overlay Widget Controller for the HUD.
	 *
	 * This method ensures the Overlay Widget Controller is valid and configured with the provided parameters.
	 * If the controller does not exist, a new instance is created based on the configured class type,
	 * and its parameters and callbacks are initialized.
	 *
	 * @param WCParams A structure containing parameters required to initialize the Widget Controller,
	 * such as PlayerController, PlayerState, AbilitySystemComponent, and AttributeSet.
	 * @return A pointer to the initialized UOverlayWidgetController instance.
	 */
	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);
	/**
	 * @brief Retrieves or initializes the Attribute Menu Widget Controller used to manage interactions with attribute-related UI elements.
	 *
	 * This method checks if the Attribute Menu Widget Controller is valid. If not, it creates a new instance of the controller,
	 * initializes it with the provided widget controller parameters, and binds any relevant callbacks to dependencies.
	 *
	 * @param WCParams A struct containing references to essential gameplay components such as the Player Controller, Player State,
	 *                 Ability System Component, and Attribute Set, which are required for initializing the controller.
	 * @return A pointer to the initialized or existing UAttributeMenuWidgetController.
	 */
	UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const FWidgetControllerParams& WCParams);

	/**
	 * @brief Initializes the overlay UI for the game, incorporating player state, ability system, and attribute data.
	 *
	 * This method creates and sets up the user interface overlay widget, linking it to the appropriate widget controller.
	 * The overlay widget is responsible for displaying HUD elements such as player abilities, health, or other gameplay-specific data.
	 *
	 * @param PC A pointer to the player's controller, providing input and gameplay control reference.
	 * @param PS A pointer to the player's state, used for maintaining persistent gameplay information.
	 * @param ASC A pointer to the player's ability system component, facilitating interaction with abilities and effects.
	 * @param AS A pointer to the player's attribute set, containing gameplay-related attributes like health, mana, and stamina.
	 */
	UFUNCTION()
	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

private:
	/**
	 * @brief Holds a reference to the player's overlay widget used to display dynamic HUD elements.
	 *
	 * This widget is responsible for rendering real-time information to the player, such as health,
	 * mana, and other status indicators. Managed by the OverlayWidgetController.
	 */
	UPROPERTY()
	TObjectPtr<class UAuraUserWidget> OverlayWidget = nullptr;

	/**
	 * @brief Represents the class type for the overlay widget used in the HUD.
	 *
	 * This property defines the blueprint or class type that will be instantiated to display
	 * the overlay widget as part of the game's user interface. It enables customization
	 * of the overlay interface through assignment of different widget classes.
	 */
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UAuraUserWidget> OverlayWidgetClass = nullptr;

	/**
	 * @var TObjectPtr<UOverlayWidgetController> OverlayWidgetController
	 * @brief Manages the overlay widget functionality and its interaction logic within the user interface.
	 *
	 * This variable holds a reference to the instance of UOverlayWidgetController responsible for handling
	 * overlay-related widget behaviors, including binding callbacks, broadcasting initial values, and processing
	 * attribute-related events like changes to health or mana.
	 */
	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController = nullptr;

	/**
	 * @brief Represents the class reference for creating OverlayWidgetController instances.
	 *
	 * This property allows the selection of a specific UOverlayWidgetController subclass in the editor
	 * that will define the behavior and interface logic for the overlay widget.
	 * Used to dynamically create and initialize the overlay controller during gameplay.
	 */
	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass = nullptr;

	/**
	 * @property AttributeMenuWidgetController
	 * @brief Holds a reference to the Attribute Menu Widget Controller instance, which manages the attribute menu UI logic and interactions.
	 *
	 * This property is used to initialize and retrieve the attribute menu widget controller responsible
	 * for handling callbacks and broadcasting attribute-related data within the HUD. The instance is
	 * created dynamically if not already instantiated.
	 */
	UPROPERTY()
	TObjectPtr<UAttributeMenuWidgetController> AttributeMenuWidgetController = nullptr;

	/**
	 * @brief Holds a reference to the class type used for creating the Attribute Menu Widget Controller.
	 *
	 * This property allows designers to specify a blueprint class or scriptable variant of the Attribute Menu Widget Controller
	 * within the editor. It serves as a template for dynamically instantiating the controller responsible for managing
	 * the attribute menu widget's behavior and functionality.
	 */
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAttributeMenuWidgetController> AttributeMenuWidgetControllerClass = nullptr;
};
