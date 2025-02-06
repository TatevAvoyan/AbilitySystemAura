// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/AbilitySystem/Abilities/AuraProjectileSpell.h"

#include "Game/Interaction/CombatInterface.h"
#include "ProjectileActor/AuraProjectile.h"


void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (HasAuthority(&ActivationInfo))
	{
		if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo()))
		{
			const FVector SocketLocation = CombatInterface->GetCombatSocketLocation();
			FTransform Transform;
			Transform.SetLocation(SocketLocation);
			// TODO: Set the Projectile Rotation

			AAuraProjectile* AuraProjectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(
				ProjectileClass,
				Transform,
				GetOwningActorFromActorInfo(),
				Cast<APawn>(GetOwningActorFromActorInfo()),
				ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

			// TODO: Give the Projectile a gameplay effect for causiong damage.
			AuraProjectile->FinishSpawning(Transform);
		}
	}
}
