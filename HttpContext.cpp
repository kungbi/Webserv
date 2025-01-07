#include "HttpContext.hpp"

HttpContext::HttpContext()
{

}

ContextType HttpContext::GetType() const
{
	return (type_);
}

bool HttpContext::IsValid() const
{

}