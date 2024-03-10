#include "physics2d.h"
#include "math_helper.h"
#include "game.h"
#include <iostream>

namespace Nebel
{
    void PhysicsWorld2D::step(float delta_time)
    {
		for (PhysicObject2D* object : physic_objects)
		{
            if (object->type == PhysicsObjType::DynamicPO)
            {
                // add gravity
                object->force += object->mass * m_gravity;

                // correct y axis
                object->force.y = -object->force.y;
                // apply forces
                object->linear_velocity += object->force / object->mass * delta_time;
            }
            if (object->type != PhysicsObjType::StaticPO) // dyna
            {
                object->transform.position += object->linear_velocity * delta_time;
            }
            
            object->force = glm::vec2(0, 0);
		}
    }
    void PhysicsWorld2D::ResolveCollisions(float delta_time)
    {
		std::vector<CollisionManifold2D> collisions;
        
		for (PhysicObject2D* a : physic_objects)
		{
			for (PhysicObject2D* b : physic_objects) 
			{
				if (a == b)
				{
					break;
				}

				if (!a->shape || !b->shape)
				{
					continue;
				}

				CollisionManifold2D cm = TestCollide(a, b);
                    
				if (cm.HasCollision)
				{
					collisions.push_back(cm);
                }
			}
		}
		for (Solver2D* solver : solvers)
		{
			solver->Solve(collisions, delta_time);
		}
    }
    void PhysicsWorld2D::Synchronize_Transforms()
    {
        for (auto &&i : Game::ecs->components.physics_components)
        {
            i.second.entity->transform2D = i.second.object->transform;
        }
    }
    void PhysicObject2D::addForce(glm::vec2 val)
    {
        force += val;
    }
    void PhysicObject2D::addTorque(float val)
    {
        torque += val;
    }
    void PhysicObject2D::move(glm::vec2 val)
    {
        linear_velocity.x =  val.x;
        linear_velocity.y = -val.y;
    }
    CollisionManifold2D TestCollide(PhysicObject2D* A, PhysicObject2D* B) // AABB vs AABB
    {
        CollisionManifold2D cm;
		cm.A = A;
		cm.B = B;

		cm.HasCollision = false;
		cm.normal = {0,0};
		cm.penetration_depth=0;
		
        glm::vec2 n = cm.B->transform.position - cm.A->transform.position;
        float a_extent_x = (cm.A->shape->max.x - cm.A->shape->min.x) / 2;
        float b_extent_x = (cm.B->shape->max.x - cm.B->shape->min.x) / 2;
        
        float x_overlap = a_extent_x + b_extent_x - abs( n.x );

        if(x_overlap > 0)
        {
            float a_extent_y = (cm.A->shape->max.y - cm.A->shape->min.y) / 2;
            float b_extent_y = (cm.B->shape->max.y - cm.B->shape->min.y) / 2;
        
            float y_overlap = a_extent_y + b_extent_y - abs( n.y );
        
            if(y_overlap > 0)
            {
                if(x_overlap > y_overlap)
                { 
                    if (n.x>0&&n.y<0)
                    {
                        cm.normal = glm::vec2(0, -1);
                        cm.penetration_depth = y_overlap;
                        cm.HasCollision = true;
                    }
                    if (n.x<0&&n.y>0)
                    {
                        cm.normal = glm::vec2(0, 1);
                        cm.penetration_depth = y_overlap;
                        cm.HasCollision = true;
                    }
                    if (n.x>0&&n.y>0)
                    {
                        cm.normal = glm::vec2(0, 1);
                        cm.penetration_depth = y_overlap;
                        cm.HasCollision = true;
                    }
                    if (n.x<0&&n.y<0)
                    {
                        cm.normal = glm::vec2(0, -1);
                        cm.penetration_depth = y_overlap;
                        cm.HasCollision = true;
                    }
                }
                else if(x_overlap < y_overlap)
                {
                    if (n.x>0&&n.y<0)
                    {
                        cm.normal = glm::vec2(1, 0);
                        cm.penetration_depth = x_overlap;
                        cm.HasCollision = true;
                    }
                    if (n.x<0&&n.y>0)
                    {
                        cm.normal = glm::vec2(-1, 0);
                        cm.penetration_depth = x_overlap;
                        cm.HasCollision = true;
                    }
                    if (n.x>0&&n.y>0)
                    {
                        cm.normal = glm::vec2(1, 0);
                        cm.penetration_depth = x_overlap;
                        cm.HasCollision = true;
                    }
                    if (n.x<0&&n.y<0)
                    {
                        cm.normal = glm::vec2(-1, 0);
                        cm.penetration_depth = x_overlap;
                        cm.HasCollision = true;
                    }
                }
                else{
                    cm.HasCollision=false;
                }
                //cm.normal = glm::normalize(n);
            }
        }

        return cm;
    }
	void ImpulseSolver2D::Solve(std::vector<CollisionManifold2D> &collisions, float delta_time)
	{
		for(auto &&cm : collisions)
		{
            glm::vec2 linear_velocity_A;
            glm::vec2 linear_velocity_B;
            if (cm.A->type == PhysicsObjType::DynamicPO)
            {
                linear_velocity_A = cm.A->linear_velocity;
            }else{
                linear_velocity_A = {0,0};
            }
            if (cm.B->type == PhysicsObjType::DynamicPO)
            {
                linear_velocity_B = cm.B->linear_velocity;
            }else{
                linear_velocity_B = {0,0};
            }
			glm::vec2 relative_velocity = linear_velocity_B - linear_velocity_A;
			float velAlongNormal = glm::dot(relative_velocity, cm.normal);
			
			if(!(velAlongNormal > 0))
			{
				float e = min(cm.A->restitution, cm.B->restitution);
				
				float j = -(1 + e) * velAlongNormal;
				j /= cm.A->inv_mass + cm.B->inv_mass;
				
				glm::vec2 impulse = j * cm.normal;
                if(cm.A->type == PhysicsObjType::DynamicPO)
                {
				    cm.A->linear_velocity -= cm.A->inv_mass * impulse;
                }
                if(cm.B->type == PhysicsObjType::DynamicPO)
                {
				    cm.B->linear_velocity += cm.B->inv_mass * impulse;
                }
			}
		}
	}
    void PositionSolver2D::Solve(std::vector<CollisionManifold2D> &collisions, float delta_time)
    {
		std::vector<std::pair<glm::vec2, glm::vec2>> deltas;
        for (CollisionManifold2D cm : collisions)
        {
            float inv_mass_A;
            float inv_mass_B;
            if(cm.A->type== PhysicsObjType::DynamicPO){inv_mass_A = cm.A->inv_mass;}else{inv_mass_A=0.0001f;}
            if(cm.A->type== PhysicsObjType::DynamicPO){inv_mass_B = cm.B->inv_mass;}else{inv_mass_B=0.0001f;}

			const float percent = 0.8f;
			const float slop = 0.01f;

			glm::vec2 correction =  cm.normal * percent
                                    * fmax(cm.penetration_depth - slop, 0.0f)
                                    / (inv_mass_A + inv_mass_B);
		
			glm::vec2 deltaA;
			glm::vec2 deltaB;

			if (cm.A->type==PhysicsObjType::DynamicPO) {
				deltaA = inv_mass_A * correction;
			}

			if (cm.B->type==PhysicsObjType::DynamicPO) {
				deltaB = inv_mass_B * -correction;
			}

			deltas.emplace_back(deltaA, deltaB);
		}
		for (size_t i = 0; i < collisions.size(); i++) {

			if (collisions[i].A->type == PhysicsObjType::DynamicPO) {
				collisions[i].A->transform.position -= deltas[i].first;
			}
			if (collisions[i].B->type == PhysicsObjType::DynamicPO) {
				collisions[i].B->transform.position -= deltas[i].second;
			}
		}
    }
} // namespace Nebel