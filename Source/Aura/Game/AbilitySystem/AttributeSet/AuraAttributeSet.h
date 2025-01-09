// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AuraAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

DECLARE_DELEGATE_RetVal(FGameplayAttribute, FAttributeSignature)

/**
 * @struct FEffectProperties
 * @brief This structure holds various properties relevant to gameplay effects.
 *
 * The FEffectProperties structure is used to encapsulate contextual information regarding gameplay effects
 * such as the source and target of an effect. It contains pointers to various actors and components that
 * are involved in casting and receiving effects in the game.
 */
USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()
	/**
	 * Default constructor for FEffectProperties.
	 *
	 * Constructs an instance of the FEffectProperties structure with default values.
	 *
	 * @return FEffectProperties
	 */
	FEffectProperties(){}

	/**
	 * A handle to the context of a gameplay effect, which is used to store
	 * information about the source and target of the effect, such as the source
	 * actor, target actor, ability system components, controllers, and characters
	 * involved. This context can be utilized to determine the detailed conditions
	 * and entities affected by a gameplay effect.
	 */
	FGameplayEffectContextHandle EffectContextHandle;

	/**
	 * Holds a pointer to the Ability System Component of the source actor.
	 *
	 * This variable is used to reference and access the abilities and effects
	 * originating from the source actor, such as applying gameplay effects or
	 * triggering ability-specific logic. It is set within effect context handling
	 * to ensure that any relevant source information is easily accessible.
	 */
	UPROPERTY()
	UAbilitySystemComponent* SourceASC = nullptr;

	/**
	 * The actor that represents the source of the applied gameplay effect.
	 * It is typically the avatar actor associated with the source ability system component.
	 * This actor can be used to extract additional context or to access specific components
	 * or properties relevant to the execution of gameplay effects.
	 */
	UPROPERTY()
	AActor* SourceAvatarActor = nullptr;

	/**
	 * Holds a reference to the controller responsible for initiating a gameplay effect.
	 * This can be either a player or AI controller.
	 * It is used to trace back the source of abilities or effects within the game context.
	 */
	UPROPERTY()
	AController* SourceController = nullptr;

	/**
	 * Pointer to the character that is the source of a gameplay effect.
	 *
	 * This variable is used to store a reference to the character that initiated a
	 * gameplay effect. It is intended to be used in gameplay logic that requires
	 * information about the origin of an effect, such as determining which character
	 * inflicted damage or applied a buff/debuff.
	 */
	UPROPERTY()
	ACharacter* SourceCharacter = nullptr;

	/**
	 * Pointer to the target's AbilitySystemComponent.
	 *
	 * This variable initializes to nullptr and is intended to hold a reference to the target's
	 * UAbilitySystemComponent. It provides access to the ability system of the target, enabling
	 * interaction and manipulation of the target's gameplay abilities and effects.
	 */
	UPROPERTY()
	UAbilitySystemComponent* TargetASC = nullptr;

	/**
	 * @brief The actor that serves as the target in gameplay effect applications.
	 *
	 * This variable holds a pointer to an AActor instance, which represents the target avatar actor in the context of ability system components and gameplay effects.
	 */
	UPROPERTY()
	AActor* TargetAvatarActor = nullptr;

	/**
	 * Points to the controller associated with the target.
	 *
	 * Represents the player controller or AI controller managing the target actor.
	 * Used in the context of gameplay effects and abilities to identify the target's controller for further logic processing.
	 */
	UPROPERTY()
	AController* TargetController = nullptr;

	/**
	 * Pointer to the target character affected by the ability system component.
	 * This variable is typically assigned within the context of applying effects or
	 * responding to gameplay events involving target characters.
	 */
	UPROPERTY()
	ACharacter* TargetCharacter = nullptr;
};

//typedef TBaseStaticDelegateInstance<FGameplayAttribute(), FDefaultTSDelegateUserPolicy>::FFuncPtr FAttributeFuncPtr;
template<class T>
using TStaticFuncPtr = TBaseStaticDelegateInstance<FGameplayAttribute(), FDefaultTSDelegateUserPolicy>::FFuncPtr;

/**
 * Initializes a new instance of the UAuraAttributeSet class.
 * This constructor sets up default values and configurations.
 */
