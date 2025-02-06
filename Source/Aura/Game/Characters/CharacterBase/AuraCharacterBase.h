// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Aura/Game/Interaction/CombatInterface.h"
#include "AuraCharacterBase.generated.h"

/**
 * @class UGameplayAbility
 * @brief Base class for defining gameplay abilities in Unreal Engine.
 *
 * UGameplayAbility serves as the foundation for creating various gameplay abilities, such as spells, attacks,
 * or any other functionality that a character can perform. It integrates tightly with Unreal Engine's ability
 * system and leverages features such as gameplay tags, input bindings, and effects.
 *
 * This class can be extended to define custom abilities with specialized behavior, input activation methods,
 * and application logic. It is commonly used in conjunction with AbilitySystemComponent to manage gameplay
 * abilities dynamically at runtime.
 *
 * In a derived class, you can:
 *   - Define customized logic for gameplay effects.
 *   - Bind input through gameplay tags for user interaction.
 *   - Specify conditions or costs for activation.
 *   - Implement cooldowns and resource management.
 *
 * UGameplayAbility is central to Unreal's gameplay framework and supports a modular, extensible system
 * for creating diverse gameplay behaviors.
 */
class UGameplayAbility;

/**
 * AAuraCharacterBase is the base character class for the Aura game framework.
 * It extends ACharacter and implements IAbilitySystemInterface and ICombatInterface,
 * enabling the integration of the Ability System and combat-related functionalities.
 */
UCLASS()
class AURA_API AAuraCharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	/**
	 * Default constructor for the AAuraCharacterBase class.
	 * Initializes components such as the SpringArmComponent, CameraComponent,
	 * and Weapon, and sets their respective attachments.
	 * Configures default settings like disabling actor ticking and disabling collision
	 * for the Weapon component.
	 *
	 * @return A new instance of the AAuraCharacterBase class.
	 */
	AAuraCharacterBase();

protected:
	/**
	 * Called when the game starts or when the character is spawned.
	 *
	 * This method is an override of the AActor's `BeginPlay` function.
	 * It serves as the entry point for initializing any game-related logic
	 * specific to the Aura character after the character is instantiated
	 * and just before gameplay begins. This allows for any setup that
	 * requires the character and its components to exist in the game world.
	 */
	virtual void BeginPlay() override;

	/**
	 * Retrieves the Ability System Component associated with this character.
	 *
	 * @return A pointer to the UAbilitySystemComponent instance if available, or nullptr if not valid.
	 */
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	/**
	 * Retrieves the AttributeSet associated with the character.
	 *
	 * @return A pointer to the UAttributeSet instance associated with the character.
	 */
	class UAttributeSet* GetAttributeSet() const { return AttributeSet; }

protected:
	/**
	 * A SpringArmComponent that allows for flexible control of camera positioning and movement.
	 *
	 * This variable represents a USpringArmComponent, commonly used to provide smooth camera lag,
	 * offset, and rotation control in Unreal Engine. It is often used to adjust the camera
	 * position relative to the character in gameplay scenarios. Specifically,
	 * it helps control and manage the camera boom or spring arm functionality,
	 * attaching the camera to the character with desirable movement constraints.
	 *
	 * Attributes:
	 * - EditAnywhere: Allows this property to be edited in the Unreal Engine editor.
	 * - Category "Camera": Categorizes this variable under the "Camera" section in the editor.
	 *
	 * Default Value:
	 * - Set to nullptr, indicating no SpringArmComponent is assigned by default. It may be initialized
	 *   during runtime or in the editor.
	 *
	 * Note:
	 * To utilize this component, it must be correctly attached to the owning actor (e.g., a character).
	 */

	UPROPERTY(EditAnywhere, Category="Camera")
	TObjectPtr<class USpringArmComponent> SpringArmComponent = nullptr;

	/**
	 * CameraComponent is a pointer to the UCameraComponent associated with the character.
	 * It is used to define and control the camera behavior and properties for the character in the game.
	 *
	 * This property is editable in the editor and categorized under "Camera".
	 */
	UPROPERTY(EditAnywhere, Category="Camera")
	TObjectPtr<class UCameraComponent> CameraComponent = nullptr;

	/**
	 * Represents the weapon component attached to the character.
	 * This component is of type USkeletalMeshComponent and is intended to handle the visual representation
	 * and potentially animations related to the equipped weapon in the combat system.
	 *
	 * This property is editable in the editor under the "Combat" category.
	 */
	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<class USkeletalMeshComponent> Weapon = nullptr;

	/**
	 * @property FName WeaponTipSocketName
	 * @brief Name of the socket located at the tip of the weapon.
	 *
	 * This property is used to identify the socket on a weapon, typically used
	 * for gameplay-related functionalities such as spawning effects, determining
	 * hit points, or aligning objects with the weapon's tip.
	 *
	 * It is editable in the editor under the "Combat" category, allowing designers
	 * to specify or adjust the relevant socket name dynamically.
	 */
	UPROPERTY(EditAnywhere, Category = "Combat")
	FName WeaponTipSocketName;

	/**
	 * @brief Retrieves the location of the combat socket attached to the weapon.
	 *
	 * This method returns the world-space location of the specified combat socket on the character's weapon.
	 * It is used for determining positions relevant to combat, such as attack origins or projectile spawning points.
	 *
	 * @return The FVector representing the world-space location of the combat socket.
	 */
	virtual FVector GetCombatSocketLocation() override;
	
	/**
	 * A pointer to the AbilitySystemComponent associated with this character.
	 *
	 * This component is responsible for managing abilities, attributes, and gameplay effects
	 * for the character.
	 */
	UPROPERTY()
	TObjectPtr<class UAbilitySystemComponent> AbilitySystemComponent = nullptr;

	/**
	 * A pointer to the UAttributeSet object associated with the character.
	 * Used to manage and access gameplay attributes specific to the character.
	 * Typically initialized and utilized in relation to the Ability System Component (ASC)
	 * for applying gameplay effects and attribute calculations.
	 */
	UPROPERTY()
	TObjectPtr<class UAttributeSet> AttributeSet = nullptr;

	/**
	 * Initializes the Ability Actor Info, necessary for setting up the ability system component
	 * and attribute set for the character. This method prepares the character to interact with
	 * the ability system and ensures the proper configuration of default attributes and abilities.
	 *
	 * This function is intended to be overridden by derived classes for specific initialization logic
	 * related to their ability systems or gameplay mechanics.
	 */
	virtual void InitAbilityActorInfo();

