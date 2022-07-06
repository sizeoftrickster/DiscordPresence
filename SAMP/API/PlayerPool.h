#ifndef _SAMP_PLAYER_POOL_H_
#define _SAMP_PLAYER_POOL_H_

#include <string>

namespace SAMP
{
	class PlayerPool
	{
		void* pPlayerPool;

		void* pLocalPlayerNickname{ nullptr };
		short* pLocalPlayerId{ nullptr };
	public:
		PlayerPool( void* pPlayerPool );
		~PlayerPool() {  };

		std::string GetLocalPlayerNickname();
		short GetLocalPlayerId();
	};
}; // namespace SAMP

#endif // !_SAMP_PLAYER_POOL_H_