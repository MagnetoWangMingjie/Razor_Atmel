/**********************************************************************************************************************
File: user_app1.c                                                                

----------------------------------------------------------------------------------------------------------------------
To start a new task using this user_app1 as a template:
 1. Copy both user_app1.c and user_app1.h to the Application directory
 2. Rename the files yournewtaskname.c and yournewtaskname.h
 3. Add yournewtaskname.c and yournewtaskname.h to the Application Include and Source groups in the IAR project
 4. Use ctrl-h (make sure "Match Case" is checked) to find and replace all instances of "user_app1" with "yournewtaskname"
 5. Use ctrl-h to find and replace all instances of "UserApp1" with "YourNewTaskName"
 6. Use ctrl-h to find and replace all instances of "USER_APP1" with "YOUR_NEW_TASK_NAME"
 7. Add a call to YourNewTaskNameInitialize() in the init section of main
 8. Add a call to YourNewTaskNameRunActiveState() in the Super Loop section of main
 9. Update yournewtaskname.h per the instructions at the top of yournewtaskname.h
10. Delete this text (between the dashed lines) and update the Description below to describe your task
----------------------------------------------------------------------------------------------------------------------

Description:
This is a user_app1.c file template 

------------------------------------------------------------------------------------------------------------------------
API:

Public functions:


Protected System functions:
void UserApp1Initialize(void)
Runs required initialzation for the task.  Should only be called once in main init section.

void UserApp1RunActiveState(void)
Runs current task state.  Should only be called once in main loop.


**********************************************************************************************************************/

#include "configuration.h"

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_UserApp1"
***********************************************************************************************************************/
/* New variables */
volatile u32 G_u32UserApp1Flags;                       /* Global state flags */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */
extern volatile u32 G_u32SystemFlags;                  /* From main.c */
extern volatile u32 G_u32ApplicationFlags;             /* From main.c */

extern volatile u32 G_u32SystemTime1ms;                /* From board-specific source file */
extern volatile u32 G_u32SystemTime1s;                 /* From board-specific source file */


/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "UserApp1_" and be declared as static.
***********************************************************************************************************************/
static fnCode_type UserApp1_StateMachine;            /* The state machine function pointer */
//static u32 UserApp1_u32Timeout;                      /* Timeout counter used across states */


/**********************************************************************************************************************
Function Definitions
**********************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------*/
/* Public functions                                                                                                   */
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
/* Protected functions                                                                                                */
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------
Function: UserApp1Initialize

Description:
Initializes the State Machine and its variables.

Requires:
  -

Promises:
  - 
*/
void UserApp1Initialize(void)
{
 
  /* If good initialization, set state to Idle */
  if( 1 )
  {
    UserApp1_StateMachine = UserApp1SM_Idle;
  }
  else
  {
    /* The task isn't properly initialized, so shut it down and don't run */
    UserApp1_StateMachine = UserApp1SM_FailedInit;
  }

   LedOff(WHITE);
  LedOff(PURPLE);
  LedOff(BLUE);
  LedOff(CYAN);
  LedOff(GREEN);
  LedOff(YELLOW);
  LedOff(ORANGE);
  LedOff(RED);
  
} /* end UserApp1Initialize() */

  
/*----------------------------------------------------------------------------------------------------------------------
Function UserApp1RunActiveState()

Description:
Selects and runs one iteration of the current state in the state machine.
All state machines have a TOTAL of 1ms to execute, so on average n state machines
may take 1ms / n to execute.

Requires:
  - State machine function pointer points at current state

Promises:
  - Calls the function to pointed by the state machine function pointer
*/
void UserApp1RunActiveState(void)
{
  UserApp1_StateMachine();

} /* end UserApp1RunActiveState */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Private functions                                                                                                  */
/*--------------------------------------------------------------------------------------------------------------------*/


/**********************************************************************************************************************
State Machine Function Definitions
**********************************************************************************************************************/

/*-------------------------------------------------------------------------------------------------------------------*/
/* Wait for ??? */
static void UserApp1SM_Idle(void)
{
  static u16 u16counter=0;//counter the length of the password you've entered
  static u16 u16a[10]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};//record what you've entered for your password
  static u16 u16acounter=0;//remember the length of your password
  static u16 key=-1;//judge whether you are right or wrong
  static u16 two=0;//judge whether you are creating or decoding
  static u16 u16time=0;//+5 Initialize
  static u16 shunxu=100;
  static u8 once=0;
  if( IsButtonPressed(BUTTON3))
  {
    if(u16time<=10000)
    {
    u16time++;
    
    }
    if (once==0)
    {
    if(u16time>=5000)
   {
       LedBlink(GREEN, LED_2HZ);
        LedBlink(RED, LED_2HZ);
        shunxu=G_u32SystemTime1s;
       
     }
      ButtonAcknowledge(BUTTON3);
  }
  }
  if( (IsButtonPressed(BUTTON3)==0)&&(u16time<5000))
  {
  u16time=0;
  }
 
 
 if (G_u32SystemTime1s>shunxu)
 {
   once=1;
  if(two==0)//enter
  {
    if( WasButtonPressed(BUTTON3)==0)
{
  
  if(u16acounter<=9)
 {  
   if( WasButtonPressed(BUTTON0) )
 {
   u16a[u16acounter]=0;
   u16acounter++;
   ButtonAcknowledge(BUTTON0);
 }
 if( WasButtonPressed(BUTTON1) )
 {
    u16a[u16acounter]=1;
   u16acounter++;
   ButtonAcknowledge(BUTTON1);
 }
 if( WasButtonPressed(BUTTON2) )
 {
    u16a[u16acounter]=2;
   u16acounter++;
   ButtonAcknowledge(BUTTON2);
 }
 
 }
}
if( WasButtonPressed(BUTTON3))
  {
    u16acounter--;
    two++;
    LedOn(RED);//lock
    LedOff(GREEN);
    ButtonAcknowledge(BUTTON3);
  }
  }
//enter
  
  
  if(two==1)//decode
  {
  if(u16counter<=u16acounter)
 {
  
   if( WasButtonPressed(BUTTON0) )
 {
   if(u16a[u16counter]==0)
   {
     key++;
    }
   else
     key=-1;
   u16counter++;
   ButtonAcknowledge(BUTTON0);
 }
 if( WasButtonPressed(BUTTON1) )
 {
   if(u16a[u16counter]==1)
     key++;
   else
     key=-1;
   u16counter++;
   ButtonAcknowledge(BUTTON1);
 }
 if( WasButtonPressed(BUTTON2) )
 {
   if(u16a[u16counter]==2)
     key++;
   else
     key=-1;
   u16counter++;
   ButtonAcknowledge(BUTTON2);
 }
 }

 if( WasButtonPressed(BUTTON3) )
 {
   
   ButtonAcknowledge(BUTTON3);
 
   u16counter=0;
   if (key==u16acounter)//password is right
   {
     key=-1;
     LedBlink(GREEN, LED_2HZ);//you are right
     LedOff(RED);
   }
   else
   {
     key=-1;
     LedBlink(RED, LED_2HZ);//you are wrong
     LedOff(GREEN);
   }
   
 
  }
  }
 }
} /* end UserApp1SM_Idle() */
    
#if 0
/*-------------------------------------------------------------------------------------------------------------------*/
/* Handle an error */
static void UserApp1SM_Error(void)          
{
  
} /* end UserApp1SM_Error() */
#endif


/*-------------------------------------------------------------------------------------------------------------------*/
/* State to sit in if init failed */
static void UserApp1SM_FailedInit(void)          
{
    
} /* end UserApp1SM_FailedInit() */


/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
