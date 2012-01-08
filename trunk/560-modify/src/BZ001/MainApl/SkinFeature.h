#ifndef _SKINFEATURE_H__
#define _SKINFEATURE_H__

//Application    Interface
#ifdef __cplusplus  
extern "C"
{
#endif
	
#define  ERROR_UNKNOWNFILEFORMAT  0x00001
#define  ERROR_WRONGPASSWORD	  0x00002
	////////////////////////////////////////////////////////////////////////////
	
	//��ʼ��skinfeature�����
	BOOL __stdcall InitializeSkin();
	
	//����һ��Ƥ���ļ�(.rss �ļ�) pszFileName ΪҪװ�ص�skinfeatureƤ���ļ�
	BOOL __stdcall LoadSkinFile(LPCTSTR  pszFileName, LPCTSTR pszPassWord = NULL);
	
	//����Դ����Ƥ��
	BOOL __stdcall LoadSkinFromResource(HINSTANCE hInstance, LPCTSTR pszResourceName,
		LPCTSTR pszResourceType, LPCTSTR pszFileName, LPCTSTR pszPassWord = NULL);
	
	//�Ƴ�Ƥ��
	BOOL __stdcall RemoveSkin();
	
	//�˳�skinfeature����⣬�ͷ��ڴ���Դ��
	BOOL __stdcall UnLoadSkin();
	
	//�������ʹ������ԴID
	BOOL __stdcall SetShapeWindowSkin(HWND hWnd,int nResID);
	
	//����Ƥ��ɫ�� ����ΪҪת���ɵ�Ƥ����ɫ
	void __stdcall SetColorize( COLORREF color );
	
	//��ָ���Ĵ��ڽ��л���
	//hWnd			: ָ���Ĵ��ھ��
	//pszName	    : ��Ҫ����Ƥ����ʽ�Ŀ�������
	void __stdcall SetWindowSkinHwnd(HWND hWnd, LPCTSTR pszName = NULL);
	
	//����ȥ��ָ�����ڵ�Ƥ����ʽ.
	//hWnd			: ָ���Ĵ��ھ��
	//bChildNoSkin	: �Ƿ�Ըô����е��Ӵ���ȥ��Ƥ��
	void __stdcall SetWindowNoSkinHwnd(HWND hWnd, BOOL bChildNoSkin = TRUE);
	
	//��ָ���Ĵ���ȥ��Ƥ��,����Ҫ�ٴλ�������ͨ��SetWindowSkinHwnd����Ƥ����ʽ����
	void __stdcall RemoveWindowSkinHwnd(HWND hWnd);
	
	//�����Ƿ���Ҫ�û��Լ����ƶԻ��򱳾�.
	void __stdcall SetDialogEraseBkgnd(HWND hWnd, BOOL bErase = TRUE);
	
	BOOL __stdcall SetWindowSkinResID(HWND hWnd, int nResID);
	
	//���ò���Ҫ�����Ĳ˵���������û��Ի�˵�ʱʹ��
	void __stdcall SetMenuNoSkinHwnd(HMENU hMenu);

	void  __stdcall DrawSkinImageRes(HDC hdc, RECT rect, LPCTSTR pszResName, 
		int nLeftWidth, int nRightWidth, int nTopHeight, int nBottomHeight,
		BOOL bStretchAll = FALSE, COLORREF clrTrans = 0xff00ff, BOOL bTrans = TRUE);
	
	void  __stdcall DrawSkinImage(HDC hdc, RECT rect, HBITMAP hbitmap, 
		int nLeftWidth, int nRightWidth, int nTopHeight, int nBottomHeight,
		BOOL bStretchAll = FALSE, COLORREF clrTrans = 0xff00ff, BOOL bTrans = TRUE);

#ifdef __cplusplus
}
#endif  //__cplusplus

#endif






















