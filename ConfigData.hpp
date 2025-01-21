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

	public:
		ConfigData(IConfigContext *root);
		~ConfigData(); // 트리 전부 삭제.
		IConfigContext *GetRoot();
		void SearchTree();
		void SearchTreetest(IConfigContext *root);
	//트리에 대한 유효성 검사
	//올바르지 않은 유효성의 트리는 객체 생성 불가
	//트리 순회, 탐색 메서드
	//없는 지시어들을 각 node를 default 기준으로 수정
};