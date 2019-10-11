// Sphere Geaometrical Primitive class
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "Prim.h"
/**
 * @brief Sphere Geaometrical Primitive class
 */
class CPrimSphere : public CPrim
{
public:
    /**
     * @brief Constructor
     * @param center Position of the center of the sphere
     * @param radius Radius of the sphere
     */
    CPrimSphere(Vec3f center, float radius, std::shared_ptr<IShader> pShader)
        : CPrim(pShader), m_center(center), m_radius(radius)
    {
    }
    virtual ~CPrimSphere(void) = default;

    virtual bool Intersect(Ray &ray) override
    {
        Vec3f diff = ray.org - m_center;
        float a = ray.dir.dot(ray.dir);
        float b = 2 * ray.dir.dot(diff);
        float c = diff.dot(diff) - m_radius * m_radius;
        float inRoot = b * b - 4 * a * c;
        if (inRoot < 0)
            return false;
        float root = sqrtf(inRoot);
        float dist = (-b - root) / (2 * a);
        if (dist > ray.t)
            return false;
        if (dist < Epsilon)
        {
            dist = (-b + root) / (2 * a);
            if (dist < Epsilon || dist > ray.t)
                return false;
        }
        ray.t = dist;
        ray.hit = this;
        return true;
    }
    virtual Vec3f GetNormal(const Ray &ray) const override
    {
        return normalize(ray.org + ray.dir * ray.t - m_center);
    }

private:
    Vec3f m_center;
    float m_radius;
};
