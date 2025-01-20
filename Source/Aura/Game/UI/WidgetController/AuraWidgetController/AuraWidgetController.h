// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AuraWidgetController.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
class UAuraAttributeSet;

/**
 * @brief A data structure that holds parameters for initializing or configuring widget controllers.
 *
 * This structure is primarily used to encapsulate common references required for widget controllers,
 * such as player controller, player state, ability system component, and attribute set.
 */
USTRUCT(BlueprintType)
struct FWidgetControllerParams
{
	GENERATED_BODY()

	/**
	 * @brief Default constructor for the FWidgetControllerParams structure.
	 *
	 * Initializes an instance of the FWidgetControllerParams structure with default values.
	 *
	 * @return A default-initialized FWidgetControllerParams instance.
	 */
	FWidgetControllerParams() {}
	/**
	 * @brief Constructs a `FWidgetControllerParams` object with the provided player controller, player state,
	 * ability system component, and attribute set references.
	 *
	 * This constructor initializes the object with the specified parameters, which are commonly
	 * used for setting up or configuring widget controllers that interact with gameplay systems.
	 *
	 * @param PC Pointer to the player controller owning this widget controller.
	 * @param PS Pointer to the player state associated with this widget controller.
	 * @param ASC Pointer to the ability system component used for managing abilities.
	 * @param AS Pointer to the attribute set containing gameplay attributes.
	 * @return An initialized `FWidgetControllerParams` object.
	 */
	FWidgetControllerParams(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
	: PlayerController(PC), PlayerState(PS), AbilitySystemComponent(ASC), AttributeSet(AS) {}

	/**
	 * @brief A pointer to the player's controller instance.
	 *
	 * This variable is used to hold a reference to the player controller, typically required
	 * for managing and interacting with player-specific functionality within the game framework.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerController> PlayerController = nullptr;

	/**
	 * @brief A reference to the player state object associated with the widget controller.
	 *
	 * This variable is used to store and interact with the player's state in the game, such as their attributes,
	 * score, or other gameplay-related data. It is intended to establish a connection between the widget controller
	 * and the player's state information.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerState> PlayerState = nullptr;

	/**
	 * @brief A pointer to the Ability System Component associated with this widget controller.
	 *
	 * Used to handle gameplay abilities, manage attribute values, and interface with the ability system
	 * for executing logic related to abilities and gameplay effects.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;

	/**
	 * @brief A reference to an Attribute Set used by the Ability System for managing gameplay attributes.
	 *
	 * This variable holds a pointer to an Attribute Set, which defines and manages various gameplay
	 * attributes such as health, mana, or strength. It is part of the Ability System implementation
	 * and provides access to these attributes for use in widgets or controllers.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAttributeSet> AttributeSet = nullptr;
};

/**
 * @brief A class responsible for managing widget behavior and communication with gameplay systems.
 *
 * UAuraWidgetController serves as a base class for widget controllers that integrate with Unreal Engine's Gameplay Ability System (GAS).
 * It facilitates communication between UI widgets and game systems by providing references to key components such as the Player Controller,
 * Player State, Ability System Component, and Attribute Set, while also exposing functionality for managing initial values
 * and binding callbacks to dependencies.
 */
UCLASS()
class AURA_API UAuraWidgetController : public UObject
{
	GENERATED_BODY()

public:
	/**
	 * @brief Sets the parameters for the widget controller using the provided configuration.
	 *
	 * This function initializes the widget controller by setting its internal references (PlayerController,
	 * PlayerState, AbilitySystemComponent, and AttributeSet) based on the provided `FWidgetControllerParams` instance.
	 * These parameters are essential for the widget controller's operation, enabling it to interact with the associated
	 * gameplay systems and player-specific components.
	 *
	 * @param WCParams A structure containing the PlayerController, PlayerState, AbilitySystemComponent, and AttributeSet
	 * required to set up the widget controller.
	 */
	UFUNCTION(BlueprintCallable)
	void SetWidgetControlParams(const FWidgetControllerParams& WCParams);

	/**
	 * @brief Broadcasts the initial values of the widget controller's dependent properties.
	 *
	 * This method is used to propagate initial state or property values to any bound listeners or UI elements.
	 * Derived classes can override this function to implement specific behavior when broadcasting initial values.
	 */
	UFUNCTION(BlueprintCallable)
	virtual void BroadcastInitialValues();

	/**
	 * @brief Binds callbacks to dependencies required by the widget controller.
	 *
	 * This function establishes connections or associations between the widget controller
	 * and its external dependencies, such as the ability system component or attribute set.
	 * It is designed to ensure that events, updates, or functionality related to these
	 * dependencies propagate correctly to the widget controller.
	 */
	virtual void BindCallbacksToDependencies();
protected:
	/**
	 * @brief A reference to the player controller associated with this widget controller.
	 *
	 * This property is used to manage interactions and operations related to the player controller,
	 * which represents the interface between human input and in-game character actions.
	 */
	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<class APlayerController> PlayerController = nullptr;

	/**
	 * @brief A reference to the player state object associated with the widget controller.
	 *
	 * This property is used to store a pointer to the player state related to this widget controller.
	 * It allows interaction with the player's gameplay data, such as attributes and achievements,
	 * to facilitate display or updates within widgets.
	 */
	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<class APlayerState> PlayerState = nullptr;

	/**
	 * @brief A pointer to the Ability System Component used for handling gameplay abilities and related logic.
	 *
	 * This property provides access to the Ability System Component, enabling the widget controller to interface with gameplay abilities, manage attributes, and process gameplay effects.
	 */
	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<class UAbilitySystemComponent> AbilitySystemComponent = nullptr;

	/**
	 * @brief A reference to an Attribute Set associated with this widget controller.
	 *
	 * This variable provides access to gameplay attributes managed by the Ability System,
	 * enabling widgets or systems to display or interact with attributes such as health, mana, or other custom attributes.
	 */
	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<class UAttributeSet> AttributeSet = nullptr;
};
