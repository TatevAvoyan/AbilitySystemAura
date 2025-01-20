// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Aura/Game/UI/Widget/AuraUserWidget.h"
#include "Aura/Game/UI/WidgetController/AuraWidgetController/AuraWidgetController.h"
#include "OverlayWidgetController.generated.h"

/**
 * Represents a row in a data table containing user interface widget data.
 * This structure is used to define UI elements associated with specific gameplay tags.
 */
USTRUCT()
struct FUIWidgetRow : public FTableRowBase
{
	GENERATED_BODY()

	/**
	 * A gameplay tag that serves as an identifier or category for the associated UI message.
	 * This variable is editable in the editor and is read-only in blueprints.
	 * Primarily used in FUIWidgetRow to tag specific rows with a unique identifier
	 * that can correspond to a specific type of UI message or action.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag MessageTag = FGameplayTag();

	/**
	 * A localized text variable used to store displayable text data.
	 * This variable is editable in the property editor and can be read-only within Blueprints.
	 * It is primarily designed for user-facing UI widgets to display specific messages or information.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Message = FText();

	/**
	 * A property that holds a class reference to a subclass of UAuraUserWidget.
	 * The widget represented by this property can be used to display messages
	 * or other UI elements within the context of a gameplay framework.
	 *
	 * This property is editable in both the editor and through blueprints,
	 * but can only be read in blueprints. The exact class must derive from UAuraUserWidget.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class UAuraUserWidget> MessageWidget;

	/**
	 * A UTexture2D object representing an image associated with the widget.
	 * This property is editable in the editor and read-only in Blueprints.
	 * It is initialized to nullptr and can be assigned a valid texture to display or use as needed.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* Image = nullptr;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangedSignature, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMessageWidgetRowSignature, FUIWidgetRow, Row);

/**
 * @class UOverlayWidgetController
 * @brief A widget controller for managing overlay widgets and their associated data and callbacks.
 *
 * The UOverlayWidgetController is a subclass of UAuraWidgetController designed for managing overlay-specific
 * UI elements and their interaction with gameplay systems. It facilitates broadcasting attribute changes,
 * binding callbacks, and retrieving widget data from a data table.
 */
UCLASS(BlueprintType, Blueprintable)
class AURA_API UOverlayWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()

public:
	/**
	 * Broadcasts the initial values of health and mana attributes to the corresponding delegates.
	 *
	 * This method retrieves the current and maximum values for health and mana from the associated attribute set
	 * and broadcasts these values to their respective event delegates. This ensures that all listeners
	 * are informed of the initial attribute values when the widget is initialized.
	 *
	 * Note:
	 * - The method assumes that the AttributeSet is correctly cast to `UAuraAttributeSet` and holds valid data.
	 * - It invokes the `BroadcastInitialValues` method from the parent class before handling specific attributes.
	 *
	 * Events triggered:
	 * - `OnHealthChanged` with the current health value.
	 * - `OnMaxHealthChanged` with the maximum health value.
	 * - `OnManaChanged` with the current mana value.
	 * - `OnMaxManaChanged` with the maximum mana value.
	 */
	virtual void BroadcastInitialValues() override;

	/**
	 * Binds callback functions to attribute value change delegates and effect asset tags for dependencies
	 * in the Ability System Component of the overlay widget controller.
	 *
	 * This function is responsible for monitoring changes in key gameplay attributes such as health,
	 * max health, mana, and max mana. It triggers corresponding delegate broadcasts whenever an
	 * attribute's value changes. Additionally, it processes gameplay tags for associated effects
	 * and triggers delegate broadcasts for newly matched UI widget rows based on gameplay tags.
	 *
	 * Delegates triggered:
	 * - OnHealthChanged: Broadcasts when the health attribute changes.
	 * - OnMaxHealthChanged: Broadcasts when the max health attribute changes.
	 * - OnManaChanged: Broadcasts when the mana attribute changes.
	 * - OnMaxManaChanged: Broadcasts when the max mana attribute changes.
	 * - MessageWidgetRowDelegate: Broadcasts a UI widget row based on matching gameplay tags.
	 */
	virtual void BindCallbacksToDependencies() override;

