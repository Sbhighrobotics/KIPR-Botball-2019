#include <kipr/botball.h>

void DeadReckoning();
void firemanHit();
int fTravel = -200; //Other side is -125 // first travel distance before turning. edit as needed. needs to be negative since roomba is moving negatively.
int turn1 = 75;
int turn2 = 50;
int sTravel = -530; //-750 is original code
int tTravel = -100;

int main()
{
//	wait_for_light(0);
    create_connect();
    create_stop();
    set_create_total_angle(0);
    set_create_distance(0);
    printf("MOVING!!!\n");

    int x = 0;


     set_create_total_angle(0);
    x = 0;
    while(x <= turn1) // momentum should get it to approx 90 or other mark you're trying to get to
    {
        create_drive_direct(-125,125);
        x = get_create_total_angle();


    }
    create_stop();
    printf("Turned  %d \n",x);
    
    
    while(x >= fTravel)
    {
        create_drive_direct(-500,-500);
        x = get_create_distance();
        printf("%d \n",x);
        msleep(1);
    }

   


    set_create_distance(0);
    x = 0;
    while(x >= sTravel)
    {
        create_drive_direct(-500,-500);
        x = get_create_distance();

        msleep(1);
        printf("Goingpt2 %d \n",x);
    }
   

    create_stop();
    printf("Turned  %d \n",x);

    firemanHit();

    set_create_distance(0);
    x = 0;
    while(x >= tTravel)
    {
        create_drive_direct(-500,-500);
        x = get_create_distance();

        msleep(1);
        printf("Goingpt2 %d \n",x);
    }
    
    return 0;
}



void firemanHit()
{
    set_create_distance(0);
    set_create_total_angle(0);

    while(get_create_total_angle()<=2035)
    {

        create_drive_direct(-300,300); //forward turn
        msleep(50);


    }
    create_stop();
    shut_down_in(120);
}

void DeadReckoning()
{

    create_drive_direct(-400,0);
    msleep(2000);
    create_drive_direct(400,0);
    msleep(600);
    create_drive_direct(-400,0);
    msleep(600);
    create_drive_direct(400,0);
    msleep(600);
    create_drive_direct(-400,0);
    msleep(600);
    create_drive_direct(400,0);
    msleep(600);
    create_drive_direct(-400,0);
    msleep(600);
    create_drive_direct(400,0);
    msleep(600);
    create_drive_direct(-400,0);
    msleep(600);
    create_drive_direct(400,0);
    msleep(600);
    create_drive_direct(-400,0);
    msleep(600);
    create_drive_direct(400,0);
    msleep(600);
    create_drive_direct(-400,0);
    msleep(600);
    create_drive_direct(400,0);
    msleep(600);
    create_drive_direct(-400,0);
    msleep(600);
}

