#include "amp_distribution.h"

auto amp_distributor_t::invoke_request(const _Float64 request, const AMP_REQUEST_PRIORITY priority) -> dynamic_amp_request_t&
{
    const dynamic_amp_request_t new_request = dynamic_amp_request_t(request, priority);
    m_active_requests.push_back(new_request);

    const int32_t location = m_active_requests.size()-1;

    return m_active_requests[location];
}

auto amp_distributor_t::tally_by_priority(const AMP_REQUEST_PRIORITY which) -> uint32_t
{
    uint32_t res;

    for (auto request : m_active_requests)
    {
        if (request.get_priority() != which)
        {
            continue;
        }

        res++;
    }

    return res;
}

auto amp_distributor_t::min_variable_request() -> dynamic_amp_request_t*
{
    _Float64 found_min = INFINITY;
    dynamic_amp_request_t *p_found = nullptr;

    for (auto request : m_active_requests)
    {
        if (request.get_priority() != AMP_REQUEST_PRIORITY::DISTRIBUTE) continue;
        if (request.get_request() > found_min) continue;

        found_min = request.get_request();
        p_found = &request;
    }

    return p_found;
}

void amp_distributor_t::compute()
{
    // Splitting the cake between requests
    _Float64 cake = m_max_allowance;

    for (auto request : m_active_requests)
    {
        request.mark_computed(false);
        request.reset_allowance();
    }

    for (auto request: m_active_requests)
    {
        if (request.get_priority() != AMP_REQUEST_PRIORITY::ALWAYS_FULFILL) continue;

        cake -= request.get_request(); // "Always Fulfilled Requests" must be fulfilled
        request.set_allowance(request.get_request());
        request.mark_computed(); // Nothing more to do to this request.
    }

    dynamic_amp_request_t *p_min_request = min_variable_request();

    if (p_min_request == nullptr) return; // Also implies that there are no dynamic requests

    uint32_t ndynamic_requests = tally_by_priority(AMP_REQUEST_PRIORITY::DISTRIBUTE);
    _Float64 distributed;

    // IF YOU THINK OF A MATH formula that can do this in a simpler manner,
    // please implement it.
    //
    // Brief: Start by evenly distributing amperage, collect leftovers from smaller
    // requests, then distribute that among the other requests.
    for (int i = 0; i < ndynamic_requests; i++)
    {
        for (auto request : m_active_requests)
        {
            distributed = cake/ndynamic_requests; // Split the cake

            if (request.get_priority() != AMP_REQUEST_PRIORITY::DISTRIBUTE) continue;
            if (request.is_computed() == false) continue; // Already satisfied
            
            _Float64 diff = distributed - request.get_request(); // Leftovers

            if (request.is_fulfilled())
            {
                request.mark_computed(); // Fulfilled! Not taking any more amperage away from this.
            }

            cake -= distributed; // Fair share
            request.set_allowance(request.get_allowance() + distributed);


            if (diff < 0) continue; // The request has nothing to offer if it's negative.
            cake += diff; // Add leftovers
        }
    }
}