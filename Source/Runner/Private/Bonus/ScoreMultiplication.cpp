// Fill out your copyright notice in the Description page of Project Settings.


#include "Bonus/ScoreMultiplication.h"
#include "../../../../Source/Runner/Public/Charaters/RunCharacter.h"
#include "Components/BoxComponent.h"



// Sets default values
AScoreMultiplication::AScoreMultiplication()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = SceneComponent;

	ScoreMultTriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("ScoreMultTriggerBox"));
	ScoreMultTriggerBox->SetupAttachment(SceneComponent);

	MultiplicationMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MultMesh"));
	MultiplicationMesh->SetupAttachment(ScoreMultTriggerBox);
}

float AScoreMultiplication::GetMultiplier()
{
	return multiplier;
}

// Called when the game starts or when spawned
void AScoreMultiplication::BeginPlay()
{
	Super::BeginPlay();

	ScoreMultTriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AScoreMultiplication::OnTriggerBoxOverlap);
	
}

// Called every frame
void AScoreMultiplication::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AScoreMultiplication::OnTriggerBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ARunCharacter* RunCharacter = Cast<ARunCharacter>(OtherActor);
	if (RunCharacter)
	{
		multiplier *= 2;
		Destroy();
	}
}

