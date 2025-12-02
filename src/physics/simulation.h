#ifndef H_SIMULATION
#define H_SIMULATION

#include <cstdint>
#include <vector>

#include "body.h"
#include "shape.h"
#include "utils.h"
#include "denseutils.h"

const uint64_t DEFAULT_TICK_MS = 10;

class simulation_t
{
public:
    void step(uint64_t ticks);

    double tick_s()
    {
        return (m_ticksize * utils::MILLIU_T_U);
    }
private:
    /**
     * @brief Vector of physically simulated bodies with
     * specific shapes
     * 
     */
    std::vector<body_t> m_bodies{{}};

    /**
     * @brief Ticks- a unit of time between physics updates
     * 
     */
    uint64_t m_ticksize{DEFAULT_TICK_MS};
};

#endif