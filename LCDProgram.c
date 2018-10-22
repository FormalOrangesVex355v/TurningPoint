// These are the different choices we have
typedef enum {
    kLcdDispStart = 0,

    kLcdAuto_1    = 0,
    kLcdAuto_2,
    kLcdAuto_3,
    kLcdAuto_4,

    kLcdDispNumber
    } kLcdDispType;

// globals for tracking choices
short           autoMode = (-1);

// Display LCD choice
void lcdMenuDisplay(kLcdDispType current)
{
    //Switch case that allows the user to choose from 4 different options
    switch(current){
        case kLcdAuto_1:
            //Display first choice
            displayLCDCenteredString(0, "Red Left");
            displayLCDCenteredString(1, "<     Enter    >");
            break;
        case kLcdAuto_2:
            //Display second choice
            displayLCDCenteredString(0, "Red Right");
            displayLCDCenteredString(1, "<     Enter    >");
            break;
        case kLcdAuto_3:
            //Display third choice
            displayLCDCenteredString(0, "Blue Left");
            displayLCDCenteredString(1, "<     Enter    >");
            break;
        case kLcdAuto_4:
            //Display fourth choice
            displayLCDCenteredString(0, "Blue Right");
            displayLCDCenteredString(1, "<     Enter    >");
            break;

        default:
            break;
        }
}

// Pre auton code - allow auton choice until enabled or selection is made
void pre_auton()
{
    int     i;
    int     autoTime = 1000;
    TControllerButtons    Buttons;

    // current choice
    kLcdDispType    mode = kLcdAuto_1;

    //Clear LCD
    clearLCDLine(0);
    clearLCDLine(1);
    bLCDBacklight = true;

    // Initial display
    lcdMenuDisplay(mode);

    //Loop while disabled
    while( bIfiRobotDisabled )
        {
        // Select display Item
        Buttons = nLCDButtons;

        // if right or left pressed change display
        if( (Buttons == kButtonLeft) || (Buttons == kButtonRight) )
            {
            // check for button press
            if( Buttons == kButtonRight )
                {
                mode++;
                if(mode >= kLcdDispNumber)
                    mode = kLcdDispStart;
                }
            if( Buttons == kButtonLeft )
                {
                mode--;
                if(mode < kLcdDispStart)
                    mode = (kLcdDispNumber-1);
                }

            // update display
            lcdMenuDisplay(mode);

            // wait for release or auto repeat time
            for( i=0;i<autoTime;i+=10)
                {
                if( nLCDButtons == kButtonNone )
                    {
                    autoTime = 1000;
                    break;
                    }
                wait1Msec(10);
                }
            // shorten auto repeat for next time
            if( nLCDButtons != kButtonNone )
                autoTime = 250;
            }

        // Center button selects choice
        if( Buttons == kButtonCenter )
            {
            displayLCDCenteredString(1, "<   Selected   >");
            // set the autononomous mode (replaces choice variable from sdrobotics code)
            autoMode = (short)mode;
            wait1Msec(1000);
            return;
            }

        // don't hog cpu
        wait1Msec(25);
        }
}
