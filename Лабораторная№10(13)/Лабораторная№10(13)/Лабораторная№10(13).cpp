// �������������10(13).cpp: ���������� ����� ����� ��� ����������.
//��� 209

#include "stdafx.h"
#include "�������������10(13).h"

#define MAX_LOADSTRING 100

// ���������� ����������:
HINSTANCE hInst;								// ������� ���������
TCHAR szTitle[MAX_LOADSTRING];					// ����� ������ ���������
TCHAR szWindowClass[MAX_LOADSTRING];			// ��� ������ �������� ����
static int winCount = 0;
HWND begin_hWnd;
HWND mass_hWnd[7];

// ��������� ���������� �������, ���������� � ���� ������ ����:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int); //��������� ��������� ���������� � ������� ������� ����.
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM); /*���������� ������� �-�
															LRESULT-�������� ��������� ��������� ���������.
		������� WindowProc - ������������ ���������� �������, ������� ������������ ���������, ������������ � ����. */
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM); //������� About ����� ���������� �������� ��� ��������� ���������, ���������� ���� �������.

int APIENTRY _tWinMain (_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: ���������� ��� �����.
	MSG msg; //�������� ���������� � ��������� �� ������� ��������� ������.
	HACCEL hAccelTable; //���������� ������� ����������� 

	// ������������� ���������� �����
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING); /*��������� ������ ������ �� ������������ �����,
																�������� ������ � ����� � ��������� � ����� ������ ������������ ����.*/
	LoadString(hInstance, IDC_MY1013, szWindowClass, MAX_LOADSTRING); /*���������� ���������� ������, ����������� ���� �������� �������� � ���� ������ ������.
																��������� ������������� ������������� ������, ������� ����� ���������.
																��������� �� �����, ������� ������ ������.
																���������� ������ ������	*/
	MyRegisterClass(hInstance); //����������� �������� ������ 

	// ��������� ������������� ����������:
	if (!InitInstance (hInstance, nCmdShow)) //������������ ������������� ���������� � ��������� ���������� ���������� hInstance
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY1013)); /*��������� �������� ������� ������-�����������
	���������� ������, ����������� ���� �������� �������� ����������� ������� ������-�����������.
	��������� �� ���������� ������ � ����� � �����, ������� �������� ��� ����������� ������� ������-�����������.*/

	/*���������� ���� ��������� ���������*/
	while (GetMessage(&msg, NULL, 0, 0))
		
	{	
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		{
			TranslateMessage(&msg); //��������� ��������� ����������� ������ � ���������� ���������
			DispatchMessage(&msg); //������������, ����� ��������� ���������, ����������� �������� GetMessage
		}
	}
	return (int) msg.wParam;
}

/* �������: MyRegisterClass()
	����������: ������������ ����� ����.
	�����������:
    ��� ������� � �� ������������� ���������� ������ � ������, ���� �����, ����� ������ ���
    ��� ��������� � ��������� Win32, �� �������� ������� RegisterClassEx'
    ������� ���� ��������� � Windows 95. ����� ���� ������� ����� ��� ����,
    ����� ���������� �������� "������������" ������ ������ � ���������� ����� � ����.*/
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex; //�������� ���������� � ������ ����
	wcex.cbSize = sizeof(WNDCLASSEX); //������ ����� ����.
	wcex.style			= CS_HREDRAW | CS_VREDRAW; /*CS_HREDRAW	�������������� ��� ����, ���� ����������� ���
												   ����������� ������� �������� ������ ��� ������ ������� �������.*/
	wcex.lpfnWndProc	= WndProc; //���������� ��� ������� ���������.
	wcex.cbClsExtra		= 0;  //�������������� ������ ��� ������.
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance; /*��������� ����������, ����������� � ������ �����.
										������ ��� ���� ����������.*/
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY1013));/*��������� ��������� ������ ������ �� ������������ �����, 
																  ���������� � ����������� ����������.
	���������� ���������� ������, ���������� ����������� ����, ������ �������� ����� ��������.
	��������� �� ������ � ����������� �����, c��������� ��� ������� ������, ������� ����� ��������. 
	������ MAKEINTRESOURCE ����������� ������������� �������� � ��� �������, ������������ � ��������� ���������� ��������*/
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW); //������������� ��� ������� � ���� ����������.
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);  //����� ����� ��� �������� ����. HBR-���������� �����
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_MY1013); //������ ���� ��� ���� ����������.
	wcex.lpszClassName	= szWindowClass; //��������� �� ������� �����.
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

