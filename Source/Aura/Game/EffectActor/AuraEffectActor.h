// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "GameFramework/Actor.h"
#include "AuraEffectActor.generated.h"

/**
 * Enum class defining the policy for applying effects.
 *
 * This enumeration is used to determine when an effect should be applied
 * based on the actor's interaction state.
 */
UENUM(BlueprintType)
enum class EEffectApplicationPolicy : uint8
{
	ApplyOnOverlap,
	ApplyOnEndOverlap,
	DoNotApply
};

/**
 * Enum representing the removal policy for an effect.
 * - RemoveOnEndOverlap: Ensures that the associated effect is removed when an overlap ends.
 * - DoNotRemove: Prevents the associated effect from being removed automatically.
 *
 * This enum is used to define how infinite gameplay effects are handled when the overlapping ends.
 */
UENUM(BlueprintType)
enum class EEffectRemovalPolicy : uint8
{
	RemoveOnEndOverlap,
	DoNotRemove
};

/**
 * AAuraEffectActor is a specialized actor for applying gameplay effects to other actors upon overlapping events.
 * It supports applying instant, duration, and infinite gameplay effects, with customizable application and removal policies.
 */
UCLASS()
class AURA_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()
	
public:
	/**
	 * Default constructor for the AAuraEffectActor class.
	 * Initializes the actor with default properties, such as disabling the Tick() function and setting up the root component.
	 *
	 * @return A newly constructed instance of the AAuraEffectActor class.
	 */
	AAuraEffectActor();

