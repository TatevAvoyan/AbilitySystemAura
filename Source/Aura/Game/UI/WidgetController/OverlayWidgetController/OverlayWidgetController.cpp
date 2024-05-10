// Fill out your copyright notice in the Description page of Project Settings.


#include "OverlayWidgetController.h"

#include "Aura/Game/AbilitySystem/AttributeSet/AuraAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	Super::BroadcastInitialValues();

	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);

	const float L_Health = AuraAttributeSet->GetHealth();
	const float L_MaxHealth = AuraAttributeSet->GetHealth();

	OnHealthChanged.Broadcast(L_Health);
	OnMaxHealthChanged.Broadcast(L_MaxHealth);
}
