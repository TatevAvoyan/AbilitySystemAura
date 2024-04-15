// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraEnemy.h"

AAuraEnemy::AAuraEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
}

void AAuraEnemy::BeginPlay()
{
	Super::BeginPlay();
	SetMeshes();
}

void AAuraEnemy::ToggleActorHighlighting(const bool bIsHighlight) const
{
	if (IsValid(BodyMesh) && IsValid(WeaponMesh))
	{
		BodyMesh->SetRenderCustomDepth(bIsHighlight);
		WeaponMesh->SetRenderCustomDepth(bIsHighlight);

		const float L_StencilValue = bIsHighlight ? 250.f : 0.f;
		BodyMesh->SetCustomDepthStencilValue(L_StencilValue);
		WeaponMesh->SetCustomDepthStencilValue(L_StencilValue);
	}
}

void AAuraEnemy::HighlightActor()
{
	ToggleActorHighlighting(true);
}

void AAuraEnemy::UnHighlightActor()
{
	ToggleActorHighlighting(false);
}

void AAuraEnemy::SetMeshes()
{
	BodyMesh = GetMesh();
	WeaponMesh = Weapon;
}
