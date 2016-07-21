#ifndef threading_def
#define threading_def

#ifdef SW_Windows
typedef struct {
	function<bool()> call;
} SW_threading_struct;

/**
*	\brief This class is used to create threads.
*	The class is a high level object that interacts with the os threading api.
*/
class Thread {
public:
	Thread(function<bool()> threadFunction) {
		thread = threadFunction;
	}
	bool start();
	
	void kill();
private:
	
	HANDLE threadHandle;
	
	function<bool()> thread;
};

DWORD WINAPI SW_threading_thread(LPVOID lpParam) {
	lpParam.call();
	return 0;
}
#endif

#include "threading.cpp"

#endif