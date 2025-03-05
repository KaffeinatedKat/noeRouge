#include <iostream>
#include <chrono>

const int UPDATE_RATE = 60;

double get_dTime( )
{
	static auto pTime = std::chrono::steady_clock::now( );
	auto cTime = std::chrono::steady_clock::now( );

	double dTime = std::chrono::duration<double>( cTime - pTime ).count( );
	pTime = cTime;

	return dTime;
}

int main( )
{
	double update_timer = 0.0;
	bool gogogo = true;
	while ( gogogo )
	{
		double dTime = get_dTime( );
		update_timer += dTime;
		if ( update_timer % UPDATE_RATE > 1 )
		{
			//continue
		}
	}
	return 0;
}