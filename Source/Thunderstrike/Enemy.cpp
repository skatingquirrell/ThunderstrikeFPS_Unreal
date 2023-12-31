// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy.h"

#include "Components/BoxComponent.h"
#include "Hero.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

// Sets default values
AEnemy::AEnemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DamageCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Damage Collision"));
	DamageCollision->SetupAttachment(RootComponent);

	AIPerComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AI Perception Component"));
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));

	SightConfig->SightRadius = 1250.0f;
	SightConfig->LoseSightRadius = 1280.0f;
	SightConfig->PeripheralVisionAngleDegrees = 90.0f;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->SetMaxAge(0.1f);

	AIPerComp->ConfigureSense(*SightConfig);
	AIPerComp->SetDominantSense(SightConfig->GetSenseImplementation());
	AIPerComp->OnPerceptionUpdated.AddDynamic(this, &AEnemy::OnSensed);

	CurrentVelocity = FVector::ZeroVector;
	MovementSpeed = 375.0f;

	DistanceSquared = BIG_NUMBER;
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	DamageCollision->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnHit);

	BaseLocation = this->GetActorLocation();

	// Call the randomization function
	RandomizeMesh();
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Move character to base or to the opponent's position
	if (!CurrentVelocity.IsZero())
	{
		NewLocation = GetActorLocation() + CurrentVelocity * DeltaTime;
		if (BackToBaseLocation)
		{
			if ((NewLocation - BaseLocation).SizeSquared2D() < DistanceSquared)
			{
				DistanceSquared = (NewLocation - BaseLocation).SizeSquared2D();
			}
			else
			{
				CurrentVelocity = FVector::ZeroVector;
				DistanceSquared = BIG_NUMBER;
				BackToBaseLocation = false;

				SetNewRotation(GetActorForwardVector(), GetActorLocation());
			}
		}

		SetActorLocation(NewLocation);
	}
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEnemy::DealDamage(float DamageAmount)
{
	Health -= DamageAmount;
	UE_LOG(LogTemp, Warning, TEXT("Enemy HEALTH %f"), Health);

	if (Health <= 0.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("ENEMY ELIMINATED!"));

		Destroy()	;
	}
}

void AEnemy::OnHit(UPrimitiveComponent *HitComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &Hit)
{
	// UE_LOG(LogTemp, Warning, TEXT("CONTACT"));

	//Deal damage to the hero
	AHero* Char = Cast<AHero>(OtherActor);
	if(Char)
	{
		isAttacking = true;
		Char->DealDamage(DamageValue);
	}
}

void AEnemy::RandomizeMesh()
{
	if (MeshArray.Num() == 0)
	{
		return;
	}

	// Get a random index within the range of the array
	int32 RandomIndex = FMath::RandRange(0, MeshArray.Num() - 1);

	// Set the skeletal mesh of the MeshComponent to the randomly selected mesh
	USkeletalMeshComponent *SkeletalMeshComponent = FindComponentByClass<USkeletalMeshComponent>();
	if (SkeletalMeshComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Set Skeletal Mesh: %d"), RandomIndex);
		SkeletalMeshComponent->SetSkeletalMesh(MeshArray[RandomIndex]);
	}
}

void AEnemy::OnSensed(const TArray<AActor *> &UpdatedActors)
{

	// return;
	for (int i = 0; i < UpdatedActors.Num(); i++)
	{

		FActorPerceptionBlueprintInfo Info;

		AIPerComp->GetActorsPerception(UpdatedActors[i], Info);

		// chase the opponent if detected, or else go back to base
		if (Info.LastSensedStimuli[0].WasSuccessfullySensed())
		{
			// UE_LOG(LogTemp, Warning, TEXT("SENSE by ENEMY %d"), i);
			FVector dir = UpdatedActors[i]->GetActorLocation() - GetActorLocation();
			dir.Z = 0.0f;

			CurrentVelocity = dir.GetSafeNormal() * MovementSpeed;

			SetNewRotation(UpdatedActors[i]->GetActorLocation(), GetActorLocation());
		}
		else
		{
			FVector dir = BaseLocation - GetActorLocation();
			dir.Z = 0.0f;

			if (dir.SizeSquared2D() > 1.0f)
			{
				CurrentVelocity = dir.GetSafeNormal() * MovementSpeed;
				BackToBaseLocation = true;
				isAttacking = false;
				UE_LOG(LogTemp, Display, TEXT("ENEMY %d goes back to base"), i);

				SetNewRotation(BaseLocation, GetActorLocation());
			}
		}
	}
}

void AEnemy::SetNewRotation(FVector TargetPosition, FVector CurrentPosition)
{
	FVector NewDirection = TargetPosition - CurrentPosition;
	NewDirection.Z = 0.0f;

	EnemyRotation = NewDirection.Rotation();
	SetActorRotation(EnemyRotation);
}

void AEnemy::SetMovementAnim(FVector Velocity)
{
	// UAnimInstance *AnimInstance = FindComponentByClass<UAnimInstance>();
	// if (AnimInstance)
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("Got anim instance"));
	// AnimInstance->set
	// }
}
