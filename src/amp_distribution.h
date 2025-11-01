#ifndef H_AMP_DISTRIBUTION
#define H_AMP_DISTRIBUTION

#include <memory>
#include <vector>
#include <cstdint>
#include <cmath>

enum AMP_REQUEST_PRIORITY
{
    /**
     * @brief This request will always be fulfilled, no matter how thin it spreads amperage.
     * For components such as computers, sensors, and the arm
     */
    ALWAYS_FULFILL,

    /**
     * @brief This request can have a variable amperage. This is mostly reserved for thrusters.
     * 
     */
    DISTRIBUTE
};

/**
 * @brief Dynamic Amp Request object
 * 
 */
class dynamic_amp_request_t
{
public:
    /**
     * @brief Construct a new dynamic amperage request object
     * 
     * @param request The starting request that this object is making.
     * @param priority The priority of the request.
     */
    dynamic_amp_request_t(const _Float64 request, const AMP_REQUEST_PRIORITY priority)
    {
        m_request = request;
        m_allowance = 0.0;
        m_priority = priority;
    }

    /**
     * @brief Construct a new dynamic amperage request object using default parameters
     * 
     */
    dynamic_amp_request_t()
    {
        m_request = 0.0;
        m_allowance = 0.0;
        m_priority = AMP_REQUEST_PRIORITY::DISTRIBUTE;
    }

    auto get_request() -> _Float64
    {
        return m_request;
    }

    auto get_priority() -> AMP_REQUEST_PRIORITY
    {
        return m_priority;
    }

    auto get_allowance() -> _Float64&
    {
        return m_allowance;
    }

    /**
     * @brief Allow this request to use amperage.
     * Will not set the "computed" property.
     */
    void set_allowance(_Float64 n)
    {
        m_allowance = n;
    }

    void reset_allowance()
    {
        m_allowance = 0.0;
    }

    /**
     * @brief Set this request's "computed" status to "true"
     * 
     */
    void mark_computed()
    {
        m_computed = true;
    }

    /**
     * @brief Set the request's computed variable
     * 
     * @param to The value to set this request's computed status to
     */
    void mark_computed(bool to)
    {
        m_computed = to;
    }

    auto is_computed() -> bool
    {
        return m_computed;
    }

    /**
     * @brief Shorthand for `this->get_allowance() == this->get_request()`
     */
    auto is_fulfilled() -> bool
    {
        return (m_request == m_allowance);
    }
private:
    /**
     * @brief Whether or not the dynamic amperage request has been computed
     * 
     */
    bool m_computed{false};

    /**
     * @brief Priority of the amperage request.
     */
    AMP_REQUEST_PRIORITY m_priority{AMP_REQUEST_PRIORITY::DISTRIBUTE};

    /**
     * @brief Amount of amperage requested
     */
    _Float64 m_request{0.0};

    /**
     * @brief Amount of amperage allowed
     */
    _Float64 m_allowance{0.0};
};

class amp_distributor_t
{
public:
    amp_distributor_t(const _Float64 max_allowance)
    {
        m_max_allowance = max_allowance;
        m_active_requests = {};
    }

    /**
     * @brief Produce a dynamic amperage request and recieve a handle to it
     * 
     * @param request The starting amperage request
     * @param priority The priority of the request
     * @return dynamic_amp_request_t& 
     */
    auto invoke_request(const _Float64 request, const AMP_REQUEST_PRIORITY priority) -> std::shared_ptr<dynamic_amp_request_t>;

    auto tally_by_priority(const AMP_REQUEST_PRIORITY which) -> uint32_t;

    /**
     * @brief Finds the minimum dynamic amperage request that is the priority "DISTIBUTE"
     * 
     * @return dynamic_amp_request_t 
     */
    auto min_variable_request() -> std::shared_ptr<dynamic_amp_request_t>;

    /**
     * @brief Compute and fulfill requests
     * 
     */
    void compute();
private:
    /**
     * @brief The total amount of amperage that this distributor is entitled to give out.
     * 
     */
    _Float64 m_max_allowance{0.0};

    /**
     * @brief A vector of active amperage requests.
     * 
     */
    std::vector<std::shared_ptr<dynamic_amp_request_t>> m_active_requests{{}};
};

#endif