#pragma once

# include "IConfigContext.hpp"
# include "IConfigDirective.hpp"
# include "Http.hpp"

class ConfigData
{
	private:
		IConfigContext *root_;
		ConfigData();
		void ValidCheck(IConfigContext *root);
		void MainContextCheck(IConfigContext *node);
		void HttpContextCheck(IConfigContext *node);
		void ServerContextCheck(IConfigContext *node);
		void EventsContextCheck(IConfigContext *node);
		void LocationContextCheck(IConfigContext *node);

		void ErrorPageDirectiveCheck(IConfigDirective *dir);
		void WorkerProcessesDirectiveCheck(IConfigDirective *dir);
		void ListenDirectiveCheck(IConfigDirective *dir);
		void ServerNameDirectiveCheck(IConfigDirective *dir);
		void ClientMaxBodySizeDirectiveCheck(IConfigDirective *dir);
		void RootDirectiveCheck(IConfigDirective *dir);
		void IndexDirectiveCheck(IConfigDirective *dir);
		void AllowMethodDirectiveCheck(IConfigDirective *dir);
		void AutoIndexDirectiveCheck(IConfigDirective *dir);
		void ReturnDirectiveCheck(IConfigDirective *dir);

		bool CallDirectiveCheck(std::vector<IConfigDirective *> directives);
		

	public:
		typedef void (ConfigData::*DirectiveCheckFunction)(IConfigDirective *node);
		ConfigData::DirectiveCheckFunction getDirectiveCheckFuntion(int type);
		ConfigData(IConfigContext *root);
		~ConfigData(); // 트리 전부 삭제.
		IConfigContext *GetRoot();
		void SearchTree();
		void SearchTreetest(IConfigContext *root);
};