#include "gamepark.h"

/*
The start of the main function starts like in most other example. We ask the
user for the desired renderer and start it up. This time with the advanced
parameter handling.
*/
int main()
{
    GamePark gamePark;
    return gamePark.run();
}

/*
Now you know how to use terrain in Irrlicht.
**/
