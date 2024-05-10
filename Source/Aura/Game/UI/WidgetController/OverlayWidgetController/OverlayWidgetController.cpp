// Fill out your copyright notice in the Description page of Project Settings.


#include "OverlayWidgetController.h"

#include "Aura/Game/AbilitySystem/AttributeSet/AuraAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	Super::BroadcastInitialValues();

	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);

	const float L_Health = AuraAttributeSet->GetHealth();
	const float L_MaxHealth = AuraAttributeSet->GetMaxHealth();

	OnHealthChanged.Broadcast(L_Health);
	OnMaxHealthChanged.Broadcast(L_MaxHealth);
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UAuraAttributeSet* L_AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);

	const FGameplayAttribute L_HealthAttributeData = L_AuraAttributeSet->GetHealthAttribute();
	const FGameplayAttribute L_MaxHealthAttributeData = L_AuraAttributeSet->GetMaxHealthAttribute();

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(L_HealthAttributeData).AddUObject(this, &UOverlayWidgetController::HealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(L_MaxHealthAttributeData).AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);
}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}
