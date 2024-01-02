#include <Windows.h>
namespace state {

	enum ConnectionState
	{
		DISCONNECTED = 0,
		CONNECTING = 1,
		CONNECTED = 2
	};

	struct _GlobalState
	{
		ConnectionState connectionState;
	};

	struct _LocalState
	{
		struct
		{
			LPCVOID OnRender;
			LPCVOID OnGameUpdate;
			LPCVOID OnSpecialUpdate;
			LPCVOID OnExecuteCommand;
			LPCVOID OnConsoleOutput;
			LPCVOID OnWindowMessage;
		} callbacks;

		bool initialized = false;
		bool needReload = false;
		bool needReloadDll = false;
		bool useSharedMemory;
		isaac::IsaacImage* isaac;
		lua::Lua lua;
		uint32_t MTRandomLockedValue = 0;
		HANDLE hProcess;
		HMODULE hOpenGL;
	};

	inline state::_GlobalState* global;
	inline state::_LocalState local;
	inline char charsBuffer[3];
}
