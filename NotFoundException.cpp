/** @file NotFoundException.cpp */
#include "NotFoundException.h"
NotFoundException::NotFoundException(const std::string& message)
	: std::logic_error("Not Found Violated Exception : " + message)
{} // end constructor