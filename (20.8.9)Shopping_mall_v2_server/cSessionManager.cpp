#include "cSessionManager.h"
cSessionManager::cSessionManager()
{
	mSessionCount = 0;
	mHeadNode = NULL;
}
cSessionManager::~cSessionManager()
{

}
void cSessionManager::InputNewSession(cSession* _session,SOCKET _sock, SOCKADDR_IN _sockaddr)
{
	Session_NODE* newnode = new Session_NODE;
	_session->Setsock(_sock);
	_session->SetAddr(_sockaddr);
	newnode->mSessionNode = _session;
	newnode->mNextNode = NULL;
	if (mHeadNode == NULL)
	{
		mHeadNode = newnode;
		
	}
	else
	{
		mTailNode->mNextNode = newnode;
	}
	mTailNode = newnode;
	_session->Onrecv();
	mSessionCount++;
	//변경된 로그를 찍어 보자 
}
void cSessionManager::DeleteSession(cSession* _session)
{
	Session_NODE* cur = mHeadNode;
	if (cur->mSessionNode == _session)
	{
		mHeadNode = mHeadNode->mNextNode; 
	}
	while (cur->mNextNode!=NULL)
	{
		if (cur->mNextNode->mSessionNode == _session)
		{
			cur->mNextNode = cur->mNextNode->mNextNode;
		}
		cur = cur->mNextNode;
	}
	mSessionCount--;
	// 변경된 로그를 찍어 보자 
}