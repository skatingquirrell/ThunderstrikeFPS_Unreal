// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Hero.generated.h"

UCLASS()
class THUNDERSTRIKE_API AHero : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHero();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

	// Mesh for hero's shooting hands
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* HandsMesh;

	// Mesh for hero's gun
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* GunMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USceneComponent* MuzzleLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = camera)
	class UCameraComponent* FirstPersonCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float TurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float LookUpRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector GunOffset;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AProjectile> Projectile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class USoundBase* FireSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UAnimMontage* FireAnimation;

	class UAnimInstance* AnimInstance;

	class UWorld* World;

	FRotator SpawnRotation;
	FVector SpawnLocation;

protected:
	void OnFire();

	void MoveForward(float Value);
	void MoveRight(float Value);

	void TurnAtRate(float Rate);
	void LookAtRate(float Rate);

};
