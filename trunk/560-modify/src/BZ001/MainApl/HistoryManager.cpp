#include "StdAfx.h"
#include "HistoryManager.h"

CHistoryManager* CHistoryManager::pInstance = NULL;

CHistoryManager::CHistoryManager(void)
{
}

CHistoryManager::~CHistoryManager(void)
{
}

CHistoryManager* CHistoryManager::getInstance()
{
	if ( pInstance == NULL) {
		pInstance = new CHistoryManager;
	}
	return pInstance;
}