	/**
	 * Delegate to handle the event when the Health attribute value changes.
	 * This variable is bound to the Health attribute changes in the underlying system
	 * and broadcasts the updated value to any subscribed listeners.
	 *
	 * Category:
	 * - GAS|Attributes
	 *
	 * Usage:
	 * - Useful for responding to changes in the player's health, such as updating UI elements.
	 *
	 * BlueprintAssignable:
	 * - Enables binding this event in Blueprints, allowing handling of health changes in visual scripting workflows.
	 */
	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnAttributeChangedSignature OnHealthChanged;

	/**
	 * Delegate that is broadcast when the "Max Health" attribute value changes.
	 * This is used to notify listeners of any updates to the maximum health value
	 * of the associated character or entity. The delegate can be bound to
	 * Blueprint or C++ callbacks for custom behavior in response to the change.
	 *
	 * Category: GAS|Attributes
	 */
	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnAttributeChangedSignature OnMaxHealthChanged;

	/**
	 * Delegate triggered when the Mana attribute changes.
	 * This is part of the GAS (Gameplay Ability System) framework and is used to broadcast updates to the Mana value.
	 * Typically utilized for updating UI or other systems dependent on the Mana attribute.
	 *
	 * Category: GAS|Attributes
	 */
	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnAttributeChangedSignature OnManaChanged;

	/**
	 * A delegate used to broadcast notifications when the Max Mana attribute changes.
	 *
	 * This property is marked as BlueprintAssignable, allowing it to be bound and handled in
	 * Blueprints or C++ to respond to changes in the Max Mana attribute dynamically.
	 *
	 * The delegate uses FOnAttributeChangedSignature to pass relevant data, such as the updated value
	 * of Max Mana, enabling external systems or widgets to react accordingly.
	 *
	 * Category:
	 *   "GAS|Attributes"
	 */
	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnAttributeChangedSignature OnMaxManaChanged;

	/**
	 * @brief A delegate used to handle the broadcasting of message widget row data.
	 *
	 * This delegate is meant to signal updates or changes in data that pertain to a particular
	 * message widget row. It is primarily utilized to propagate information, such as gameplay
	 * events or updates tied to UI elements, to listening or bound components.
	 *
	 * The delegate is dynamically assignable in Blueprint and categorized under "GAS|Attributes".
	 */
	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FMessageWidgetRowSignature MessageWidgetRowDelegate;
protected:
	/**
	 * @brief A reference to a data table containing configurations for message widgets.
	 *
	 * This property is used to store a pointer to a UDataTable asset that holds information
	 * about different message widget entries. These entries are typically used to configure
	 * or parameterize the behavior and appearance of message widgets within the UI.
	 *
	 * The data table rows are expected to conform to a predefined structure that the widget
	 * can interpret and utilize for display or functionality purposes. It may be accessed
	 * to retrieve configuration data dynamically during runtime.
	 *
	 * @remark This property is marked as editable in defaults and readable in Blueprints.
	 *
	 * @category WidgetData
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WidgetData")
	TObjectPtr<UDataTable> MessageWidgetDataTable = nullptr;
	
	template<typename T>
	/**
	 * Retrieves a row from a data table corresponding to the specified gameplay tag.
	 * The template type T represents the expected structure of the row in the data table.
	 *
	 * @param DataTable The data table to search for the row.
	 * @param Tag The gameplay tag used to locate the desired row in the data table.
	 * @return A pointer to the row of type T if found, or nullptr if the row does not exist.
	 */
	T* GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag)
	{
		return DataTable->FindRow<T>(Tag.GetTagName(), TEXT(""));
	};
};
