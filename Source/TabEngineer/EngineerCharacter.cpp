// Fill out your copyright notice in the Description page of Project Settings.


#include "EngineerCharacter.h"
#include "DrawDebugHelpers.h"
#include "Enemy.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SphereComponent.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "WeaponComponent.h"
#include "Turret.h"

// Sets default values
AEngineerCharacter::AEngineerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AttackRange = 500.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 300.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->AirControl = 0.2f;
	
	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	SpringCameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringCameraArm"));
	SpringCameraArm->SetupAttachment(RootComponent);
	SpringCameraArm->TargetArmLength = 300.f;
	SpringCameraArm->bUsePawnControlRotation = true;
	
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(SpringCameraArm, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("TargetingSphere"));
	SphereComponent->SetupAttachment(RootComponent);
	SphereComponent->SetSphereRadius(AttackRange);

	Weapon = CreateDefaultSubobject<UWeaponComponent>(TEXT("WeaponComponent"));
	Weapon->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AEngineerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEngineerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

// Called to bind functionality to input
void AEngineerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AEngineerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AEngineerCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &AEngineerCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &AEngineerCharacter::LookUp);
	PlayerInputComponent->BindAxis("TurnRate", this, &AEngineerCharacter::TurnRate);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AEngineerCharacter::LookUpRate);
	
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AEngineerCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AEngineerCharacter::StopJumping);

	PlayerInputComponent->BindAction("Target", IE_Pressed, this, &AEngineerCharacter::Target);
	PlayerInputComponent->BindAction("ClearTarget", IE_Pressed, this, &AEngineerCharacter::ClearTarget);
	PlayerInputComponent->BindAction("MainAction", IE_Pressed, this, &AEngineerCharacter::MainAction);
}

void AEngineerCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AEngineerCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void AEngineerCharacter::Jump()
{
	Super::Jump();
}

void AEngineerCharacter::StopJumping()
{
	Super::StopJumping();
}

void AEngineerCharacter::Turn(const float Value)
{
	AddControllerYawInput(Value);
}

void AEngineerCharacter::TurnRate(const float Value)
{
	AddControllerYawInput(Value * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AEngineerCharacter::LookUpRate(const float Value)
{
	AddControllerPitchInput(Value * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AEngineerCharacter::Target()
{
	TArray<AActor*> Result;
	SphereComponent->GetOverlappingActors(Result, AEnemy::StaticClass());
	if (Result.Num() > 0)
	{
		AActor* FirstHit = *(Result.GetData());
		AEnemy* FirstEnemy = Cast<AEnemy>(FirstHit);
		CurrentTarget = FirstEnemy;

		if (CurrentTarget != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Cast enemy"));
			StartAttack();
		}
		
	}
}

void AEngineerCharacter::ClearTarget()
{
	CurrentTarget.Reset();
	StopAttack();
}

void AEngineerCharacter::StopAttack()
{
	GetWorldTimerManager().ClearTimer(AutoAttackTimerHandle);
}

void AEngineerCharacter::BuildTurret()
{
	FVector PointOnGround;
	bool IsValidHit = RayCastFromCamera(PointOnGround);
	if (IsValidHit)
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		FVector SpawnLocation = PointOnGround + FVector(0.f, 0.f, 90.f);
		FRotator SpawnRotation = FRotator::ZeroRotator;
		GetWorld()->SpawnActor(TurretClass, &SpawnLocation, &FRotator::ZeroRotator, SpawnParameters);
	}
}

void AEngineerCharacter::MainAction()
{
	BuildTurret();
}

bool AEngineerCharacter::RayCastFromCamera(FVector& HitLocation) const
{
	FHitResult OutHit;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this->GetOwner());

	
	FVector ForwardVector = GetControlRotation().Vector();
	FVector StartPoint = FollowCamera->GetComponentLocation();
	StartPoint += ForwardVector * SpringCameraArm->TargetArmLength;
	
	float RayDistance = 500.f;
	FVector EndPoint = StartPoint + ForwardVector * RayDistance;
	

	DrawDebugLine(GetWorld(), StartPoint, EndPoint, FColor::Green, false, 1,0,5);

	bool IsHit = GetWorld()->LineTraceSingleByChannel(OutHit, StartPoint, EndPoint, ECC_Visibility, CollisionParams);

	if (IsHit)
	{
		HitLocation = OutHit.Location;
	}
	return IsHit;
}

void AEngineerCharacter::Attack()
{
	if (CurrentTarget != nullptr)
	{
		if (GetDistanceTo(CurrentTarget.Get()) > AttackRange
			|| CurrentTarget->IsDead())
		{
			StopAttack();
			ClearTarget();
		}
		else
		{
			ShootPressed = true;
			Weapon->Shoot(CurrentTarget.Get());
		}
	}
}

void AEngineerCharacter::StartAttack()
{
	GetWorldTimerManager().SetTimer(AutoAttackTimerHandle, this, &AEngineerCharacter::Attack, 1.0f, true, 1.0f);
}

void AEngineerCharacter::LookUp(const float Value)
{
	AddControllerPitchInput(Value);
}




