#ifndef UTILS_H
#define UTILS_H

#include <glm/glm.hpp>
#include <glm/ext.hpp>

class SpectralDistribution
{
public:
	SpectralDistribution();
	~SpectralDistribution();

	friend std::ostream& operator<<(std::ostream& os, const SpectralDistribution& sd);
	friend SpectralDistribution operator*(float f, const SpectralDistribution& sd);
	float& operator[](const int i);
	SpectralDistribution operator+(const SpectralDistribution& sd) const;
	SpectralDistribution operator-(const SpectralDistribution& sd) const;
	SpectralDistribution operator^(const float& f) const;
	SpectralDistribution operator/(const float& f) const;
	SpectralDistribution operator*(const float& f) const;
	SpectralDistribution operator*(const SpectralDistribution& sd) const;
	SpectralDistribution operator+=(const SpectralDistribution& sd);
	SpectralDistribution operator-=(const SpectralDistribution& sd);
	SpectralDistribution operator/=(const float& f);

	static const int N_WAVELENGTHS = 3;
	static const int MIN_WAVELENGTH = 300;
	static const int MAX_WAVELENGTH = 700;
	float data[N_WAVELENGTHS];
};

struct Material
{
	SpectralDistribution color_diffuse;
	SpectralDistribution color_specular;
	float emittance; // [ 0 (non lightsource), inf]
	float specular_reflectance; // [0 , 1]
	//float diffuse_reflectance; // [0 , 1]
	float transmissivity; // [0 , 1]
	float refraction_index; // [1 (air) , 2.4 (diamond)]
	float polish_power; // High => near perfect reflection
	float clearness_power; // High => near perfect refraction

	static Material air();
};

struct Ray
{
	glm::vec3 position;
	glm::vec3 direction;
	Material material; // The material the ray is travelling in
};

struct IntersectionData
{
	Material material; // Material of the object hit by the ray
	glm::vec3 normal; // Normal of the surface hit by the ray
	float t; // The distance the ray travelled before intersecting
};

#endif // UTILS_H