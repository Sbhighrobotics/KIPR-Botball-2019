#include <kipr/botball.h>

/* Constants - Edit as needed */
int distanceFromStart = -200;  // first travel distance before turning. edit as needed. needs to be negative since roomba is moving negatively.
int distanceToFireStation = -750;
int distanceToRunAway = -500;
int driveSpeed = -500;

int angleToFireStation = 90; // momentum should get it to approx 90 or other mark you're trying to get to
int angle2 = 50;
int turningSpeed = 125;

/* Turning Stuff */
typedef int direction;
const direction clockwise = -1, counterclockwise = 1;
const float angleCorrectionFactorClockwise = 360.0 / 345.5;
const float angleCorrectionFactorCounterclockwise = 360.0 / 351.5;

/* Function Prototypes */
void turn(int angle, int speed, direction thisDirection);
void drive(int distance, int speed);
void punchFiremen();

int main()
{
//	wait_for_light(0);
    create_connect();
    printf("MOVING!!!\n");

	drive(distanceFromStart, driveSpeed);
    turn(angleToFireStation, turningSpeed, counterclockwise);
    
    drive(distanceToFireStation, driveSpeed);
    punchFiremen();
    
	drive(distanceToRunAway, driveSpeed);
    
    shut_down_in(120);
    return 0;
}

void drive(int distance, int speed) {
 
    set_create_distance(0);
    while(get_create_distance() > distance) 
    {
        create_drive_direct(speed, speed);
    }
    
    create_stop();
}

void turn(int targetAngle, int speed, direction thisDirection) {
    
    if (thisDirection == clockwise) targetAngle *= angleCorrectionFactorClockwise;
    else targetAngle *= angleCorrectionFactorCounterclockwise;

    set_create_total_angle(0);
    while(get_create_total_angle() * thisDirection < targetAngle) 
    {
        int thisTurningSpeed = thisDirection * speed;
        create_drive_direct(-1 * thisTurningSpeed, thisTurningSpeed);
    }
    
    create_stop();
}

void punchFiremen()
{
    set_create_distance(0);
    set_create_total_angle(0);

    while(get_create_total_angle()<=1705)
    {

        create_drive_direct(-300,300); //forward turn
        msleep(50);


    }
    create_stop();
}



