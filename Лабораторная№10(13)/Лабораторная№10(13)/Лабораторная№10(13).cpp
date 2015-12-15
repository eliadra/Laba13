// Лабораторная№10(13).cpp: определяет точку входа для приложения.
//стр 209

#include "stdafx.h"
#include "Лабораторная№10(13).h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;								// текущий экземпляр
TCHAR szTitle[MAX_LOADSTRING];					// Текст строки заголовка
TCHAR szWindowClass[MAX_LOADSTRING];			// имя класса главного окна
static int winCount = 0;
HWND begin_hWnd;
HWND mass_hWnd[7];

// Отправить объявления функций, включенных в этот модуль кода:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int); //сохраняет обработку экземпляра и создает главное окно.
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM); /*вывызвется оконная ф-я
															LRESULT-Знаковый результат обработки сообщения.
		Функция WindowProc - определяемая программой функция, которая обрабатывает сообщения, отправленные в окно. */
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM); //Функция About будет вызываться системой для обработки сообщений, посылаемых окну диалога.

int APIENTRY _tWinMain (_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: разместите код здесь.
	MSG msg; //содержит информацию о сообщении из очереди сообщений потока.
	HACCEL hAccelTable; //Дескриптор таблицы ускорителей 

	// Инициализация глобальных строк
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING); /*загружает ресурс строки из исполняемого файла,
																копирует строку в буфер и добавляет в конец символ завершающего нуля.*/
	LoadString(hInstance, IDC_MY1013, szWindowClass, MAX_LOADSTRING); /*Дескриптор экземпляра модуля, исполняемый файл которого содержит в себе ресурс строки.
																Указывает целочисленный идентификатор строки, которая будет загружена.
																Указатель на буфер, который примет строку.
																Определяет размер буфера	*/
	MyRegisterClass(hInstance); //регистрация оконного класса 

	// Выполнить инициализацию приложения:
	if (!InitInstance (hInstance, nCmdShow)) //осуществляет инициализацию приложения и формирует дескриптор приложения hInstance
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY1013)); /*загружает заданную таблицу клавиш-ускорителей
	Дескриптор модуля, исполняемый файл которого содержит загружаемую таблицу клавиш-ускорителей.
	Указатель на символьную строку с нулем в конце, которая содержит имя загружаемой таблицы клавиш-ускорителей.*/

	/*простейший цикл обработки сообщения*/
	while (GetMessage(&msg, NULL, 0, 0))
		
	{	
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		{
			TranslateMessage(&msg); //переводит сообщения виртуальных клавиш в символьные сообщения
			DispatchMessage(&msg); //используется, чтобы доставить сообщение, извлеченное функцией GetMessage
		}
	}
	return (int) msg.wParam;
}

/* ФУНКЦИЯ: MyRegisterClass()
	НАЗНАЧЕНИЕ: регистрирует класс окна.
	КОММЕНТАРИИ:
    Эта функция и ее использование необходимы только в случае, если нужно, чтобы данный код
    был совместим с системами Win32, не имеющими функции RegisterClassEx'
    которая была добавлена в Windows 95. Вызов этой функции важен для того,
    чтобы приложение получило "качественные" мелкие значки и установило связь с ними.*/
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex; //содержит информацию о классе окна
	wcex.cbSize = sizeof(WNDCLASSEX); //Задает стиль окна.
	wcex.style			= CS_HREDRAW | CS_VREDRAW; /*CS_HREDRAW	Перерисовывает все окно, если перемещение или
												   регулировка размера изменяют ширину или высоту рабочей области.*/
	wcex.lpfnWndProc	= WndProc; //Определяет имя оконной процедуры.
	wcex.cbClsExtra		= 0;  //Дополнительные данные для класса.
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance; /*Заголовок приложения, работающего с данным окном.
										Иконка для окна приложения.*/
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY1013));/*загружает указанный ресурс значка из исполняемого файла, 
																  связанного с экземпляром приложения.
	Дескриптор экземпляра модуля, содержащий исполняемый файл, значок которого будет загружен.
	Указатель на строку с завершающим нулем, cодержащую имя ресурса значка, который будет загружен. 
	Макрос MAKEINTRESOURCE преобразует целочисленное значение в тип ресурса, совместимого с функциями управления ресурсом*/
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW); //Устанавливает тип курсора в окне приложения.
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);  //Задет кисть для закраски окна. HBR-Дескриптор кисти
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_MY1013); //Задает меню для окна приложения.
	wcex.lpszClassName	= szWindowClass; //Указатель на оконный класс.
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

