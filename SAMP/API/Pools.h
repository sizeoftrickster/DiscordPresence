#ifndef _SAMP_POOLS_H_
#define _SAMP_POOLS_H_

namespace SAMP
{
	class Pools
	{
		void* pPools;
		void** ppPlayer;
		class PlayerPool* pPlayers_{ nullptr };
	public:
		Pools( void* pPools_ );
		~Pools();

		class PlayerPool* PlayerPool();
	}; // class Pools
}; // namespace SAMP

#endif // !_SAMP_POOLS_H_