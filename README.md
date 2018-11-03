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
