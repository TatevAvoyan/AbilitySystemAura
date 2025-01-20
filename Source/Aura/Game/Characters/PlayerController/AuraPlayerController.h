// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Aura/Game/Interaction/EnemyInterface.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

class USplineComponent;
class UAuraAbilitySystemComponent;
struct FGameplayTag;
class UAuraInputConfig;

/**
 * A player controller class that extends APlayerController.
 * It handles player input, movement, and interaction with the game world, as well as
 * defining additional abilities and auto-run functionality.
 */
UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	/**
	 * Constructor for AAuraPlayerController class.
	 *
	 * Initializes the player controller with default properties,
	 * such as enabling replication and creating a SplineComponent
	 * subobject for use in managing spline-related functionality.
	 */
	AAuraPlayerController();

protected:
	/**
	 * This method is called when gameplay begins for the player controller.
	 *
	 * Overrides the BeginPlay method of the parent `APlayerController` class.
	 * It performs the following tasks:
	 * - Checks the validity of the `AuraContext` input mapping context.
	 * - Adds the `AuraContext` input mapping context to the input subsystem for this player.
	 * - Configures the mouse cursor to be shown with the default style.
	 * - Prepares the input mode to allow both Game and UI input, disables mouse locking to the viewport,
	 *   and prevents hiding the cursor during input capture.
	 */
	virtual void BeginPlay() override;

	/**
	 * Overrides the PlayerTick function to execute custom functionality during each tick of the PlayerController.
	 *
	 * Performs the following actions:
	 * - Calls the base class's PlayerTick function.
	 * - Conducts a trace to detect the actor under the player cursor using the CursorTrace method.
	 * - Executes the AutoRun method to enable auto-navigation along a spline path if auto-run is enabled.
	 *
	 * @param DeltaTime The time elapsed since the last frame.
	 */
	virtual void PlayerTick(float DeltaTime) override;

	/**
	 * Overrides the SetupInputComponent method from the parent class to initialize and configure the player input for the AuraPlayerController.
	 *
	 * This function casts the base InputComponent to the UAuraInputComponent type and binds actions to its input system.
	 * It sets up the following input bindings:
	 * - Binds the movement action (MoveAction) to the Move function.
	 * - Binds ability input actions as defined in the InputConfig to the appropriate press, release, and hold functions in the controller.
	 *
	 * It ensures the player controller correctly processes input events relevant to game mechanics like movement and ability activation.
	 */
	virtual void SetupInputComponent() override;

private:
	/**
	 * Handles movement input for the player character.
	 *
	 * This method processes the movement input received through the given InputActionValue,
	 * interprets it based on the player's control rotation, and applies the movement to the controlled pawn.
	 *
	 * @param InputActionValue The value representing user input for movement.
	 *                         It is expected to contain a 2D vector where X represents movement along the
	 *                         right-left axis and Y represents movement along the forward-backward axis.
	 *
	 * Movement is calculated relative to the player's facing direction (control rotation),
	 * ensuring the character moves in a direction consistent with the camera or controller's perspective.
	 */
	void Move(const struct FInputActionValue& InputActionValue);

	/**
	 * Performs a cursor trace to determine the current actor under the mouse cursor.
	 *
	 * This function uses the `GetHitResultUnderCursor` method to perform a trace and store the result in the `CursorHit` variable.
	 * If the trace hits a blocking actor:
	 * - Casts the actor hit by the trace into the `IEnemyInterface`.
	 * - Compares the current actor under the cursor (`ThisActor`) with the previous actor from the last trace (`LastActor`).
	 *   - If `ThisActor` and `LastActor` are different:
	 *     - Calls `UnHighlightActor` on the previous actor if it implements the `IEnemyInterface`.
	 *     - Calls `HighlightActor` on the current actor if it implements the `IEnemyInterface`.
	 */
	void CursorTrace();

	/**
	 * A structure that holds hit result information from cursor tracing.
	 * It contains detailed information about the trace hit, such as the location,
	 * the actor hit, and whether a blocking hit occurred.
	 *
	 * Used in conjunction with the CursorTrace() method to evaluate what's under the player's cursor.
	 */
	FHitResult CursorHit;

