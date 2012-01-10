#pragma once

class CHistoryManager
{
public:

	static CHistoryManager* getInstance();
	~CHistoryManager(void);
protected:
	CHistoryManager(void);
private:
	static CHistoryManager *pInstance;
};
