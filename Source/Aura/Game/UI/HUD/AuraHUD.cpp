// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraHUD.h"

#include "../Widget/AuraUserWidget.h"

void AAuraHUD::BeginPlay()
{
	Super::BeginPlay();

	UUserWidget* L_Widget = CreateWidget(GetWorld(), OverlayWidgetClass);
	L_Widget->AddToViewport();
}
