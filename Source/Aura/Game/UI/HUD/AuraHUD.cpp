// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraHUD.h"

#include "Aura/Game/UI//Widget/AuraUserWidget.h"
#include "Aura/Game/UI/WidgetController/OverlayWidgetController/OverlayWidgetController.h"
#include "Game/UI/WidgetController/AttributeMenuWidgetController/AttributeMenuWidgetController.h"

UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (!IsValid(OverlayWidgetController))
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControlParams(WCParams);
		OverlayWidgetController->BindCallbacksToDependencies();
	}

	return OverlayWidgetController;
}

UAttributeMenuWidgetController* AAuraHUD::GetAttributeMenuWidgetController(const FWidgetControllerParams& WCParams)
{
	if (!IsValid(AttributeMenuWidgetController))
	{
		AttributeMenuWidgetController = NewObject<UAttributeMenuWidgetController>(this, AttributeMenuWidgetControllerClass);
		AttributeMenuWidgetController->SetWidgetControlParams(WCParams);
		AttributeMenuWidgetController->BindCallbacksToDependencies();
	}

	return AttributeMenuWidgetController;
}

void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	if (OverlayWidgetClass)
	{
		UUserWidget* L_Widget = CreateWidget(GetWorld(), OverlayWidgetClass);
		OverlayWidget = Cast<UAuraUserWidget>(L_Widget);

		const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
		UOverlayWidgetController* L_WidgetController = GetOverlayWidgetController(WidgetControllerParams);

		OverlayWidget->SetWidgetController(L_WidgetController);
		L_WidgetController->BroadcastInitialValues();
		
		L_Widget->AddToViewport();
	}	
}
