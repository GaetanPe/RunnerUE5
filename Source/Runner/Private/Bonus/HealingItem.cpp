// Fill out your copyright notice in the Description page of Project Settings.


#include "Bonus/HealingItem.h"
#include "../../../../Source/Runner/Public/Charaters/RunCharacter.h"
#include "Components/BoxComponent.h"


// Sets default values
AHealingItem::AHealingItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = SceneComponent;

	HealingTriggerBox = CreateDefaultSubobject< UBoxComponent >(TEXT("HealingTriggerBox"));
	HealingTriggerBox->SetupAttachment(SceneComponent);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(HealingTriggerBox);
	StaticMesh->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));

	
}

// Called when the game starts or when spawned
void AHealingItem::BeginPlay()
{
	Super::BeginPlay();
	StaticMesh->OnComponentBeginOverlap.AddDynamic(this, &AHealingItem::OnTriggerBoxOverlap);
}

void AHealingItem::OnTriggerBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ARunCharacter* RunCharacter = Cast<ARunCharacter>(OtherActor);

	if (RunCharacter)
	{
		RunCharacter->Heal(1);
		Destroy();
	}
}

