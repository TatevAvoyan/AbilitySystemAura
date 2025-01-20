// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * @brief The FAuraGameplayTags class serves as a centralized structure to manage and retrieve gameplay tags
 * used throughout the application.
 *
 * This class encapsulates various gameplay tag definitions to ensure consistent usage of tags across
 * the codebase. It is designed as a container that provides a structured and centralized way to define
 * and access gameplay tags, improving readability and reducing potential errors with tag strings.
 *
 * The primary purpose of this class is to store tag-related identifiers used for game mechanics, abilities,
 * states, and other gameplay-related features. This helps developers avoid hardcoding tag strings in multiple
 * locations and provides operational consistency.
 */

struct FAuraGameplayTags
{
	/**
	 * Retrieves a reference to the statically defined FAuraGameplayTags instance.
	 *
	 * This static method provides access to the singleton instance of the FAuraGameplayTags
	 * struct, which contains all predefined gameplay tags used throughout the system.
	 *
	 * @return A constant reference to the FAuraGameplayTags instance containing predefined gameplay tags.
	 */
public:
    static const FAuraGameplayTags& Get() {return GameplayTags;}
	/**
	 * Initializes all native gameplay tags used in the Aura system.
	 *
	 * This method registers and assigns various gameplay tags for primary attributes,
	 * secondary attributes, and input tags to the GameplayTags instance. These
	 * tags encapsulate different gameplay mechanics like character attributes
	 * (e.g., Strength, Intelligence, Armor, etc.) and input actions (e.g., Left Mouse
	 * Button, specific keyboard keys, etc.).
	 *
	 * The primary attributes include:
	 * - Strength: Increases physical damage.
	 * - Intelligence: Increases magical damage.
	 * - Resilience: Increases Armor and Armor Penetration.
	 * - Vigor: Increases Health.
	 *
	 * The secondary attributes include:
	 * - Armor: Reduces damage taken, improves Block Chance.
	 * - Armor Penetration: Ignores a percentage of enemy Armor, increases Critical Hit Chance.
	 * - Block Chance: Chance to cut incoming damage in half.
	 * - Critical Hit Chance: Chance to double damage plus critical hit bonus.
	 * - Critical Hit Damage: Bonus damage added when a critical hit is scored.
	 * - Critical Hit Resistance: Reduces Critical Hit Chance of attacking enemies.
	 * - Health Regeneration: Amount of Health regenerated every second.
	 * - Mana Regeneration: Amount of Mana regenerated every second.
	 * - Max Health: Maximum amount of Health obtainable.
	 * - Max Mana: Maximum amount of Mana obtainable.
	 *
	 * The input tags include:
	 * - Input Tag for the Left Mouse Button (LMB).
	 * - Input Tag for the Right Mouse Button (RMB).
	 * - Input Tags for the keys 1, 2, 3, and 4.
	 */
	static void InitializeNativeGameplayTags();

	/**
	 * Gameplay tag representing the Strength attribute in the primary attributes category.
	 * Used to identify and modify characteristics related to the Strength stat in gameplay mechanics.
	 */
	FGameplayTag Attributes_Primary_Strength;
	/**
	 * Represents the gameplay tag associated with the primary attribute Intelligence.
	 * This tag is used to identify and interact with the Intelligence attribute in
	 * gameplay systems, ensuring consistent handling and referencing within the game framework.
	 */
	FGameplayTag Attributes_Primary_Intelligence;
	/**
	 * @brief Represents the primary attribute of resilience in a system.
	 *
	 * This variable is used to define or manipulate the resilience attribute
	 * within the primary set of attributes for a character, entity, or object.
	 * Resilience often signifies the ability to withstand hardships, recover
	 * from damage, or maintain stability under stress in a given environment.
	 *
	 * Usage depends on the specific system or mechanics implemented, typically
	 * related to stamina, defense, recovery, or durability characteristics.
	 */
	FGameplayTag Attributes_Primary_Resilience;
	/**
	 * Represents the primary vigor attribute gameplay tag used for identifying or categorizing
	 * gameplay elements related to the vigor attribute within the gameplay framework.
	 */
	FGameplayTag Attributes_Primary_Vigor;


