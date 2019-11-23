#pragma once

#include <boost/outcome.hpp>

#include <string_view>

template< typename ResultType >
using Result = boost::outcome_v2::result< ResultType, std::string_view >;
