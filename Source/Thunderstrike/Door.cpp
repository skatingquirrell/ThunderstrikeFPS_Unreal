// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Hero.h"
#include "ThunderstrikeGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Mesh"));
	RootComponent = DoorMesh;

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Component"));
	CollisionComponent->SetupAttachment(DoorMesh);
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ADoor::OnHit);
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADoor::OnHit(UPrimitiveComponent *HitComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &Hit)
{
	AHero* Char = Cast<AHero>(OtherActor);

	if(Char)
	{
		AThunderstrikeGameMode* ThunderstrikeGameMode = Cast<AThunderstrikeGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

		if(ThunderstrikeGameMode)
		{
		UE_LOG(LogTemp, Warning, TEXT("reached door & restart map"));

			ThunderstrikeGameMode->RestartGameplay(true);
		}
	}
}