	/**
	 * A gameplay tag representing the secondary armor attribute in the game.
	 * This tag can be used to identify and manage gameplay elements associated with secondary armor,
	 * such as modifiers, effects, or interactions affecting the secondary armor attribute.
	 */
	FGameplayTag Attributes_Secondary_Armor;
	/**
	 * @brief Represents the secondary attribute for armor penetration in a game or system.
	 *
	 * This variable is used to define the degree to which an entity is capable of
	 * bypassing or reducing an opponent's armor or defense mechanisms during calculations
	 * related to damage or attack resolution. Higher values may indicate greater
	 * effectiveness in penetrating armor.
	 *
	 * @note The functionality or impact of this attribute may depend on the specific
	 *       implementation of armor or damage mechanics within the system.
	 */
	FGameplayTag Attributes_Secondary_ArmorPenetration;
	/**
	 * Represents a gameplay tag associated with the block chance attribute in the secondary attributes category.
	 * This tag is typically used to define or reference block chance-related gameplay mechanics or properties.
	 */
	FGameplayTag Attributes_Secondary_BlockChance;
	/**
	 * @brief Represents the critical hit chance as a secondary attribute.
	 *
	 * This variable stores the percentage chance of performing a critical hit in combat
	 * or gameplay interactions. A critical hit typically deals extra damage or has
	 * an enhanced effect compared to a standard action.
	 *
	 * It is considered a secondary attribute, meaning it is derived or influenced
	 * by other primary attributes or factors such as equipment, skills, or buffs.
	 *
	 * The value is generally expected to be within a defined range, often represented
	 * as a percentage (e.g., 0 to 100), though this may depend on the specific implementation.
	 */
	FGameplayTag Attributes_Secondary_CriticalHitChance;
	/**
	 * @brief Represents the attribute value associated with the critical hit damage modifier
	 * in a secondary attribute category.
	 *
	 * This variable typically defines the multiplier or percentage bonus that is applied
	 * to damage dealt during a critical hit event, enhancing the total damage output.
	 * It is commonly used in systems such as combat mechanics, character statistics, or
	 * weapon attributes in games or simulations.
	 *
	 * The value for Attributes_Secondary_CriticalHitDamage could vary based on the context,
	 * such as character level, equipment bonuses, or other gameplay modifiers.
	 */
	FGameplayTag Attributes_Secondary_CriticalHitDamage;
	/**
	 * Represents a gameplay tag associated with the secondary attribute "Critical Hit Resistance."
	 * This attribute typically defines a character's ability to resist or reduce the effects of critical hits.
	 * It may influence gameplay mechanics such as damage reduction or the probability of receiving critical hits.
	 */
	FGameplayTag Attributes_Secondary_CriticalHitResistance;
	/**
	 * @brief Represents the secondary attribute for health regeneration in a character or entity.
	 *
	 * This variable is used to define or calculate the rate at which an entity regenerates health over time.
	 * It is typically utilized in gameplay mechanics where health recovery is influenced by specific secondary
	 * attributes or custom behavior.
	 *
	 * @note The exact implementation and scaling factors for health regeneration may vary depending on the game
	 * or application design.
	 */
	FGameplayTag Attributes_Secondary_HealthRegeneration;
	/**
	 * @brief Represents the rate at which mana regenerates over time.
	 *
	 * This variable is used to track and modify the secondary attribute
	 * associated with mana regeneration. It determines the regeneration of
	 * mana points for a character or entity within a specified period.
	 *
	 * Commonly used in game mechanics or systems where mana is required for
	 * abilities, spells, or other resource-driven actions.
	 *
	 * Adjustments to this variable can influence the recovery rate of mana,
	 * impacting gameplay balance and resource management.
	 */
	FGameplayTag Attributes_Secondary_ManaRegeneration;
	/**
	 * Represents a gameplay tag associated with the maximum mana attribute
	 * in the secondary attributes category of a gameplay system.
	 *
	 * This tag is commonly used to identify and manage references, properties,
	 * or effects related to the maximum mana stat within the game's mechanics.
	 */
	FGameplayTag Attributes_Secondary_MaxMana;
	/**
	 * A gameplay tag that represents the secondary attribute for maximum health.
	 * This tag is used to identify and manage functionality related to the
	 * maximum health secondary attribute in the gameplay system.
	 */
	FGameplayTag Attributes_Secondary_MaxHealth;

	/**
	 * Represents the gameplay tag associated with the left mouse button (LMB) input.
	 * Used for binding or recognizing specific gameplay mechanics or actions triggered by the LMB.
	 */
	FGameplayTag InputTag_LMB;
	/**
	 * @brief Variable to store the input tag for the Right Mouse Button (RMB) event.
	 *
	 * This variable is used to identify and manage input events specifically triggered
	 * by the right mouse button in the application. It may be used within event handling
	 * mechanisms or for mapping actions to the RMB input.
	 */
	FGameplayTag InputTag_RMB;
	/**
	 * @brief Represents the first input tag for a specific operation or process.
	 *
	 * This variable is typically used to identify or define the primary input
	 * parameter required to execute a function, method, or operation. It may
	 * serve as a unique identifier or a data source reference for the process.
	 *
	 * Usage and intended value of this variable depend on the context in which
	 * it is applied.
	 */
	FGameplayTag InputTag_1;
	/**
	 * @brief Represents a specific input tag used for identifying or categorizing
	 *        a secondary input in the application.
	 *
	 * This variable is utilized to distinguish an input source or to provide
	 * additional context for the system's input handling logic. It may be used
	 * for tasks such as data processing, filtering, or routing specific
	 * actions to a particular input stream.
	 */
	FGameplayTag InputTag_2;
	/**
	 * @brief Represents the third input tag utilized in the system.
	 *
	 * The `InputTag_3` variable is used for managing and processing a specific
	 * input in the application. It serves as an identifier or placeholder
	 * for data associated with the third input, ensuring a consistent reference
	 * within the system's logic.
	 *
	 * This variable plays a role in configurations, data pipelines, or workflows
	 * where multiple input tags are involved, designated by sequential numbering.
	 */
	FGameplayTag InputTag_3;
	/**
	 * @brief Represents the fourth input tag used for identifying or categorizing a specific input in the system.
	 *
	 * This variable is utilized to store or reference the fourth input tag in a sequential process or tagging system.
	 * It may be used to track, label, or manage data relevant to a specific input. The context and value of InputTag_4
	 * depend on its application in the program.
	 */
	FGameplayTag InputTag_4;

private:
	/**
	 * @brief A collection of tags used to define gameplay-specific attributes or states.
	 *
	 * GameplayTags are typically utilized to represent metadata, categorize objects, or
	 * define component or actor-specific properties within a game engine. They enable
	 * efficient and flexible tagging systems to determine gameplay logic, features, or
	 * behavior triggering mechanisms. Often used for improving modularity and reducing
	 * hardcoded dependencies between gameplay systems.
	 */
	static FAuraGameplayTags GameplayTags;
};