UCLASS()
class AURA_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	/**
	 * UAuraAttributeSet constructor. Initializes the TagsToAttributes map with primary and secondary attribute tags.
	 *
	 * @return A constructed instance of UAuraAttributeSet with predefined gameplay tags mapped to corresponding attribute getter functions.
	 */
	UAuraAttributeSet();

	/**
	 * Populates the list of properties that require network replication for this attribute set.
	 *
	 * @param OutLifetimeProps The array that will be populated with the properties to replicate.
	 */
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/**
	 * This method is called before an attribute's value is changed.
	 * It ensures that the new value for the Health and Mana attributes are clamped within their respective valid ranges.
	 *
	 * @param Attribute The attribute that is about to be changed.
	 * @param NewValue The new value that is about to be assigned to the attribute. This value may be modified by this method.
	 */
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	/**
	 * Handles the modifications applied by a gameplay effect after it has been executed.
	 * Clamps health and mana attributes to ensure they remain within valid ranges.
	 *
	 * @param Data Callback data containing details about the gameplay effect execution.
	 */
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	/**
	 * A mapping between gameplay tags and corresponding static function pointers that return gameplay attributes.
	 *
	 * This map facilitates the association of specific gameplay tags with functions that yield the corresponding
	 * FGameplayAttribute, allowing for dynamic and flexible attribute management based on tags.
	 *
	 * - Key: FGameplayTag representing a unique identifier for a category or type of gameplay element.
	 * - Value: TStaticFuncPtr<FGameplayAttribute()> is a pointer to a static function that returns an FGameplayAttribute.
	 */
	TMap<FGameplayTag, TStaticFuncPtr<FGameplayAttribute()>> TagsToAttributes;

	/**
	 * Represents the Strength attribute for a character.
	 * This attribute is read-only in Blueprints and is replicated across the network using the OnRep_Strength function.
	 * It belongs to the Primary Attributes category.
	 */

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Strength, Category = "Primary Attributes")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Strength);

	/**
	 * @brief Represents the intelligence attribute of a character or entity.
	 *
	 * This variable holds the value of an entity's intelligence.
	 * Intelligence is used to determine the entity's ability to solve problems,
	 * make decisions, and perform tasks requiring mental effort.
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Intelligence, Category = "Primary Attributes")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Intelligence);

	/**
	 * Represents the resilience attribute in the game's attribute set system.
	 * This attribute is a primary attribute and it's replicated using the OnRep_Resilience function.
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Resilience, Category = "Primary Attributes")
	FGameplayAttributeData Resilience;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Resilience);

	/**
	 * Represents the Vigor attribute in the Aura game, which is a primary attribute.
	 *
	 * This variable is a FGameplayAttributeData type and is replicated to ensure
	 * consistency across the network. It uses the OnRep_Vigor function for replication
	 * updates and belongs to the "Primary Attributes" category.
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Vigor, Category = "Primary Attributes")
	FGameplayAttributeData Vigor;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Vigor);

	/**
	 * @brief Represents the health attribute of a character.
	 *
	 * This property is replicated and triggers a callback function OnRep_Health whenever it changes.
	 * It's categorized under "Vital Attributes" and can be read from the Blueprint.
	 */

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Vital Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Health);

	/**
	 * The Mana attribute in the UAuraAttributeSet class, representing the character's mana points.
	 * This attribute is replicated using the OnRep_Mana method and is categorized under "Vital Attributes".
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "Vital Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Mana);

	/**
	 * Represents the maximum health attribute of a character.
	 * This attribute is categorized under "Secondary Attributes" and is replicated.
	 * The value is updated using the `OnRep_MaxHealth` function.
	 */

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Secondary Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxHealth);

	/**
	 * Handles updates and notifications when the MaxHealth attribute is replicated.
	 *
	 * @param OldMaxHealth The previous value of the MaxHealth attribute before replication.
	 */
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;

	/**
	 * Represents the maximum amount of mana a character can have.
	 * This attribute is replicated and includes a callback function, OnRep_MaxMana,
	 * that is triggered whenever the value is updated.
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "Secondary Attributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxMana);

	/**
	 * Callback function that gets called when the MaxMana attribute is replicated.
	 *
	 * @param OldMaxMana The previous value of MaxMana before it was replicated.
	 */
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;

	/**
	 * @brief Represents the armor value in the game's attribute system.
	 *
	 * The armor attribute determines the amount of physical damage reduction a character possesses. It is used
	 * to mitigate incoming damage in combat scenarios. This attribute is replicated and is read-only in blueprints.
	 *
	 * @note This variable is replicated using the OnRep_Armor function, which is called whenever the value of the armor changes.
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Armor, Category = "Secondary Attributes")
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Armor);

	/**
	 * Handles actions to be taken when the value of the Armor attribute is replicated.
	 * This method is called to notify that the Armor attribute has been updated and
	 * performs any corresponding logic.
	 *
	 * @param OldArmor The previous value of the Armor attribute before replication.
	 */
	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData& OldArmor) const;

	/**
	 * Represents the amount of armor penetration a character has.
	 * This attribute is typically used to calculate how much of the target's armor is ignored during damage calculations.
	 * It is replicated to ensure that the value is the same on both the client and server.
	 *
	 * Attributes:
	 * - BlueprintReadOnly: The property is read-only in Blueprints.
	 * - ReplicatedUsing: Specifies the function to call when this variable is replicated.
	 * - Category: Defines the category of this attribute in the editor.
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ArmorPenetration, Category = "Secondary Attributes")
	FGameplayAttributeData ArmorPenetration;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ArmorPenetration);

	/**
	 * Handles the replication notification for the ArmorPenetration attribute.
	 *
	 * This function is called whenever the ArmorPenetration attribute is replicated to ensure that any necessary updates
	 * or notifications are performed based on the old and new values of the attribute.
	 *
	 * @param OldArmorPenetration The previous value of the ArmorPenetration attribute before it was updated.
	 */
	UFUNCTION()
	void OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const;

	/**
	 * @brief Represents the chance of a character blocking an incoming attack.
	 *
	 * The BlockChance attribute determines the likelihood that a character can block an
	 * incoming attack, thereby reducing or nullifying damage. This attribute can be modified
	 * by various gameplay effects and is replicated to ensure consistency across clients in
	 * a networked game.
	 *
	 * @remark This attribute is categorized under Secondary Attributes and is replicated.
	 * When the attribute is updated on the server, the OnRep_BlockChance function is called
	 * on the clients to handle the change.
	 *
	 * @property BlueprintReadOnly Specifies that the attribute is read-only in Blueprints.
	 * @property ReplicatedUsing Indicates the function to be called for handling replication of this attribute.
	 * @property Category Specifies the category under which this attribute falls.
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BlockChance, Category = "Secondary Attributes")
	FGameplayAttributeData BlockChance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, BlockChance);

	/**
	 * Notifies the system about changes to the BlockChance attribute.
	 * This method is called automatically whenever the BlockChance attribute is replicated.
	 *
	 * @param OldBlockChance The previous value of the BlockChance attribute before replication.
	 */
	UFUNCTION()
	void OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const;

	/**
	 * Represents the chance to land a critical hit.
	 * This attribute determines the probability that an attack will deal extra damage by striking a critical spot.
	 *
	 * Attributes:
	 * - BlueprintReadOnly: Indicates that this variable can be read in Blueprints but not modified.
	 * - ReplicatedUsing: Specifies the function to call when this variable is updated over the network.
	 * - Category: Groups this attribute under "Secondary Attributes" in the editor.
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitChance, Category = "Secondary Attributes")
	FGameplayAttributeData CriticalHitChance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitChance);

	/**
	 * Handles changes in the CriticalHitChance attribute when it's replicated.
	 *
	 * @param OldCriticalHitChance The previous value of the CriticalHitChance attribute before replication.
	 */
	UFUNCTION()
	void OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const;

	/**
	 * Represents the critical hit damage attribute. This attribute is read-only in Blueprints and
	 * is replicated to clients using the `OnRep_CriticalHitDamage` function.
	 *
	 * Category: Secondary Attributes
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitDamage, Category = "Secondary Attributes")
	FGameplayAttributeData CriticalHitDamage;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitDamage);

	/**
	 * Handles the replication of the CriticalHitDamage attribute.
	 *
	 * This function is called when the CriticalHitDamage attribute is updated on
	 * the server and needs to be synced to clients. It notifies the system of the
	 * updated value to ensure proper replication.
	 *
	 * @param OldCriticalHitDamage The previous value of the CriticalHitDamage attribute before the update.
	 */
	UFUNCTION()
	void OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const;

	/**
	 * CriticalHitResistance is a secondary attribute that represents the character's ability
	 * to reduce damage from incoming critical hits.
	 *
	 * This attribute is replicated and will trigger the OnRep_CriticalHitResistance function
	 * whenever it gets updated. It should be used to enhance gameplay mechanics related to
	 * resisting critical damage.
	 *
	 * Category: Secondary Attributes
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitResistance, Category = "Secondary Attributes")
	FGameplayAttributeData CriticalHitResistance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitResistance);

	/**
	 * Handles the replication notification for the CriticalHitResistance attribute.
	 * This method is called whenever there is a replication update for the CriticalHitResistance attribute.
	 *
	 * @param OldCriticalHitResistance The previous value of the CriticalHitResistance attribute before the update.
	 */
	UFUNCTION()
	void OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance) const;

	/**
	 * @brief Represents the rate at which a character's health regenerates over time.
	 *
	 * This attribute determines how quickly health is restored for a character. It is a
	 * secondary attribute and is replicated across the network.
	 *
	 * This variable is tagged with ReplicatedUsing to ensure that changes in health
	 * regeneration are synchronized across clients, and BlueprintReadOnly to allow
	 * read access within blueprints.
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HealthRegeneration, Category = "Secondary Attributes")
	FGameplayAttributeData HealthRegeneration;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, HealthRegeneration);

	/**
	 * Called to replicate changes in the HealthRegeneration attribute.
	 *
	 * @param OldHealthRegeneration The previous value of the HealthRegeneration attribute before replication.
	 */
	UFUNCTION()
	void OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const;

	/**
	 * Represents the rate at which a character regenerates mana.
	 * This attribute is used to determine the amount of mana a character gains back over time.
	 * The value of this attribute is replicated and updated across the network.
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ManaRegeneration, Category = "Secondary Attributes")
	FGameplayAttributeData ManaRegeneration;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ManaRegeneration);

	/**
	 * Handles the replication of the ManaRegeneration attribute.
	 * This function is called when the ManaRegeneration attribute is updated on the server
	 * and needs to be synchronized to clients.
	 *
	 * @param OldManaRegeneration The previous value of the ManaRegeneration attribute before the update.
	 */
	UFUNCTION()
	void OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const;

	/**
	 * This method is called whenever the Health property is replicated.
	 * It updates the health-related variables and states within the gameplay.
	 *
	 * @param OldHealth The previous value of the Health property before replication.
	 */
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;

	/**
	 * @brief Replicates the current mana value to all clients.
	 *
	 * This function is called automatically when the mana value is updated
	 * on the server to ensure that the change is propagated to all clients.
	 *
	 * @param OldMana The previous value of mana before the update.
	 */
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;

	/**
	 * Function that gets called whenever the Strength property is updated.
	 *
	 * @param OldStrength The previous value of the Strength property before it was updated.
	 */
	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& OldStrength) const;

	/**
	 * Method called when the Intelligence variable is replicated.
	 *
	 * @param OldIntelligence The value of the Intelligence variable before it was updated.
	 */
	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const;

	/**
	 * Method that is called when the resilience property is updated.
	 *
	 * @param OldResilience The previous value of the resilience property before the update.
	 */
	UFUNCTION()
	void OnRep_Resilience(const FGameplayAttributeData& OldResilience) const;

	/**
	 * Handles the replication notification for the Vigor attribute.
	 *
	 * @param OldVigor The previous value of the Vigor attribute before the replication update.
	 */
	UFUNCTION()
	void OnRep_Vigor(const FGameplayAttributeData& OldVigor) const;

private:
	/**
	 * Sets the properties for a given effect.
	 *
	 * This method initializes and configures the properties of a specified effect,
	 * which can include various parameters that dictate how the effect behaves
	 * and is rendered.
	 *
	 * @param effectID The identifier of the effect to be configured.
	 * @param properties A collection of key-value pairs representing the properties
	 *                   and their corresponding values to be set for the effect.
	 */
	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const;
};