protected:
	/**
	 * Called when the game begins or when the actor is spawned.
	 * This method is overridden from the parent class to allow for any
	 * custom initialization logic specific to the AAuraEffectActor.
	 */
	virtual void BeginPlay() override;

	/**
	 * Handles the overlap event for the aura effect actor. This method determines
	 * whether a specific gameplay effect should be applied to the overlapping actor,
	 * based on the configured application policies for instant, duration, and
	 * infinite effects.
	 *
	 * @param TargetActor The actor that overlaps with this aura effect actor.
	 */
	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor* TargetActor);

	/**
	 * Handles the logic to manage gameplay effects when an actor stops overlapping with this aura effect actor.
	 * Depending on the defined application and removal policies, effects might be applied or removed for the target actor.
	 *
	 * @param TargetActor The actor that has stopped overlapping with this aura effect actor.
	 *                    Effects will be applied or removed on this actor as per the policies.
	 */
	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* TargetActor);

	/**
	 * Applies a specified gameplay effect to a target actor. The effect is instantiated from the provided gameplay effect class
	 * and applied through the target actor's Ability System Component, if it exists.
	 *
	 * @param InTargetActor The actor to which the gameplay effect will be applied. Must have a valid Ability System Component.
	 * @param InGameplayEffectClass The class of the gameplay effect to be applied. Should derive from UGameplayEffect.
	 */
	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* InTargetActor, TSubclassOf<class UGameplayEffect> InGameplayEffectClass);

	/**
	 * Determines whether the actor should be destroyed upon effect removal.
	 *
	 * If set to true, the actor will be destroyed when its associated effect is removed.
	 * If set to false, the actor will remain in the scene even after the effect is removed.
	 *
	 * This property allows customization of the actor's lifecycle in relation to applied effects.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	bool bDestroyOnEffectRemoval = false;

	/**
	 * A property that specifies the class of an instant gameplay effect to be applied.
	 * Instant gameplay effects are effects that are applied immediately upon execution
	 * with no duration, persistence, or overlapping behavior.
	 *
	 * This property is editable in the editor and exposed to blueprints as a read-only value.
	 * It belongs to the "Applied Effects" category and should be assigned a class derived
	 * from UGameplayEffect.
	 *
	 * Setting this property to a valid UGameplayEffect subclass allows the actor to
	 * apply the specified gameplay effect to a target as defined by the application logic.
	 * By default, this is set to nullptr, indicating no instant gameplay effect is defined.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	TSubclassOf<class UGameplayEffect> InstantGameplayEffectClass = nullptr;

	/**
	 * Specifies the application policy for instant gameplay effects.
	 * This variable determines the conditions under which an instant gameplay effect is applied to a target actor.
	 * The available policies are defined in the EEffectApplicationPolicy enumeration:
	 *   - ApplyOnOverlap: The effect is applied when there is an overlap with the target actor.
	 *   - ApplyOnEndOverlap: The effect is applied when the overlap with the target actor ends.
	 *   - DoNotApply: The effect is not applied under any condition.
	 * This variable is configurable in the editor and marked as read-only for Blueprints.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	EEffectApplicationPolicy InstantEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	/**
	 * A class reference to a specific type of UGameplayEffect that represents a gameplay effect with a defined duration.
	 * This property is editable within the editor and can be accessed in Blueprint scripts.
	 * It is used to specify and associate a duration-based gameplay effect with this actor.
	 *
	 * Category: "Applied Effects"
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	TSubclassOf<class UGameplayEffect> DurationGameplayEffectClass = nullptr;

	/**
	 * Defines the application policy for effects with a duration.
	 *
	 * This property determines how and when a duration-based gameplay effect
	 * should be applied to an overlapping actor. The available policies are:
	 *
	 * - ApplyOnOverlap: The effect is applied when an actor begins overlapping.
	 * - ApplyOnEndOverlap: The effect is applied when an actor ends overlapping.
	 * - DoNotApply: The effect is not applied under any circumstances.
	 *
	 * This setting enables dynamic control over the application behavior of
	 * gameplay effects tied to specific actor interactions.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	EEffectApplicationPolicy DurationEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	/**
	 * Specifies the class of an infinite-duration gameplay effect that can be applied to target actors.
	 * This effect persists indefinitely until explicitly removed or based on defined removal policies.
	 * Set to nullptr by default, allowing it to remain unassigned if not required.
	 *
	 * - Configurable via Editor and Blueprint for additional flexibility during design-time.
	 * - Categorized under "Applied Effects" for organizational purposes within the editor.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	TSubclassOf<class UGameplayEffect> InfiniteGameplayEffectClass = nullptr;

	/**
	 * Determines the application policy for infinite (permanent) gameplay effects.
	 *
	 * This variable controls how and when an infinite gameplay effect should be applied to a target actor.
	 * It uses the EEffectApplicationPolicy enum, which provides the following options:
	 * - ApplyOnOverlap: The effect is applied when the actor begins overlapping with the effect source.
	 * - ApplyOnEndOverlap: The effect is applied when the actor ends overlapping with the effect source.
	 * - DoNotApply: The effect will not be applied in any case.
	 *
	 * InfiniteEffectApplicationPolicy primarily impacts the behavior of OnOverlap and OnEndOverlap
	 * functions to decide whether the associated infinite gameplay effect should be applied.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	EEffectApplicationPolicy InfiniteEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	/**
	 * Specifies the removal policy for infinite gameplay effects applied by the Aura Effect Actor.
	 *
	 * This variable determines whether infinite effects applied to actors will be removed automatically when they stop
	 * overlapping with the Aura Effect Actor. By default, the policy is set to `RemoveOnEndOverlap`, which removes
	 * the infinite effect when the overlap ends. This can be adjusted to define alternate removal policies depending
	 * on game logic and desired behavior.
	 *
	 * The removal policies are defined by the EEffectRemovalPolicy enumeration:
	 * - `RemoveOnEndOverlap`: Removes the effect when the overlap ends.
	 * - `DoNotRemove`: Effect remains active even after the overlap ends.
	 *
	 * Applicable to infinite gameplay effects specified by the `InfiniteGameplayEffectClass` or similar logic
	 * utilizing infinite-duration effects. Behavior may depend on other policies or settings in the associated
	 * `AAuraEffectActor`.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	EEffectRemovalPolicy InfiniteEffectRemovalPolicy = EEffectRemovalPolicy::RemoveOnEndOverlap;

	/**
	 * A map that tracks active gameplay effect handles and their associated ability system components.
	 * It is used to manage the application and removal of gameplay effects, particularly infinite effects
	 * with specific removal policies.
	 *
	 * Key: An FActiveGameplayEffectHandle representing the unique handle for an active gameplay effect.
	 * Value: A UAbilitySystemComponent pointer associated with the actor that the effect is applied to.
	 *
	 * This variable is primarily used in:
	 * - Applying gameplay effects to target actors and tracking their active state.
	 * - Removing gameplay effects when necessary, such as during overlap events.
	 */
	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*> ActiveEffectHandles;

	/**
	 * The level of the actor used to determine the strength or scaling of gameplay effects applied by this actor.
	 * This value is used in generating gameplay effect specifications to influence their attributes, calculations,
	 * or impact.
	 *
	 * Category: "Applied Effects"
	 * Editable in the editor and read-only in Blueprints.
	 * Default value is 1.f.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	float ActorLevel = 1.f;
};
