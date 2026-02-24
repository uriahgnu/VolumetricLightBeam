#include "VolumetricSpotLightComponent.h"
#include "GameFramework/Actor.h"

UVolumetricSpotLightComponent::UVolumetricSpotLightComponent()
{
	VolumetricMeshComponent = nullptr;

	SetVisibility(true);
	SetHiddenInGame(false);
	SetVolumetricScatteringIntensity(0);
}

void UVolumetricSpotLightComponent::OnRegister()
{
	Super::OnRegister();

	CreateVolumetricMesh();

	// Critical: ensures light render state exists
	RecreateRenderState_Concurrent();
}

void UVolumetricSpotLightComponent::OnUnregister()
{
	if (VolumetricMeshComponent)
	{
		VolumetricMeshComponent->DestroyComponent();
		VolumetricMeshComponent = nullptr;
	}

	Super::OnUnregister();
}

void UVolumetricSpotLightComponent::BeginPlay()
{
	Super::BeginPlay();
	SetVolumetricMeshProperties();
}

void UVolumetricSpotLightComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	SetVolumetricMeshProperties();
}

void UVolumetricSpotLightComponent::CreateVolumetricMesh()
{
	if (VolumetricMeshComponent)
		return;

	AActor* Owner = GetOwner();
	if (!Owner)
		return;

	//VolumetricMeshComponent = NewObject<UStaticMeshComponent>(Owner);
	VolumetricMeshComponent = NewObject<UStaticMeshComponent>(
		GetOwner(),
		UStaticMeshComponent::StaticClass(),
		TEXT("VolumetricSpotlightMesh"),
		RF_Transient
	);

	Owner->AddInstanceComponent(VolumetricMeshComponent);

	VolumetricMeshComponent->SetMobility(GetMobility());
	VolumetricMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	VolumetricMeshComponent->SetStaticMesh(VolumetricMesh);
	VolumetricMeshComponent->SetMaterial(0, VolumetricMaterial);

	VolumetricMeshComponent->RegisterComponent();

	VolumetricMeshComponent->AttachToComponent(
		this,
		FAttachmentTransformRules::SnapToTargetIncludingScale
	);

	SetVolumetricMeshProperties();
}

void UVolumetricSpotLightComponent::SetVolumetricMeshProperties()
{
	if (!VolumetricMeshComponent)
		return;

	float EndRadius = (FMath::Tan(FMath::DegreesToRadians(FMath::Clamp(OuterConeAngle + VolumetricAddAngle, 0.f, 89.f))) * AttenuationRadius) + SourceRadius;

	FVector VolumetricMeshScale = FVector(
		EndRadius / 200,
		EndRadius / 200,
		AttenuationRadius / 1000
	);

	VolumetricMeshComponent->SetRelativeTransform(
		FTransform(
			FRotator(-90, 0, 0),
			FVector::ZeroVector,
			VolumetricMeshScale
		)
	);

	FColor Color = LightColor;

	VolumetricMeshComponent->SetCustomPrimitiveDataVector4(
		0,
		FVector4(
			Color.R,
			Color.G,
			Color.B,
			Intensity * VolumetricIntensity * FMath::Max(VolumetricLightShift, 1)
		)
	);

	VolumetricMeshComponent->SetCustomPrimitiveDataFloat(4, SourceRadius);
	VolumetricMeshComponent->SetCustomPrimitiveDataFloat(5, VolumetricLightShift);
	VolumetricMeshComponent->SetCustomPrimitiveDataFloat(6, VolumetricEdgeFalloffPower);
	VolumetricMeshComponent->SetCustomPrimitiveDataFloat(7, MaxDrawDistance);
	VolumetricMeshComponent->SetCustomPrimitiveDataFloat(8, MaxDistanceFadeRange);
}

void UVolumetricSpotLightComponent::SetVolumetricStaticMesh(UStaticMesh* StaticMesh)
{
	if (!VolumetricMeshComponent)
		return;

	VolumetricMesh = StaticMesh;
	VolumetricMeshComponent->SetStaticMesh(VolumetricMesh);
	SetVolumetricMeshProperties();
}

void UVolumetricSpotLightComponent::SetVolumetricMaterial(UMaterialInterface* Material)
{
	if (!VolumetricMeshComponent)
		return;

	VolumetricMaterial = Material;
	VolumetricMeshComponent->SetMaterial(0, VolumetricMaterial);
	SetVolumetricMeshProperties();
}

void UVolumetricSpotLightComponent::SetVolumetricBeamIntensity(float BeamIntensity)
{
	if (!VolumetricMeshComponent)
		return;
	VolumetricIntensity = BeamIntensity;
	SetVolumetricMeshProperties();
}

void UVolumetricSpotLightComponent::SetVolumetricLightShift(float LightShift)
{
	if (!VolumetricMeshComponent)
		return;
	VolumetricLightShift = LightShift;
	SetVolumetricMeshProperties();
}

void UVolumetricSpotLightComponent::SetVolumetricEdgeFalloffPower(float EdgeFalloffPower)
{
	if (!VolumetricMeshComponent)
		return;
	VolumetricEdgeFalloffPower = EdgeFalloffPower;
	SetVolumetricMeshProperties();
}

void UVolumetricSpotLightComponent::SetVolumetricAddAngle(float AddAngle)
{
	if (!VolumetricMeshComponent)
		return;
	VolumetricAddAngle = AddAngle;
	SetVolumetricMeshProperties();
}
