#include "sharom_exception.hpp"

namespace sharom
{

SharomException::SharomException(const char *error_msg) : error_msg_{error_msg} {};

SharomException::SharomException(const std::string &error_msg) : error_msg_{error_msg} {};

const char *SharomException::what() const noexcept
{
    return error_msg_.c_str();
}
} // namespace sharom
