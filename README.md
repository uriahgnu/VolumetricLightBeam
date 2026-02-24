# Volumetric Light Beam

A plugin for UE 5.7+ that adds a VolumetricSpotLightComponent which provides high quality performant alternative to using volumetric scattering.

Current features:
- Based on the LightCone included in the Volumetrics plugin, located here: /Volumetrics/Content/Primitives/Lightcone
- VolumetricSpotLightComponent works just like a SpotLightComponent with additional volumetric mesh rendering.
- Uses Custom Primitive Data instead of Material Instance Dynamic for improved performance.
- Fake Lighting as an optional shader switch that makes objects within the light cone appear lit beyond the Spot Light Max Draw Distance.

Future features:
- SpotLight Actor C++ class.
- RectLightComponent C++ class.
- Editor Utility to mass replace existing SpotLight actors.
- Dust effects.
- Dynamic shadow mask.
- More examples, flashlight beam, shadow mask, raymarching, etc.
