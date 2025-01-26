#include "Adapter.hpp"

Adapter::Adapter()
{}

Adapter::~Adapter()
{}

WebserverConfig* Adapter::Adapt(IConfigContext *root)
{
	std::vector<IConfigDirective *> directives = root->getDirectives();
	int workerConnections;

	for (size_t i = 0; i < directives.size(); ++i)
	{
		if (directives[i]->getType() == WORKER_CONNECTIONS)
		{

		}
	}
}

bool Adapter::CheckContextDependency(IConfigContext *node)
{	
	int type = node->getType();
	if (type == MAIN)
		return (true);
	int parentType = node->getParent()->getType();

	switch (type)
	{
		case HTTP:
			if (parentType == MAIN)
				return (true);
		case SERVER:
			if (parentType == HTTP)
				return (true);
		case EVENTS:
			if (parentType == MAIN)
				return (true);
		case LOCATION:
			if (parentType == SERVER)
				return (true);
		default:
			return (false);
	}
	return (false);
}

bool Adapter::CheckDirectiveDependency(IConfigDirective *dir)
{
	IConfigContext *parent = dir->getParent();
	int parentType = parent->getType();
	int type = dir->getType();

	switch (type)
	{
	case WORKER_PROCESSES:
		if (parentType == MAIN)
			return (true);
	case WORKER_CONNECTIONS:
		if (parentType == MAIN)
			return (true);
	case ERROR_PAGE:
		if (parentType == SERVER || parentType == LOCATION)
			return (true);
	case LISTEN:
		if (parentType == SERVER)
			return (true);
	case SERVER_NAME:
		if (parentType == SERVER)
			return (true);
	case CLIENT_MAX_BODY_SIZE:
		if (parentType == SERVER || parentType == HTTP || parentType == LOCATION)
			return (true);
	case ROOT:
		if (parentType == SERVER || parentType == HTTP || parentType == LOCATION)
			return (true);
	case INDEX:
		if (parentType == SERVER || parentType == HTTP || parentType == LOCATION)
			return (true);
	case ALLOW_METHOD:
		if (parentType == SERVER || parentType == LOCATION)
			return (true);
	case AUTOINDEX:
		if (parentType == SERVER || parentType == HTTP || parentType == LOCATION)
			return (true);
	case FASTCGI_PASS:
		if (parentType == LOCATION)
			return (true);
	case FASTCGI_INDEX:
		if (parentType == LOCATION)
			return (true);
	case FASTCGI_PARAM:
		if (parentType == LOCATION)
			return (true);
	default:
		return (false);
	}
	return (false);
}