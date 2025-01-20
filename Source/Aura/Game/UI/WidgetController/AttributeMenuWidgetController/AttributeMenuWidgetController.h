// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Game/UI/WidgetController/AuraWidgetController/AuraWidgetController.h"
#include "AttributeMenuWidgetController.generated.h"

struct FGameplayAttribute;
class UAttributeInfo;
struct FGameplayTag;
struct FAuraAttributeInfo;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeInfoSignature, const FAuraAttributeInfo&, Info);

/**
 * UAttributeMenuWidgetController handles delegation and broadcasting of gameplay attribute information
 * for use within the user interface, specifically focusing on menu widgets.
 * It interacts with gameplay attribute data managed by the Gameplay Ability System (GAS).
 */
UCLASS(BlueprintType, Blueprintable)
class AURA_API UAttributeMenuWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()

public:
	/**
	 * BindCallbacksToDependencies sets up the necessary connections between attribute changes in the associated
	 * Gameplay Ability System component and the Attribute Menu Widget Controller.
	 * This method ensures that attribute changes are tracked and corresponding attribute menu updates
	 * are broadcasted efficiently, leveraging gameplay tags and attributes defined in the associated Attribute Set.
	 */
	virtual void BindCallbacksToDependencies() override;

	/**
	 * BroadcastInitialValues initializes and broadcasts the initial state of gameplay attribute data from the associated
	 * AttributeSet to the user interface. It iterates through all attribute mappings in the TagsToAttributes container
	 * and invokes the broadcasting functionality using the defined AttributeMenuInfo format.
	 */
	virtual void BroadcastInitialValues() override;

	/**
	 * AttributeInfoDelegate is a broadcastable event designed for delegating gameplay attribute information.
	 * It is used within the AttributeMenuWidgetController to notify listeners of attribute updates, leveraging data
	 * compiled from the Gameplay Ability System (GAS). This delegate streamlines communication of relevant attribute
	 * details to the user interface or other subscribed systems.
	 */
	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FAttributeInfoSignature AttributeInfoDelegate;

protected:
	/**
	 * AttributeInfo holds the reference to a UAttributeInfo object that provides a mapping
	 * of gameplay attribute information, such as tags and related values, within the context
	 * of the Gameplay Ability System (GAS).
	 * It is used by the widget controller to retrieve and manage game attribute data, enabling
	 * components to interact with and broadcast relevant attribute changes to the UI.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UAttributeInfo> AttributeInfo = nullptr;

private:
	/**
	 * Broadcasts updated attribute information for a specific gameplay attribute tag.
	 * This method retrieves the attribute information associated with the provided tag,
	 * updates its value using the numeric value from the gameplay attribute,
	 * and then broadcasts the updated information to all registered listeners.
	 *
	 * @param AttributeTag The gameplay tag that identifies the attribute to be broadcasted.
	 * @param Attribute The gameplay attribute whose value will be used to update and broadcast the attribute information.
	 */
	void BroadcastAttributeMenuInfo(const FGameplayTag& AttributeTag, const FGameplayAttribute& Attribute) const;
};
