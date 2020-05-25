#include"windows.h"
#include"windowsx.h"
#include"stdio.h"
BITMAPINFO bmi={0};

bool CheckForJumps(HDC hdc, HDC hmemdc,HBITMAP hbmp)
{
     BitBlt(hmemdc, 0, 0, 30, 40, hdc, 488, 195, SRCCOPY);
     int arr[30][35];
     int nret=GetDIBits(hmemdc, hbmp, 0, 35, &arr, &bmi, DIB_RGB_COLORS);
     if(nret==0)exit(-1);
     
     for(int i=0; i<30;i++)
     for(int j=0; j<35;j++)
     {
             if(arr[i][j]==0xff535353||arr[i][j]==0xffacacac)return true;
     }
     return false;
}

int main()
{
             HDC hdc=GetDC(0);
             HDC hmemdc=CreateCompatibleDC(hdc);
             HBITMAP hbmp=CreateCompatibleBitmap(hdc, 30, 35);
             SelectObject(hmemdc, hbmp);
           	 bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
             GetDIBits(hmemdc, hbmp, 0, 0, 0, &bmi, DIB_RGB_COLORS);
             while(1)
             {
                     if(CheckForJumps(hdc, hmemdc, hbmp))
                     {
                            PostMessage((HWND)0xffff,WM_KEYDOWN,VK_SPACE,0x390001);
                            PostMessage((HWND)0xffff,WM_KEYUP,VK_SPACE,0xc0390001);
                     }
             }
}
