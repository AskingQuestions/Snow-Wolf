
#ifdef SW_Windows
bool Thread::start() {
	DWORD tid;
	SW_threading_struct sts;
	sts.call = &thread;
	threadHandle = CreateThread(0, 0, SW_threading_thread, sts, 0, &tid);
}

void Thread::kill() {
	CloseHandle(threading);
}
#endif