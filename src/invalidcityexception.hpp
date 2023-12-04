#ifndef INVALID_CITY_EXCEPTION_H
#define INVALID_CITY_EXCEPTION_H

#include <exception>
#include <string>

class InvalidCityException : public std::exception {
 public:
  InvalidCityException(std::string errorMessage) : errorMessage_(errorMessage) {}

  std::string GetError() const {
    return "InvalidCityException: " + errorMessage_;
  }

 private:
  std::string errorMessage_;

};

#endif