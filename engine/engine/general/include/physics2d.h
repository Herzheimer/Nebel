#pragma once

#include "interfaces.h"
#include "transform.h"
#include <vector>

namespace Nebel
{
    struct ObjectShape2D
    {};
    struct AABB2D : ObjectShape2D
    {
        glm::vec2 min;
        glm::vec2 max;
    };
    enum class PhysicsObjType
    {
        DynamicPO,
        KinematicPO,
        StaticPO,
    };
    //enum class ForceMode2D
    //{
    //    Force2D,
    //    Impulse2D,
    //};
    //TODO Add orientation;
    struct PhysicObject2D
    {
        PhysicsObjType type = PhysicsObjType::DynamicPO;
        bool isTrigger = false;
        Transform2D transform;
        //ObjectShape2D* shape;
        AABB2D* shape;
        glm::vec2 force;
        glm::vec2 linear_velocity;
        float torque;
        float angular_vel;
        float restitution;
        float mass;
        float inv_mass;
        float static_friction = 0.6f;
        float dynamic_friction = 0.4f;
        void addForce(glm::vec2 val);
        void addTorque(float val);
        void move(glm::vec2 val);
        //void addForce(glm::vec2 force, ForceMode2D mode); // TODO
    };
    struct CollisionManifold2D {
        PhysicObject2D* A;
        PhysicObject2D* B;
        glm::vec2 normal;
        float penetration_depth;
        bool HasCollision;
    };
    struct Solver2D
    {
	    virtual void Solve(std::vector<CollisionManifold2D> &collisions, float delta_time) = 0;
    };
    struct PhysicsWorld2D : PhysicsWorld
    {
        std::vector<PhysicObject2D*> physic_objects;
        std::vector<Solver2D*> solvers;
	    glm::vec2 m_gravity = glm::vec2(0, -9.81f);
        void step(float delta_time) override;
        void ResolveCollisions(float delta_time) override;
        void Synchronize_Transforms() override;
    };
    struct ImpulseSolver2D : Solver2D
    {
        void Solve(std::vector<CollisionManifold2D> &collisions, float delta_time) override;
    };
    struct PositionSolver2D : Solver2D
    {
        void Solve(std::vector<CollisionManifold2D> &collisions, float delta_time) override;
    };
    CollisionManifold2D TestCollide(PhysicObject2D* A, PhysicObject2D* B);
} // namespace Nebel