protected:
	/**
	 * Represents the default primary attributes for the character, defined as a gameplay effect class.
	 * This attribute is used to initialize and apply the primary stats of the character when initializing attributes.
	 *
	 * This property is editable in the editor, exposed to Blueprints for read-only access, and is categorized under "Attributes".
	 *
	 * @note This variable should be set to a subclass of UGameplayEffect to ensure proper behavior.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
	TSubclassOf<class UGameplayEffect> DefaultPrimaryAttributes = nullptr;

	/**
	 * Represents the default secondary attribute set applied to the character.
	 *
	 * This variable holds a subclass of the `UGameplayEffect` class, which enables the configuration
	 * of secondary attributes for a character, such as combat-related effects, boosts, or similar effects.
	 *
	 * The `DefaultSecondaryAttributes` gameplay effect is intended to be applied to the character during
	 * initialization or gameplay mechanics to establish or modify secondary attributes.
	 *
	 * The blueprint read-only flag allows this variable to be accessed within the Unreal Engine editor,
	 * while the edit anywhere property permits modification of its value in the editor.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
	TSubclassOf<class UGameplayEffect> DefaultSecondaryAttributes = nullptr;

	/**
	 * Represents the default gameplay effect associated with vital attributes for this character.
	 *
	 * This variable is used to specify a class of gameplay effect that determines the vital attribute
	 * configuration, such as health, stamina, and other life-sustaining resources relevant to the character.
	 * The effect is typically applied to set initial values or modify these attributes during gameplay.
	 *
	 * It is editable in the editor, can be read in blueprints, and is categorized under "Attributes".
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
	TSubclassOf<class UGameplayEffect> DefaultVitalAttributes = nullptr;

	/**
	 * Applies a gameplay effect to the character itself.
	 *
	 * @param GameplayEffectClass The class of the gameplay effect to be applied.
	 * @param Level The level of the gameplay effect, which determines its potency or strength.
	 */
	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const;

	/**
	 * Initializes the default attributes for the character by applying predefined gameplay effect classes.
	 *
	 * This method applies three types of default attribute gameplay effects to the character: primary,
	 * secondary, and vital attributes. Each effect is applied at a base level of 1.0. These gameplay effects
	 * are defined as properties in the class and can be customized per character. The method is designed
	 * to ensure that the character starts with its default attribute setup correctly initialized.
	 *
	 * @note This method is expected to be called during the initialization phase of the character, such as
	 * in BeginPlay or other setup methods. It is crucial for ensuring the character's attribute system
	 * has the required effects applied from the beginning.
	 */
	void InitializeDefaultAttributes() const;

	/**
	 * Adds gameplay abilities to the character. This method is invoked to bind
	 * a predefined collection of initial abilities (StartupAbilities)
	 * to the character's ability system component.
	 *
	 * This functionality is executed only on the server by checking authority.
	 * It retrieves the associated UAuraAbilitySystemComponent of the character,
	 * and attaches the provided abilities to it.
	 *
	 * Prerequisites:
	 * - The character must have an initialized AbilitySystemComponent.
	 * - Authority (server-side) is required to make changes in abilities.
	 */
	void AddCharacterAbilities();
private:
	/**
	 * An array containing the gameplay ability classes that the character
	 * starts with. These abilities will be added to the character upon initialization.
	 *
	 * This property is editable within the editor and categorized under "Abilities".
	 * It is primarily used to define the default set of abilities available to the character
	 * at the start of the game or whenever the abilities are initialized.
	 */
	UPROPERTY(EditAnywhere, Category="Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;
};
