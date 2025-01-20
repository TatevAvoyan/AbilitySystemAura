// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AuraInputConfig.h"
#include "EnhancedInputComponent.h"
#include "AuraInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:

	/**
	 * Binds ability actions from the input configuration to the respective functions for press, release, and hold actions.
	 *
	 * @param InputConfig A pointer to the input configuration containing ability input actions to be bound.
	 * @param Object The object instance on which the pressed, released, and held functions will be called.
	 * @param PressedFunc The function to call when an input action is pressed. Can be null.
	 * @param ReleasedFunc The function to call when an input action is released. Can be null.
	 * @param HeldFunc The function to call when an input action is held. Can be null.
	 */
	template<class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
	void BindAbilityActions(const UAuraInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc,
	                        ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc);
};

/**
 * Binds input actions specified in the input configuration to the provided object and action-handling functions.
 * This binds press, release, and hold functionality for each actionable input with a valid input tag.
 *
 * @param InputConfig A pointer to the input configuration specifying the actions and their corresponding tags.
 * @param Object The object instance on which the specified functions will be invoked.
 * @param PressedFunc The function to call when an input action is pressed. Can be null if press functionality is not required.
 * @param ReleasedFunc The function to call when an input action is released. Can be null if release functionality is not required.
 * @param HeldFunc The function to call when an input action is held. Can be null if hold functionality is not required.
 */
template <class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
/**
 * Binds ability input actions specified in the provided input configuration to the given object using the provided press, release, and hold functions.
 *
 * @param InputConfig A pointer to the input configuration object containing the ability input actions to bind. Must not be null.
 * @param Object The object on which the binding functions (PressedFunc, ReleasedFunc, HeldFunc) will be executed. Must not be null.
 * @param PressedFunc A function that gets executed when the associated input action is pressed. Can be null if no binding is required for presses.
 * @param ReleasedFunc A function that gets executed when the associated input action is released. Can be null if no binding is required for releases.
 * @param HeldFunc A function that gets executed when the associated input action is held. Can be null if no binding is required for holds.
 */
void UAuraInputComponent::BindAbilityActions(const UAuraInputConfig* InputConfig, UserClass* Object,
                                             PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc)
{
	check(InputConfig);

	for (const FAuraInputAction& Action : InputConfig->AbilityInputActions)
	{
		if (Action.InputAction && Action.InputTag.IsValid())
		{
			if (PressedFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Started, Object, PressedFunc, Action.InputTag);
			}

			if (ReleasedFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Completed, Object, ReleasedFunc, Action.InputTag);
			}

			if (HeldFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Triggered, Object, HeldFunc, Action.InputTag);
			}
		}
	}
}
