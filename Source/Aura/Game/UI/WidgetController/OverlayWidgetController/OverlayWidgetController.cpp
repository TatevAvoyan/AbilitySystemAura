// Fill out your copyright notice in the Description page of Project Settings.


#include "OverlayWidgetController.h"

#include "Aura/Game/AbilitySystem/AttributeSet/AuraAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	Super::BroadcastInitialValues();

	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);

	const float L_Health = AuraAttributeSet->GetHealth();
	const float L_MaxHealth = AuraAttributeSet->GetMaxHealth();
	const float L_Mana = AuraAttributeSet->GetMana();
	const float L_MaxMana = AuraAttributeSet->GetMaxMana();

	OnHealthChanged.Broadcast(L_Health);
	OnMaxHealthChanged.Broadcast(L_MaxHealth);

	OnManaChanged.Broadcast(L_Mana);
	OnMaxManaChanged.Broadcast(L_MaxMana);
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UAuraAttributeSet* L_AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);

	const FGameplayAttribute L_HealthAttributeData = L_AuraAttributeSet->GetHealthAttribute();
	const FGameplayAttribute L_MaxHealthAttributeData = L_AuraAttributeSet->GetMaxHealthAttribute();
	const FGameplayAttribute L_ManaAttributeData = L_AuraAttributeSet->GetManaAttribute();
	const FGameplayAttribute L_MaxManaAttributeData = L_AuraAttributeSet->GetMaxManaAttribute();

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(L_HealthAttributeData).AddUObject(this, &UOverlayWidgetController::HealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(L_MaxHealthAttributeData).AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(L_ManaAttributeData).AddUObject(this, &UOverlayWidgetController::ManaChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(L_MaxManaAttributeData).AddUObject(this, &UOverlayWidgetController::MaxManaChanged);
}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Data) const
{
	OnManaChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxManaChanged.Broadcast(Data.NewValue);
}
