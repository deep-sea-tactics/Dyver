#ifndef H_AMP_DISTRIBUTION
#define H_AMP_DISTRIBUTION

#include <memory>

enum AMP_DISTRIBUTION_PRIORITY
{
    ALWAYS_FULFILL,
    DISTRIBUTE
};

class dynamic_amp_request_t
{
public:
    auto get_request() -> _Float64
    {
        return m_request;
    }


    /**
     * @brief Allow this request to use amperage 
     */
    void set_allowance(_Float64 n)
    {
        m_allowance = n;
    }
private:
    /**
     * @brief Priority of the amperage request.
     */
    AMP_DISTRIBUTION_PRIORITY m_priority;

    /**
     * @brief Amount of amperage requested
     */
    _Float64 m_request;

    /**
     * @brief Amount of amperage allowed
     */
    _Float64 m_allowance;
};

#endif