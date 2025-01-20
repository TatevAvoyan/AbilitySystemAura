// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuraUserWidget.generated.h"

/**
 * @class UAuraUserWidget
 * @brief A base class for Aura user widgets, providing functionality to set and handle the widget controller.
 *
 * This class extends UUserWidget and introduces a widget controller that can be dynamically assigned
 * and used for updating widget behavior at runtime. Additionally, it provides an event for derived
 * widgets to respond to the assignment of the widget controller.
 */
UCLASS()
class AURA_API UAuraUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/**
	 * A read-only property that holds a reference to a UObject serving as the WidgetController for this user widget.
	 * This property is intended to store the widget's controller, which may manage or interact with UI logic.
	 * It is initialized to nullptr and is expected to be set using the SetWidgetController method.
	 */
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController = nullptr;

	/**
	 * Sets the widget controller for the user widget and triggers the WidgetControllerSet event.
	 *
	 * @param InWidgetController The UObject instance to be set as the widget controller for this widget.
	 */
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);

protected:
	/**
	 * Blueprint implementable event that is triggered after the WidgetController
	 * property has been set. Can be implemented in Blueprint to define custom
	 * behavior upon the assignment of WidgetController.
	 */
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
};
