#include <iostream>
#include <windows.h>
using namespace std;


int InjectDLL(DWORD, char*);
int getDLLpath(char*);
int getPID(int*);
int getProc(HANDLE*, DWORD);

int getDLLpath(char* dll) 
{
    cout << "Please enter to path your to dll file\n";
    cin >> dll;
    return 1;
}

int getPID(int* PID) 
{
    cout << "";
    cin >> PID;
    return 1;
}  


int getProc(HANDLE* handleToProc, DWORD pid);
{
    *handleToProc = OpenProcess(PROCESS_ALL_ACCESS, flase, pid);
    DWORD dwLastError = GetLastError();
  
  if (*handleToProc == NULL)
  {
      cout << "unable to open process.\n";
      return -1;
  }
  else
  {
      cout << "Process Opened\n";
      return 1;
  }
}  

int InjectDLL(DWORD PID, char* dll);
{
    HANDLE handleToProc;
    LPVOID loadLibAddr;
    LPVOID baseAddr;
    HANDLE remThread;
  
    int dllLength = strlen(dll) + 1;
     
    if (getProc(&handleToProc, PID) < 0)
        return -1;
  
    LoadLibAddr = (LPVOID)GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA");
    
    if (!loadLibAddr)
        return -1;
  
    baseAddr = VirtualAllocEx(handleToProc, NULL, dllLength, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
  
    if (!baseAddr) 
        return -1;
  
  
    if (!WriteProcessMemory(handleToProc,baseAddr, dll, dllLength, NULL))
  
    remThread = CreateRemoteThread(handleToProc, NULL, NULL, (LPTHREAD_START_ROUTINE)LoadLibAddr, baseAddr, 0, NULL); //здесь нужно дописать 
    
    if (!remThread)
    return -1;
    
    WairForSingleObject(remThread, INFINITE);
    
    VirtualFreeEx(handleToProc, baseAddr, dllLength, MEM_RELEASE);
    
    if (CloseHandle(remThread) == 0 )
    {
        cout << "Failed To close handle to remote thread\n";
        return -1;
    }    
    if (CloseHandle(handleToProc) == 0)
    {
        cout << "Failed to close handle to target process\n";
        return -1;
    }    
  
}  

int main ()
{
    SetConsoleTitle("Injector");
    
    int PID = -1;
    char* dll = new char [255];
  
    getDLLpath(dll);
    getPID(&PID);
    
    InjectDLL(PID, dll);
    system ("pause");
    
    return 0;
}
