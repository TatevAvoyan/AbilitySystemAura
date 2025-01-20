// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "AuraAssetManager.generated.h"

/**
 * @class UAuraAssetManager
 * @brief The UAuraAssetManager class is responsible for managing game assets in the Aura project.
 *
 * This class extends the standard asset manager functionality, allowing for centralized
 * handling and loading of game assets. It ensures that all assets are loaded, managed,
 * and accessible within a unified framework to optimize performance and maintain consistency.
 *
 * The UAuraAssetManager plays a critical role in efficiently managing memory and asset
 * references. It is designed to handle asynchronous asset loading and provide utilities
 * for asset organization and retrieval throughout the application.
 *
 * Key features include:
 *  - Managing game assets such as models, textures, sounds, and other resources.
 *  - Providing global access to assets and ensuring proper memory management.
 *  - Supporting asynchronous asset loading to reduce runtime blocking.
 *
 * It is recommended to use this manager for all asset-related operations within the Aura project.
 */
UCLASS()
class AURA_API UAuraAssetManager : public UAssetManager
{
	GENERATED_BODY()
public:
	/**
	 * Retrieves the singleton instance of the UAuraAssetManager.
	 *
	 * This method ensures that the game's asset manager is of type UAuraAssetManager
	 * and returns a reference to it. It performs a runtime check to confirm the validity
	 * of GEngine and casts the AssetManager to the desired type.
	 *
	 * @return A reference to the singleton instance of UAuraAssetManager.
	 */
	UAuraAssetManager& Get();

protected:
	/**
	 * @brief Initiates the initial loading process for the application or system.
	 *
	 * This method is responsible for triggering the initial loading sequence,
	 * which may involve preparing resources, initializing configurations, or
	 * performing any necessary startup tasks. It is typically called at the
	 * beginning of the application lifecycle.
	 *
	 * @note Ensure that all required preconditions are met before calling this method.
	 */
	virtual void StartInitialLoading() override;
};
