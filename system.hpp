#ifndef sw_systemdef
#define sw_systemdef

#ifdef _WIN32
#define SW_Windows
namespace System {
	struct {
		string name = "Windows";
		string version = "";
		int minor = -1;
		int major = -1;
		bool isServer = false;
	} os;
	
	struct {
		string name = "";
	} user;
	
	struct {
		string currentDirectory = "";
		string currentApplication = "";
	} application;
	
	int processors = -1;
	int init() {
		SYSTEM_INFO ws;
		GetSystemInfo(&ws);
		//Processors
		processors = ws.dwNumberOfProcessors;
		
		//Os
		OSVERSIONINFOEX osInfo;
		ZeroMemory(&osInfo, sizeof(OSVERSIONINFOEX));
		osInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

		GetVersionEx((LPOSVERSIONINFO) &osInfo);

		os.minor = osInfo.dwMinorVersion;
		os.major = osInfo.dwMajorVersion;
		 
		if (osInfo.dwMajorVersion == 10 && osInfo.dwMinorVersion == 0 && osInfo.wProductType == VER_NT_WORKSTATION) { //Windows 10
			os.version = "10";
		}else if (osInfo.dwMajorVersion == 6 && osInfo.dwMinorVersion == 3 && osInfo.wProductType == VER_NT_WORKSTATION){ //Windows 8.1
			os.version = "8.1";
		}else if (osInfo.dwMajorVersion == 6 && osInfo.dwMinorVersion == 3 && osInfo.wProductType == VER_NT_SERVER){ //Windows Server 2012 R2
			os.version = "Server 2012 R2";
		}else if (osInfo.dwMajorVersion == 6 && osInfo.dwMinorVersion == 2 && osInfo.wProductType == VER_NT_WORKSTATION){ //Windows 8
			os.version = "8";
		}else if (osInfo.dwMajorVersion == 6 && osInfo.dwMinorVersion == 2 && osInfo.wProductType == VER_NT_SERVER){ //Windows Server 2012
			os.version = "Server 2012";
		}else if (osInfo.dwMajorVersion == 6 && osInfo.dwMinorVersion == 1 && osInfo.wProductType == VER_NT_WORKSTATION){ //Windows 7
			os.version = "7";
		}else if (osInfo.dwMajorVersion == 6 && osInfo.dwMinorVersion == 1 && osInfo.wProductType == VER_NT_SERVER){ //Windows Server 2008 R2
			os.version = "Server 2008 R2";
		}else if (osInfo.dwMajorVersion == 6 && osInfo.dwMinorVersion == 0 && osInfo.wProductType == VER_NT_WORKSTATION){ //Windows Vista
			os.version = "Vista";
		}else if (osInfo.dwMajorVersion == 6 && osInfo.dwMinorVersion == 0 && osInfo.wProductType == VER_NT_SERVER){ //Windows Server 2008
			os.version = "Server 2008";
		}/*else if (osInfo.dwMajorVersion == 5 && osInfo.dwMinorVersion == 2 && GetSystemMetrics(SM_SERVERR2) != 0){ //Windows Server 2003 R2
			os.version = "Server 2003";
		}else if (osInfo.dwMajorVersion == 5 && osInfo.dwMinorVersion == 2 && osInfo.wSuiteMask && VER_SUITE_WH_SERVER){ //Windows Home Server
			os.version = "Home Server";
		}else if (osInfo.dwMajorVersion == 5 && osInfo.dwMinorVersion == 2 && (OSVERSIONINFOEX.wProductType == VER_NT_WORKSTATION) && (SYSTEM_INFO.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_AMD64)){ //Windows XP Professional x64 Edition
			os.version = "XP Professional x64 Edition";
		}*/else if (osInfo.dwMajorVersion == 5 && osInfo.dwMinorVersion == 1){ //Windows XP
			os.version = "XP";
		}else if (osInfo.dwMajorVersion == 5 && osInfo.dwMinorVersion == 0){ //Windows 2000
			os.version = "2000";
		}
		
		//Username
		char un[UNLEN+1];
		DWORD ul = UNLEN+1;
		GetUserName(un, &ul);
		user.name = string(un);
		
		//Application Fix to handle long path names.
		char buffer[MAX_PATH];
		GetModuleFileName( NULL, buffer, MAX_PATH );
		string exPath = string(buffer);
		application.currentApplication = exPath;
		
		string::size_type pos = exPath.find_last_of("\\/");
		application.currentDirectory = exPath.substr(0, pos);
	}
};
#endif
#endif