private:
	/**
	 * UInputMappingContext object that defines input mappings for the player
	 * controller. This property can be edited in the Unreal Editor and belongs
	 * to the "Input" category. It is set to nullptr by default.
	 */
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputMappingContext> AuraContext = nullptr;

	/**
	 * Represents an Input Action object that can be invoked or bound for player input interaction.
	 * The action is assigned to handle specific player movement behaviors.
	 *
	 * EditAnywhere: Allows modification of this property in the editor.
	 * Category "Input": Groups this property under the "Input" classification in the editor UI.
	 */
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> MoveAction = nullptr;


	/**
	 * A TScriptInterface instance that holds a reference to an actor implementing the IEnemyInterface.
	 *
	 * This actor is used in the gameplay mechanics for targeting and interaction with enemy entities.
	 * It is updated dynamically based on cursor trace results or other gameplay events.
	 *
	 * The IEnemyInterface methods, such as HighlightActor and UnHighlightActor, can be invoked
	 * on this instance to provide visual or gameplay cues for the player.
	 *
	 * Initialize this variable to nullptr to indicate no enemy actor is currently targeted.
	 */
	TScriptInterface<IEnemyInterface> ThisActor = nullptr;

	/**
	 * A script interface reference to the last actor that was interacted with or traced by the cursor.
	 *
	 * This variable is used to keep track of the previously highlighted actor that implements the IEnemyInterface.
	 * During cursor tracing (in CursorTrace function), this actor reference is updated and used to manage
	 * state changes (such as highlight/unhighlight) between the current and previous actors.
	 */
	TScriptInterface<IEnemyInterface> LastActor = nullptr;

	/**
	 * @brief Handles the logic when an input tag associated with an ability is pressed.
	 *
	 * This function is typically called whenever a defined input tag for a specific ability
	 * is activated by user interaction or a similar event. It processes and triggers the
	 * necessary logic tied to the corresponding ability.
	 *
	 * The implementation of this function often involves determining if the ability can
	 * currently be activated, executing the appropriate action for the ability, and possibly
	 * handling cooldowns, costs, or state transitions related to the ability.
	 *
	 * @param abilityTag The tag identifier for the input corresponding to the ability.
	 *                   It is used to check or match the specific ability to trigger.
	 *
	 * @return void This function does not return a value.
	 */
	void AbilityInputTagPressed(FGameplayTag InputTag);

	/**
	 * Called when the input associated with a specific gameplay tag is released.
	 *
	 * @param InputTag The gameplay tag corresponding to the input action that was released.
	 */
	void AbilityInputTagReleased(FGameplayTag InputTag);

	/**
	 * Called when an ability input tagged action is held.
	 *
	 * @param InputTag The gameplay tag associated with the held input action.
	 */
	void AbilityInputTagHeld(FGameplayTag InputTag);

	/**
	 * InputConfig property to hold the reference to the input configuration for the player controller.
	 * This is used to define and manage input bindings for actions such as movement or ability interactions.
	 *
	 * - EditDefaultsOnly: Property can be edited in derived blueprint classes but not in instances.
	 * - Category: Input
	 */
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UAuraInputConfig> InputConfig;

	/**
	 * @brief Pointer to the Aura Ability System Component associated with this Player Controller.
	 *
	 * This component is responsible for managing gameplay abilities and effects for the player character.
	 * It is lazily initialized using the GetAuraAbilitySystemComponent() method, which retrieves the Ability System Component
	 * associated with the player character's pawn.
	 */
	UPROPERTY()
	TObjectPtr<UAuraAbilitySystemComponent> AuraAbilitySystemComponent = nullptr;

	/**
	 * @brief Retrieves the Aura Ability System Component associated with the player controller.
	 *
	 * This method attempts to retrieve the Aura Ability System Component by casting the ability system component
	 * of the pawn controlled by this player controller. If the Aura Ability System Component has already been assigned,
	 * it simply returns the existing reference.
	 *
	 * @return A pointer to the UAuraAbilitySystemComponent, or nullptr if the component could not be found or cast.
	 */
	UAuraAbilitySystemComponent* GetAuraAbilitySystemComponent();

	/**
	 * Stores the most recent destination location as a 3D vector.
	 * This vector is used in various movement-related logic such as auto-run and
	 * decision-making for gameplay mechanics that involve destination points.
	 *
	 * Initialized to FVector::ZeroVector to ensure a valid default state.
	 */
	FVector CachedDestination = FVector::ZeroVector;

	/**
	 * Tracks the duration of time the player is holding a specific input for gameplay purposes.
	 * It is used to differentiate between short and long presses of an input,
	 * affecting player actions such as auto-navigation or targeting.
	 */
	float FollowTime = 0.0f;

	/**
	 * @brief Represents the threshold duration for detecting a short press event in a system.
	 *
	 * This constant is typically used in input handling mechanisms to differentiate between
	 * a short press and other types of inputs, such as long presses. Its value defines the
	 * maximum duration (usually in milliseconds) of a press action that can be considered a
	 * short press. Press actions longer than this threshold are treated differently based
	 * on the application's requirements.
	 */
	float ShortPressThreshold = 0.5f;

	/**
	 * Indicates whether the character is currently in Auto Run mode.
	 *
	 * - `true`: The character is moving automatically along a predefined path.
	 * - `false`: Auto Run is disabled or has ended.
	 *
	 * The value of this variable is altered when:
	 * - Auto Run is activated or deactivated.
	 * - Gameplay inputs or certain interactions require Auto Run to be canceled.
	 */
	bool bAutoRunning = false;

	/**
	 * A boolean flag indicating whether the player is currently targeting.
	 * Used to manage targeting state within the player controller.
	 */
	bool bTargeting = false;

	/**
	 * Defines the radius within which auto-run will stop when the character reaches the destination.
	 * If the character's distance to the destination is less than or equal to this value, auto-running will stop.
	 */
	UPROPERTY(EditDefaultsOnly, Category="Input")
	float AutoRunAcceptanceRadius = 50.0f;

	/**
	 * SplineComponent is a spline-based component used in the player controller to define and manage
	 * paths for the player's controlled pawn. It is dynamically created during the initialization
	 * of the AuraPlayerController and updated during gameplay based on navigation or pathfinding logic.
	 *
	 * This component is primarily used to:
	 * - Define a spline path for auto-run functionality, which allows movement input to be applied
	 *   along the spline's direction.
	 * - Dynamically update spline points during gameplay, such as when recalculating a path.
	 * - Act as a visual debugging tool by supporting the rendering of path-related information,
	 *   such as spheres at each spline point.
	 *
	 * The spline component operates in world space and responds to changes in navigation or movement
	 * mechanics, such as auto-running towards a defined destination. It also serves as a reference
	 * for calculating directional vectors and locations closest to the associated spline.
	 */
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent> SplineComponent = nullptr;

	/**
	 * Initiates and manages the auto-run functionality for the controlled pawn.
	 * Computes the direction and moves the pawn along a spline path towards a destination.
	 * Automatically stops auto-running when the pawn reaches the predefined acceptance radius from the destination.
	 */
	void AutoRun();
};
