#pragma region project include
#include "Time.h"
#pragma endregion

#pragma region variable
int CTime::s_fps = 0;
float CTime::s_deltaSeconds = 0.001f;
#pragma endregion

#pragma region public function
// update time
void CTime::Update()
{
	// get time now
	long now = clock();

	// calculate difference from last update until now
	long diff = now - m_lastUpdate;

	// set delta seconds to difference
	s_deltaSeconds = diff / (float)CLOCKS_PER_SEC;

	// set last update to now
	m_lastUpdate = now;

	// increase frames since last time stamp
	m_frameSinceLastTimeStamp++;

	// add difference to time since last time stamp
	m_timeSinceLastTimeStamp += diff;

	// if time since last time stamp is higher than one second
	if (m_timeSinceLastTimeStamp > CLOCKS_PER_SEC)
	{
		// set fps
		s_fps = m_frameSinceLastTimeStamp;

		// reset frames since last time stamp
		m_frameSinceLastTimeStamp = 0;

		// decrease time since last time stamp by one second
		m_timeSinceLastTimeStamp -= CLOCKS_PER_SEC;
	}
}
#pragma endregion