#pragma once


static class States
{
public:
	static bool GetPausedState();
	static void SetPausedState(bool bState);

private:
	static bool bPaused;
};

