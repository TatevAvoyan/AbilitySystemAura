// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AuraEffectActor.generated.h"

UCLASS()
class AURA_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAuraEffectActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION()
	virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
public:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UStaticMeshComponent> Mesh = nullptr;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class USphereComponent> SphereComponent = nullptr;

	UPROPERTY(EditAnywhere, Category="Setup")
	bool bIsMana = false;

	UPROPERTY(EditAnywhere, Category="Setup")
	bool bIsAddMana = false;

	UPROPERTY(EditAnywhere, Category="Setup")
	bool bIsHealth = false;

	UPROPERTY(EditAnywhere, Category="Setup")
	bool bIsAddHealth = false;
};
