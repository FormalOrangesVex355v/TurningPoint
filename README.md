# TurningPoint
Code for the Turning Point season

# VEX RobotC
Download available here:

    http://www.robotc.net/release/vexrobotics/msi/

# Git client
Download the Windows Git client here:

    https://git-scm.com/download/win

The first time you start working on a project, make a directory for it:

     cd /c
     mkdir MyAwesomeProject
     cd MyAwesomeProject
     git clone https://github.com/FormalOrangesVex355v/TurningPoint.git
     cd TurningPoint

This will get the most recent version from GitHub. You are almost ready to start working on it.

Next, create a local branch:

     git checkout -b MyAwesomeFeature

This creates a local branch for your work. If someone else is working on the code and pushing commits to GitHub, you should periodically update your local branch:

     git fetch origin
     git merge origin/master
     
If you are not happy with your local code and want to abandon the work in one file, you can do:

    git checkout filename

You could also abandon all by doing:

    git checkout .

As you are working, you can checkpoint local work:

    git status

This will show all the differences between local work and what is pushed to GitHub:

    git diff

This will show you any uncommitted local work

    git add filename

Will add a single file named filename

    git add .
    
Will add all local changes

    git commit
    
Will let you commit changes. This will put you in an editor called vim. You'll need to press "i" to start typing your message. When complete, press the "ESC" key and then ":wq".

You may now be ready to share your work. You should ONLY push work to GitHub that compiles and works. If you push incomplete code and someone else pulls it, they will have to work with your incomplete code. DO NOT PUSH INCOMPLETE CODE!!!!!!

To push code:

    git push origin master

# First project
Program that allows the driver to control the Mecanum Drive Train, based on:

    http://www.robotc.net/blog/2011/11/22/vex-mecanum-drive-using-robotc/

# Second Project
Based on: 

    https://renegaderobotics.org/our-favorite-lcd-menu-code/

As well as: 

    https://www.vexforum.com/index.php/10222-how-to-program-lcd-display-robotc/6

# RobotC Examples

Sensors:

     http://www.robotc.net/wikiarchive/VEX2_Sensors_Overview
     
Potentiometer with PID:

     https://www.vexforum.com/index.php/17571-potentiometer-programming-in-robotc/0
     
RobotC Fundementals:

     http://www.robotc.net/tutor/Cortex/cortex.php?platform=Cortex&unit=robotcfundamentals&lesson=2

Improved Mecanum Drive:

     https://ftcforum.usfirst.org/forum/ftc-technology/android-studio/60054-mecanum-wheels-programming

# Notes from Graham Henderson on 11/4/2018

1. Using the data log to record and graph data
```C
      datalogDataGroupStart();

      datalogAddValue( 0, (int16_t)output );
      datalogAddValue( 1, (int32_t)thePid->target );
      datalogAddValue( 2, (int32_t)position );
      datalogAddValue( 3, (int32_t)(error *thePid->kp));
      datalogAddValue( 4, (int32_t)(thePid->integral * thePid->ki * 100));
      datalogAddValue( 5, (int32_t)(thePid->kd * ( error - thePid->prevError) * 10));

      datalogDataGroupEnd();
```

2.  Typical writing to the message log

```C
writeDebugStream( "\nx    = %3d y    = %3d\n", x , y );
```

3. Stuff from the board - using #define to characterize the drive train

```C
#define DRV_CNT_PER_REV_STD       (627.2)
#define DRV_RPM_STD                   (100.0)
#define DRV_CNT_PER_REV_HS       (392.0)
#define DRV_RPM_HS                    (160.0)

                                      // using high speed gearing
#define DRV_CNT_PER_REV       DRV_CNT_PER_REV_HS
#define DRV_RPM                       DRV_RPM_HS
#define WHEEL_DIAMETER_IN             (4.2) // modify to dial in the distance

#define WHEEL_CIRCUMFRENCE ( WHEEL_DIAMETER_IN * PI)
#define COUNTS_PER_INCH               ( DRV_CNT_PER_REV / WHEEL_CIRCUMFRENCE )
#define INCHES_TO_COUNTS(_x_)       ( COUNTS_PER_INCH * _x_)
```

# Blog Post on Datalog from Renegade Robotics

     https://renegaderobotics.org/robotc-datalog/
