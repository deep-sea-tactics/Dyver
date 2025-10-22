#include "amp_distribution.h"

auto amp_distributor_t::invoke_request(const _Float64 request, const AMP_REQUEST_PRIORITY priority) -> std::shared_ptr<dynamic_amp_request_t>
{
    std::shared_ptr<dynamic_amp_request_t> new_request = std::make_shared<dynamic_amp_request_t>(request, priority);
    m_active_requests.push_back(new_request);

    compute();

    return new_request;
}

auto amp_distributor_t::tally_by_priority(const AMP_REQUEST_PRIORITY which) -> uint32_t
{
    uint32_t res;

    for (auto request : m_active_requests)
    {
        if (request->get_priority() != which)
        {
            continue;
        }

        res++;
    }

    return res;
}

auto amp_distributor_t::min_variable_request() -> std::shared_ptr<dynamic_amp_request_t>
{
    _Float64 found_min = INFINITY;
    std::shared_ptr<dynamic_amp_request_t> p_found = nullptr;

    for (auto request : m_active_requests)
    {
        if (request->get_priority() != AMP_REQUEST_PRIORITY::DISTRIBUTE) continue;
        if (request->get_request() > found_min) continue;

        found_min = request->get_request();
        p_found = request;
    }

    return p_found;
}

void amp_distributor_t::compute()
{
    // Splitting the cake between requests
    _Float64 cake = m_max_allowance;

    for (auto request : m_active_requests)
    {
        request->mark_computed(false);
        request->reset_allowance();
    }

    for (auto request: m_active_requests)
    {
        if (request->get_priority() != AMP_REQUEST_PRIORITY::ALWAYS_FULFILL) continue;

        cake -= request->get_request(); // "Always Fulfilled Requests" must be fulfilled
        request->set_allowance(request->get_request());
        request->mark_computed(); // Nothing more to do to this request.
    }

    std::shared_ptr<dynamic_amp_request_t> p_min_request = min_variable_request();

    if (p_min_request == nullptr) return; // Also implies that there are no dynamic requests

    uint32_t ndynamic_requests = tally_by_priority(AMP_REQUEST_PRIORITY::DISTRIBUTE);
    uint32_t unfulfilled_requests = ndynamic_requests;
    _Float64 distributed;
    
    // Brief: Start by evenly distributing amperage, collect leftovers from smaller
    // requests, then distribute that among the other requests.
    for (int i = 0; i < ndynamic_requests; i++)
    {
        for (auto request : m_active_requests)
        {
            distributed = cake/unfulfilled_requests; // Split the cake

            if (request->get_priority() != AMP_REQUEST_PRIORITY::DISTRIBUTE) continue;
            if (request->is_computed() == true) continue; // Already satisfied, can skip
            
            request->set_allowance(distributed); // Helps determine if it's fulfilled.

            _Float64 diff = distributed - request->get_request(); // Leftovers

            if (diff > 0) // Nothing left-over if it's negative
            {
                request->set_allowance(request->get_request()); // Had some to spare, so crop
            }

            if (request->is_fulfilled() == true)
            {
                request->mark_computed(); // Fulfilled! Not taking any more amperage away from this.
                unfulfilled_requests -= 1; // One request has been fulfilled
                cake -= request->get_request();
                continue;
            }
        }
    }

    for (auto request : m_active_requests)
    {
        if (request->is_computed() == true) continue; // Already computed
        request->mark_computed(); // Processed to its full ability.
    }
}