// Confused Minds Inc.


#include "Player/L1_Character.h"

#include "Camera/CameraComponent.h"

// Sets default values
AL1_Character::AL1_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // Create camera and attach to boom
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(GetMesh(), FName("head"));
    FollowCamera->bUsePawnControlRotation = true;
}

// Called when the game starts or when spawned
void AL1_Character::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AL1_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AL1_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

