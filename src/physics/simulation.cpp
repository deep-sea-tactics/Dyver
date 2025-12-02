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

void simulation_t::step(uint64_t ticks)
{
    for (auto body: m_bodies)
    {
        const double tick_in_s = tick_s();
        body.get_ang_vel() += (body.get_ang_accel() * tick_in_s);
        body.get_lin_vel() += (body.get_lin_accel() * tick_in_s);

        body.get_pos() += (body.get_lin_vel() * tick_in_s);
        
        Eigen::Quaterniond dq = quat_from_euler(body.get_ang_vel());

        body.get_rot() *= dq;
    }
}