/*ФУНКЦИЯ: InitInstance(HINSTANCE, int)
  НАЗНАЧЕНИЕ: сохраняет обработку экземпляра и создает главное окно.
  КОММЕНТАРИИ:
       В данной функции дескриптор экземпляра сохраняется в глобальной переменной, а также
       создается и выводится на экран главное окно программы.*/
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   //Дескриптор окна.

   hInst = hInstance; // Сохранить дескриптор экземпляра в глобальной переменной
   
   // создает перекрывающее, выскакивающее или дочернее окно. 
   HWND hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
   begin_hWnd = hWnd;
   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);//устанавливает состояние показа определяемого окна, дескриптор окна, состояние показа окна
   UpdateWindow(hWnd);//обновляет клиентскую область указанного окна,

   return TRUE;
}

/*ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
 НАЗНАЧЕНИЕ:  обрабатывает сообщения в главном окне.
 WM_COMMAND	- обработка меню приложения
 WM_PAINT	-Закрасить главное окно
 WM_DESTROY	 - ввести сообщение о выходе и вернуться.
*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;//содержит информации для приложения
	HDC hdc;//Дескриптор контекста устройства 
	
	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Разобрать выбор в меню:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);//создает модальное диалоговое окно из ресурса шаблона блока диалога.
			break;
			/* Дескриптор модуля, исполняемый файл которого содержит шаблон диалогового окна.
			Определяет шаблон диалогового окна
			Дескриптор окна, которое владеет диалоговым окном.
			Указатель на процедуру диалогового окна			*/
		case IDM_EXIT:
			if (IDOK == MessageBox(hWnd, _T("Хотите закрыть программу?"), _T("Закрыть"),
				MB_OKCANCEL | MB_ICONQUESTION | MB_DEFBUTTON2))
				SendMessage(hWnd, WM_DESTROY, NULL, NULL); 
			DestroyWindow(hWnd);// разрушает заданное окно, дескриптор для разрушения окна
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);//обеспечивает обработку по умолчанию любого сообщения окна, которые приложение не обрабатывае
		}
		break;
	
	case WM_LBUTTONDOWN:
		SetWindowText(hWnd, _T ("Главное окно"));
		break;

	case WM_PAINT://Уведомляет окно о том, что тpебуется пеpеpисовать всю или часть его области пользователя.
		hdc = BeginPaint(hWnd, &ps);
		// TODO: добавьте любой код отрисовки...
		EndPaint(hWnd, &ps);
		break;

	case WM_RBUTTONDOWN:
		{	 //for (winCount = 0;winCount < 3;winCount++) {
			 if (winCount >= 7)
		 {		 MessageBox(hWnd, L"Нельзя создать более 7 окон", L"", MB_OKCANCEL | MB_ICONQUESTION);
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
						 SetWindowText(child, _T("Дочернее окно"));
						 ShowWindow(child, SW_NORMAL);
			 //  }
	}
	break;
		
	case WM_CLOSE: //спрашивает о выходе из программы
		if (hWnd == begin_hWnd)
		{
		if (IDOK == MessageBox(hWnd, _T("Хотите закрыть программу?"), _T("Закрыть"), MB_OKCANCEL | MB_ICONQUESTION | MB_DEFBUTTON2))
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

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
/*Функция About будет вызываться системой для обработки сообщений, посылаемых окну диалога.
	HWND  Windows-описатель окна диалога;
	UINT  — код сообщения;
	WPARAM, LPARAM  — два параметра, сопровождающих сообщение.
	Целый знаковый тип для точности указателя.*/
{
	UNREFERENCED_PARAMETER(lParam); //Помогает избежать предупреждений компилятора о наличии параметров, на которые нет ссылок (неиспользуемых параметров)
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));/*уничтожает модальное диалоговое окно, 
			Описатель диалогового окна, Значение, возвращаемое приложению из функции, создающей диалоговое окно*/
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
