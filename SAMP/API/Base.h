#ifndef _SAMP_BASE_H_
#define _SAMP_BASE_H_

namespace SAMP
{
	class Base
	{
		static Base* self;

		void* pSAMP{ nullptr };
		void** ppPools{ nullptr };
		int ofHostName;
		int ofAddress;
		int ofPort;

		class Pools* pPools_{ nullptr };

		Base();
		~Base();
	public:
		static Base* CreateInstance();
		static void DeleteInstance();

		static bool isSAMPInitilize();

		const char* GetHostname();
		const char* GetServerIP();
		short GetServerPort();
		char* GetServer();

		class Pools* Pools();
	}; // class Base
}; // namespace SAMP

#endif // !_SAMP_BASE_H_