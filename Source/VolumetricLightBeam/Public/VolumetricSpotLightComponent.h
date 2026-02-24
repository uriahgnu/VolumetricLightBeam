#pragma once

#include "CoreMinimal.h"
#include "Components/SpotLightComponent.h"
#include "Components/StaticMeshComponent.h"
#include "VolumetricSpotLightComponent.generated.h"

UCLASS(ClassGroup = (Lights), meta = (BlueprintSpawnableComponent))
class VOLUMETRICLIGHTBEAM_API UVolumetricSpotLightComponent : public USpotLightComponent
{
	GENERATED_BODY()

public:

	UVolumetricSpotLightComponent();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Light")
	UStaticMesh* VolumetricMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Light")
	UMaterialInterface* VolumetricMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Light")
	float VolumetricIntensity = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Light")
	float VolumetricLightShift = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Light")
	float VolumetricEdgeFalloffPower = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Light")
	float VolumetricAddAngle = 0.0f;

protected:

	virtual void OnRegister() override;
	virtual void OnUnregister() override;
	virtual void BeginPlay() override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif // WITH_EDITOR

	UPROPERTY(Transient, DuplicateTransient)
	UStaticMeshComponent* VolumetricMeshComponent;

	void CreateVolumetricMesh();
	void SetVolumetricMeshProperties();

public:

	UFUNCTION(BlueprintCallable, Category = "Volumetric Light Beam")
	void SetVolumetricStaticMesh(UStaticMesh* StaticMesh);

	UFUNCTION(BlueprintCallable, Category = "Volumetric Light Beam")
	void SetVolumetricMaterial(UMaterialInterface* Material);

	UFUNCTION(BlueprintCallable, Category = "Volumetric Light Beam")
	void SetVolumetricBeamIntensity(float BeamIntensity);

	UFUNCTION(BlueprintCallable, Category = "Volumetric Light Beam")
	void SetVolumetricLightShift(float LightShift);

	UFUNCTION(BlueprintCallable, Category = "Volumetric Light Beam")
	void SetVolumetricEdgeFalloffPower(float EdgeFalloffPower);

	UFUNCTION(BlueprintCallable, Category = "Volumetric Light Beam")
	void SetVolumetricAddAngle(float AddAngle);
};