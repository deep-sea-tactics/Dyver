/**
 * @file simulation.cpp
 * @author Yevgenya Cooonan (yacoonan@gmail.com)
 * @brief Active newtonian simulation
 * @date 2025-11-07
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "body.h"
#include "physics/shape.h"
#include "simulation.h"
#include "utils.h"

#include <Eigen/Dense>

template<typename S>
void simulation_t<S>::step(uint64_t ticks)
{
    for (auto body: m_bodies)
    {
        const double tick_in_s = tick_s();
        body.m_ang_vel += (body.m_ang_accel * tick_in_s);
        body.m_lin_vel += (body.m_lin_accel * tick_in_s);

        body.m_pos += (body.m_lin_vel * tick_in_s);
        
        
        Eigen::Quaterniond dq = Eigen::Quaterniond();

        body.m_rot += dq;
    }
}