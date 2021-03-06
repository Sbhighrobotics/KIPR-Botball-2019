#include <kipr/botball.h>
int speed = 2000;
int leftMotor = 1;
int rightMotor = 0;
int highGrey= 2650;
int lowBlack = 3650;
int highWhite =950;
int lowBlue = 1150;



void follow();
void goTillBlack();
void followCamera();
void goForward(int time);
void reverseFollowCamera();
void followBlue();
void toBlueR();
void toBlueL();
void toDRZ();
void goTillWhite();
void wag();

int main()
{
    
    wait_for_light(1);
    msleep(25000);
    shut_down_in(100);
    camera_open();
    enable_servos();
    set_servo_position(0,1000);
    msleep(100);
    mav(leftMotor, 0);
    mav(rightMotor, 0);
    mav(leftMotor,speed);
    msleep(350);
    goForward(1800);
    goTillBlack();
    mav(rightMotor,speed);
    mav(leftMotor,0);
    msleep(1400);
    follow();
    reverseFollowCamera();
    toDRZ();
    wag();
    return 0;
}

void wag()
{
    printf("MEOW");
    enable_servos();
    set_servo_position(0,1600);
    msleep(500);
    set_servo_position(0,400);
    msleep(500);
    set_servo_position(0,1600);
    msleep(500);
    set_servo_position(0,400);
    msleep(500);
     set_servo_position(0,1600);
   msleep(500);
    set_servo_position(0,400);
    msleep(500);
     set_servo_position(0,1600);
    msleep(500);
    set_servo_position(0,400);
    msleep(500);
}


void goForward(int t)
{
    mav(leftMotor, speed);
    mav(rightMotor, (speed));
    msleep(t);
}


void goTillBlack()
{
    while(analog(0)<lowBlack)
    {
    }
    mav(rightMotor,0);
    mav(leftMotor,0);
}
void goTillWhite()
{
    printf("Function engaged\n");
    int i=1;
    int limit=0;
    while(i<100)
    {
        if(analog(0)<highWhite)
        {
            limit++;
            printf("%d", limit);
        }
        if(limit>10)
        {
            break;
        }

    }
    mav(rightMotor,0);
    mav(leftMotor,0);
    printf("Function disengaged\n");
}


void follow()
{
    //double startTime = seconds();
    //printf("%f\n", startTime);

    int count=0;
    while(count < 60)// && r<14)
    {
        printf("%d\n",count);
        if(analog(0)<=highGrey)
        {
            mav(rightMotor,speed/2);
            mav(leftMotor,speed);
            msleep(2);

            //printf("on grey");
        }else if(analog(0)>=lowBlack)
        {
            mav(leftMotor,speed/2);
            mav(rightMotor,speed);
            msleep(2);

            //printf("on black");
        }else
        {
            mav(rightMotor,speed);
            mav(leftMotor,speed);
            msleep(100);
            //mav(rightMotor,0);
            //mav(leftMotor,0);
        }

        camera_update();
        count++;
    }
    mav(rightMotor,0);
    mav(leftMotor,0);
    // printf("%f\n", seconds() - startTime);
}


void followCamera()
{

    int width = get_object_bbox_width(0,0);
    int x=0; 
    while(width<25)
    {
        camera_update();
        if(get_object_count(0) != 0)
        {
            width = get_object_bbox_width(0,0);
            x= get_object_center_x(0,0);
            printf("%d\n",x);
            if(x<35)
            {
                mav(rightMotor, speed);
                mav(leftMotor, speed/2);
                msleep(50);
            }else if(x>=35 )
            {
                mav(leftMotor, speed);
                mav(rightMotor, speed/2);
                msleep(50);
            }
        }
    }
}

void reverseFollowCamera()
{
    int a = 0;
    while(a==0)
    {
        printf("I might be working");
        camera_update();
        if(get_object_count(0) != 0 && get_object_count(1) != 0)
        {
            printf("I see it");
            int x = (get_object_center_x(0,0)+get_object_center_x(1,0))/2;
            printf("%d\n",x);
            if(x > 140 && x <= 160)
            {
                printf("I'm going forward differently");
                mav(leftMotor, speed);
                mav(rightMotor, speed);
                goTillWhite();
                goForward(360);
                toBlueL();
                break;
            }else
            {
                printf("I'm turning");
                mav(0,1000);
                mav(1,1000);
                msleep(500);
                mav(0,0);
                mav(1, 1000);
                msleep(480);
                goForward(220);
                goTillBlack();
                goForward(350);
                toBlueR();
                break;
            }
        }else
        {
            printf("Why did I do this");
            mav(leftMotor, speed);
            mav(rightMotor, speed);
            goTillWhite();
            goForward(360);
            toBlueL();
            break;
        }
    }
}    

void followBlue(int howLong)
{
    printf("Hi Joy\n");
    int count=0;
    while(count<howLong)
    {
        if(analog(0)>=lowBlue)
        {
            mav(rightMotor,speed/2);
            mav(leftMotor,speed);
            msleep(2);
            //printf("blue\n");
        }else if(analog(0)<=highWhite)
        {
            mav(leftMotor,speed/2);
            mav(rightMotor,speed);
            msleep(2);
            //printf("white\n");
        }else
        {
            mav(rightMotor,speed);
            mav(leftMotor,speed);
            msleep(2);
            //printf("else\n");
        }

        printf("Update %d \n", count);
        count++;
    }
    mav(0,0);
    mav(1,0);
}

void toBlueR()
{
    mav(0,-2000);
    mav(1,-2000);
    msleep(1900);
    mav(leftMotor,2000);
    mav(rightMotor,0);
    msleep(1350);
    int count=0;
    while(analog(0)<lowBlue && count<500)
    {
        mav(leftMotor, 2000);
        mav(rightMotor, 2000);
        msleep(50);
        count++;
    }
    followBlue(350);
}

void toBlueL()
{
    mav(rightMotor,-2000);
    mav(leftMotor,-2000);
    msleep(1100);
    mav(leftMotor,2000);
    mav(rightMotor,0);
    msleep(1550);
    int count=0;
    while(analog(0)<lowBlue && count<500)
    {
        mav(leftMotor, 2000);
        mav(rightMotor, 2000);
        msleep(50);
        count++;
    }
    followBlue(500);
}

void toDRZ()
{
    mav(leftMotor, speed);
    mav(rightMotor, 0);
    msleep(1050);
    mav(leftMotor, speed);
    mav(rightMotor, speed);
    goTillBlack();
    mav(leftMotor, speed);
    mav(rightMotor, speed);
    msleep(400);
    goTillBlack();
    mav(leftMotor, speed);
    mav(rightMotor, speed);
    msleep(200);
    mav(leftMotor, 0);
    mav(rightMotor, 0);
}







