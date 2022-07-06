#ifndef _SAMP_LIBRARY_H_
#define _SAMP_LIBRARY_H_

namespace SAMP
{
	enum class sampVersion : int
	{
		unknown = 0,
		notLoaded = -1,
		R1 = 1,
		R2 = 2,
		R3 = 3,
		R4 = 4,
		DL = 5
	}; // enum class sampVersion
	unsigned long GetSAMPHandle();
	enum sampVersion GetSAMPVersion();
}; // namespace SAMP

#endif // !_SAMP_LIBRARY_H_