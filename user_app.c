/*!*********************************************************************************************************************
@file user_app.c                                                                
@brief User's tasks / applications are written here.  This description
should be replaced by something specific to the task.

------------------------------------------------------------------------------------------------------------------------
GLOBALS
- NONE

CONSTANTS
- NONE

TYPES
- NONE

PUBLIC FUNCTIONS
- NONE

PROTECTED FUNCTIONS
- void UserApp1Initialize(void)
- void UserApp1Run(void)


**********************************************************************************************************************/

#include "configuration.h"

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_<type>UserApp1"
***********************************************************************************************************************/
/* New variables */
volatile u8 G_u8UserAppFlags;                             /*!< @brief Global state flags */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */
extern volatile u32 G_u32SystemTime1ms;                   /*!< @brief From main.c */
extern volatile u32 G_u32SystemTime1s;                    /*!< @brief From main.c */
extern volatile u32 G_u32SystemFlags;                     /*!< @brief From main.c */


/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "UserApp_<type>" and be declared as static.
***********************************************************************************************************************/


/**********************************************************************************************************************
Function Definitions
**********************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------*/
/*! @publicsection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
/*! @protectedsection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------------------------------------------------
@fn void UserAppInitialize(void)

@brief
Initializes the application's variables.

Should only be called once in main init section.

Requires:
- NONE

Promises:
- NONE

*/
void UserAppInitialize(void)
{

    LATA= 0x80; //RA7 digital high
    T0CON0= 0x90; // 16 bit timer0 1:1
    T0CON1= 0x54; // Synchronous timer0 1:16

} /* end UserAppInitialize() */

  
/*!----------------------------------------------------------------------------------------------------------------------
@fn void UserAppRun(void)

@brief Application code that runs once per system loop

Requires:
- 

Promises:
- 

*/
void UserAppRun(void)
{
    static u8 au8Pattern[6] = {0x21, 0x31, 0x29, 0x25, 0x23, 0x21}; //pattern design
    static u8 u8Index=0;
    static u16 u16Counter=0;
    
    if (u16Counter>=500) {  
        if (u8Index==6)   //end of the pattern array is reached
        {
            u8Index=0;   //re-start array pattern
        }
        LATA= au8Pattern[u8Index];   //LATA gets the different index values of the array
        u8Index= u8Index + 1;        
        u16Counter=0;
        }
    else {
        u16Counter= u16Counter +1;    //incrementing counter by 1
    }  
    
} /* end UserAppRun */

/*!----------------------------------------------------------------------------------------------------------------------
void TimeXus(u16Microseconds_)
Sets Timer0 to count to u16Microseconds_
 
Requires:
- Timer0 configured such that each timer tick is 1 microsecond
- u16Microseconds_ is the value in microseconds to time from 1 to 65535
Promises:
- Pre-loads TMR0H:L to clock out desired period
- TMR0IF cleared
- Timer0 enabled
 */


void TimeXus(u16 u16Timer_) {
    
    u16 u16Count=0xFFFF - u16Timer_;
    T0CON0 = 0x10; //Disable timer during configuration   
    TMR0H = u16Count>>8; // Shifting to make 16-bit number fit in 8-bit register
    TMR0L & 0xFF; // PreloadmTMR0L 
    PIR3 &= 0x7F; //Clear TMR0IF
    T0CON0 =0x90; //Enable timer    
    
}

/*------------------------------------------------------------------------------------------------------------------*/
/*! @privatesection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/





/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
