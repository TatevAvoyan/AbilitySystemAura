// Fill out your copyright notice in the Description page of Project Settings.


#include "OverlayWidgetController.h"

#include "Aura/Game/AbilitySystem/AuraAbilitySystemComponent.h"
#include "Aura/Game/AbilitySystem/AttributeSet/AuraAttributeSet.h"
#include "Kismet/KismetSystemLibrary.h"

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

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(L_HealthAttributeData).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnHealthChanged.Broadcast(Data.NewValue);
		}
	);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(L_MaxHealthAttributeData).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxHealthChanged.Broadcast(Data.NewValue);
		}
	);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(L_ManaAttributeData).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnManaChanged.Broadcast(Data.NewValue);
		}
	);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(L_MaxManaAttributeData).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxManaChanged.Broadcast(Data.NewValue);
		}
	);

	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
			[this](const FGameplayTagContainer& AssetTags)
		{
			for (const FGameplayTag& Tag  : AssetTags)
			{
				// "Message.HealthPotion".MatchesTag("Message") will return True, "Message".MatchesTag("Message.HealthPotion") will return False
				FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));

				if (bool IsMatching = Tag.MatchesTag(MessageTag); IsMatching)
				{
					if (FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag))
					{
						MessageWidgetRowDelegate.Broadcast(*Row);
					}
				}
			}		
		}
	);
}
