// by OlegTim. Add *.cpp to *.dev and compile.
// Tested on Win7X64,  1024*768, fullscreen and windowed
//devcpp 4.9.9.2  tools -compiler options - settings- linker - create console - (try n)
//  tools - compiler options - compiler - add this to linker cmd -lgdi32 

//Draws filled triangles polygons 3 points x y and rgb and reads keyboard input
#include <windows.h>
#include <windowsx.h>
#include <CommCtrl.h>
#include <string>
using namespace std;

int width = 1024;
int height = 768; 
string str_show("");
HINSTANCE hInstance;
HWND hwnd;
int first = 0;

void set_width(int a){
width=a;
	}

int get_width(){
return 	width;
	}

void set_height(int a){
height = a;
	}

int get_height(){
return 	height;
	}

void set_str(string s){
str_show = s;	 
	   }

void redraw(){
RedrawWindow(hwnd,NULL,NULL,RDW_INVALIDATE );
SetFocus(hwnd);	 
	 }
 
 
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM LParam) {
  
    switch (msg) {
		   		   
case WM_KEYDOWN:
	 switch(wParam)	
	 {	  				 
case VK_F1: string g_i(); MessageBox(NULL,g_i().c_str(),"",MB_OK|MB_ICONINFORMATION); break;
//roll actually is rotation OY; but as we look down of OZ it's better as yaw
case VK_UP: void down(); down();  break;
case VK_DOWN: void up(); up(); break;
case VK_LEFT: void roll_left(); roll_left(); break;
case VK_RIGHT: void roll_right(); roll_right(); break;
case 0XBC: void right(); right(); break;
case 0XBE: void left(); left(); break;
case 0x57: void forward(); forward(); break; 
case 0x53: void back(); back(); break; 
case 0x41: void stepleft(); stepleft(); break; 
case 0x44: void stepright(); stepright(); break; 
case 0x5A: void stepup(); stepup(); break; 
case 0x58: void stepdown(); stepdown(); break; 
					   }    
break;	   
		   

    case WM_PAINT:
       {
        PAINTSTRUCT ps;
HDC hdc = BeginPaint(hWnd, &ps);       
HDC memDC = CreateCompatibleDC( hdc );
RECT rcClientRect;
GetClientRect( hwnd, &rcClientRect );
HBITMAP bmp = CreateCompatibleBitmap( hdc, 
            rcClientRect.right - rcClientRect.left, 
            rcClientRect.bottom - rcClientRect.top );
			 HBITMAP oldBmp = (HBITMAP)SelectObject( memDC, bmp );		               

int r,g,b,x1,x2,x3,y1,y2,y3,n;
int get_drawpol_size();
n= get_drawpol_size();
int get_drawpol(int a, int b);

//start drawing
for (int i=0; i<n;i++){
x1=get_drawpol(i, 0);
y1=get_drawpol(i, 1);
x2=get_drawpol(i, 2);
y2=get_drawpol(i, 3);
x3=get_drawpol(i, 4);
y3=get_drawpol(i, 5);
r=(int)get_drawpol(i, 6);
g=(int)get_drawpol(i, 7);
b=(int)get_drawpol(i, 8);
	
HPEN hPen=CreatePen(PS_NULL, 3, RGB(0, 0, 0));
SelectObject(memDC, hPen);
HBRUSH hBrush = CreateSolidBrush(RGB(r, g, b));
HBRUSH hOldBrush = SelectBrush(memDC, hBrush);
POINT vertices[] = { {x1, y1},{x2, y2}, {x3, y3} };
Polygon(memDC, vertices, sizeof(vertices) / sizeof(vertices[0]));
DeleteObject(hBrush);
DeleteObject(hOldBrush);
}
TextOut(memDC,0,0, str_show.c_str(), strlen(str_show.c_str()));  
//end drawing

BitBlt( hdc, 0, 0, rcClientRect.right - rcClientRect.left, 
            rcClientRect.bottom - rcClientRect.top, memDC, 0, 0, SRCCOPY );        
SelectObject( memDC, oldBmp );
        DeleteObject( bmp ); 
        DeleteDC( memDC ); 		   
ReleaseDC(hwnd, hdc);  
        EndPaint(hWnd, &ps);
        }
        break;
 
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }

    return DefWindowProc(hWnd, msg, wParam, LParam);
}
 
int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE h2, LPSTR cmd, int cmShow) { 	
if (first==0){first++; void init(); init();}
    WNDCLASS wc = {0};
    wc.lpszClassName = TEXT("3dpoly");
    wc.lpfnWndProc = WndProc;
    wc.hbrBackground = CreateSolidBrush(RGB(212, 208, 200));
    wc.hCursor=LoadCursor(NULL,IDC_ARROW); 
    RegisterClass(&wc); 

RECT rect; 
if(GetWindowRect(hwnd, &rect))
{
   width = rect.right - rect.left;
   height = rect.bottom - rect.top;
}	        
 
 hwnd = CreateWindow(wc.lpszClassName,"Triangle_poly_by_OlegTim",
 WS_OVERLAPPEDWINDOW | WS_VISIBLE, 0,0,width,height,0,0,hInstance,0);
 
SetWindowPos(hwnd, HWND_TOP, 0, 0, GetSystemMetrics(SM_CXSCREEN), //fullscreen w tab
GetSystemMetrics(SM_CYSCREEN), SWP_FRAMECHANGED);

WINDOWPLACEMENT wpc; //fullscreen without tab and borders
GetWindowPlacement(hwnd,&wpc);
                SetWindowLong(hwnd,GWL_STYLE,WS_POPUP);
                SetWindowLong(hwnd,GWL_EXSTYLE,WS_EX_TOPMOST);
                ShowWindow(hwnd,SW_SHOWMAXIMIZED); 
  				        
  MSG msg;
    while (GetMessage(&msg, NULL , 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
           if(msg.message==WM_KEYDOWN)
             {
                   if(msg.wParam==VK_ESCAPE)
                   {
                        PostQuitMessage(0);
                   }
				   }
        
    }
    return 0;
}