/*�������: InitInstance(HINSTANCE, int)
  ����������: ��������� ��������� ���������� � ������� ������� ����.
  �����������:
       � ������ ������� ���������� ���������� ����������� � ���������� ����������, � �����
       ��������� � ��������� �� ����� ������� ���� ���������.*/
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   //���������� ����.

   hInst = hInstance; // ��������� ���������� ���������� � ���������� ����������
   
   // ������� �������������, ������������� ��� �������� ����. 
   HWND hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
   begin_hWnd = hWnd;
   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);//������������� ��������� ������ ������������� ����, ���������� ����, ��������� ������ ����
   UpdateWindow(hWnd);//��������� ���������� ������� ���������� ����,

   return TRUE;
}

/*�������: WndProc(HWND, UINT, WPARAM, LPARAM)
 ����������:  ������������ ��������� � ������� ����.
 WM_COMMAND	- ��������� ���� ����������
 WM_PAINT	-��������� ������� ����
 WM_DESTROY	 - ������ ��������� � ������ � ���������.
*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;//�������� ���������� ��� ����������
	HDC hdc;//���������� ��������� ���������� 
	
	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// ��������� ����� � ����:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);//������� ��������� ���������� ���� �� ������� ������� ����� �������.
			break;
			/* ���������� ������, ����������� ���� �������� �������� ������ ����������� ����.
			���������� ������ ����������� ����
			���������� ����, ������� ������� ���������� �����.
			��������� �� ��������� ����������� ����			*/
		case IDM_EXIT:
			if (IDOK == MessageBox(hWnd, _T("������ ������� ���������?"), _T("�������"),
				MB_OKCANCEL | MB_ICONQUESTION | MB_DEFBUTTON2))
				SendMessage(hWnd, WM_DESTROY, NULL, NULL); 
			DestroyWindow(hWnd);// ��������� �������� ����, ���������� ��� ���������� ����
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);//������������ ��������� �� ��������� ������ ��������� ����, ������� ���������� �� �����������
		}
		break;
	
	case WM_LBUTTONDOWN:
		SetWindowText(hWnd, _T ("������� ����"));
		break;

	case WM_PAINT://���������� ���� � ���, ��� �p������� ��p�p������� ��� ��� ����� ��� ������� ������������.
		hdc = BeginPaint(hWnd, &ps);
		// TODO: �������� ����� ��� ���������...
		EndPaint(hWnd, &ps);
		break;

	case WM_RBUTTONDOWN:
		{	 //for (winCount = 0;winCount < 3;winCount++) {
			 if (winCount >= 7)
		 {		 MessageBox(hWnd, L"������ ������� ����� 7 ����", L"", MB_OKCANCEL | MB_ICONQUESTION);
			 		 break;
		 }
			 			 WNDCLASS w;
						 memset(&w, 0, sizeof(WNDCLASS));
						 w.lpfnWndProc = WndProc;
						 w.hInstance = hInst;
						 w.hbrBackground = (HBRUSH)(COLOR_WINDOW);
						 w.lpszClassName = L"ChildWClass";
						 w.hCursor = LoadCursor(NULL, IDC_IBEAM);
						 RegisterClass(&w);
						
						 HWND child;
						 child = CreateWindowEx(1, L"ChildWClass", (LPCTSTR)NULL,
							 WS_OVERLAPPEDWINDOW | WS_SYSMENU | WS_OVERLAPPEDWINDOW | WS_CAPTION | WS_HSCROLL
							 | WS_BORDER | WS_VISIBLE, winCount * 20 + 200, winCount * 20 + 200,
							 400, 500, hWnd, (HMENU)(int)(0), hInst, NULL);
						 ++winCount;
						 SetWindowText(child, _T("�������� ����"));
						 ShowWindow(child, SW_NORMAL);
			 //  }
	}
	break;
		
	case WM_CLOSE: //���������� � ������ �� ���������
		if (hWnd == begin_hWnd)
		{
		if (IDOK == MessageBox(hWnd, _T("������ ������� ���������?"), _T("�������"), MB_OKCANCEL | MB_ICONQUESTION | MB_DEFBUTTON2))
			SendMessage(hWnd, WM_DESTROY, NULL, NULL);
		}
		else
			DestroyWindow(hWnd);
		winCount--;
		break;
		
	case WM_DESTROY:
		if (hWnd == begin_hWnd)
			PostQuitMessage(0);
		else

			break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

return 0;
}

// ���������� ��������� ��� ���� "� ���������".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
/*������� About ����� ���������� �������� ��� ��������� ���������, ���������� ���� �������.
	HWND  Windows-��������� ���� �������;
	UINT  � ��� ���������;
	WPARAM, LPARAM  � ��� ���������, �������������� ���������.
	����� �������� ��� ��� �������� ���������.*/
{
	UNREFERENCED_PARAMETER(lParam); //�������� �������� �������������� ����������� � ������� ����������, �� ������� ��� ������ (�������������� ����������)
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));/*���������� ��������� ���������� ����, 
			��������� ����������� ����, ��������, ������������ ���������� �� �������, ��������� ���������� ����*/
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
