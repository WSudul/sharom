#ifndef SHAROM_EXCEPTION_SHAROM_EXCEPTION_HPP_
#define SHAROM_EXCEPTION_SHAROM_EXCEPTION_HPP_

#include <exception>
#include <string>

namespace sharom
{

class SharomException : public std::exception
{
public:
    SharomException(const char *error_msg);
    SharomException(const std::string &error_msg);
    ~SharomException() =default;

    const char *what() const noexcept override;

private:
    const std::string error_msg_;
};

} // namespace sharom

#endif //SHAROM_EXCEPTION_SHAROM_EXCEPTION_HPP_
