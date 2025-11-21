#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "alcd.h"
#include <string.h>
#include <avr/eeprom.h>
// EEPROM address for storing password
#define PASSWORD_ADDRESS 0x00
// Global variable for current password
int password;
/***************************************** */
char keypad(void);
int Enter_The_Password();
int change_password();
/************************************************* */
// Function to read password from EEPROM
int read_password_from_eeprom() 
{
    return eeprom_read_word((uint16_t*)PASSWORD_ADDRESS);
}
// Function to write password to EEPROM
void write_password_to_eeprom(int new_password) 
{
    eeprom_write_word((uint16_t*)PASSWORD_ADDRESS, new_password);
}
/*************************************************** */
void main(void)
{   // variables
    
    int counter=0;//to count the numbers of incorrect password //
    int user_password;
    // Keypad setup
    DDRD = 0b00000111;  // PD0-PD2 outputs (rows), PD3-PD6 inputs
    PORTD = 0b01111000; // Pull-ups on columns
    
    //intialization for the lcd
    lcd_init(16);
    lcd_clear();

    // Read password from EEPROM (persistent storage)
    password = read_password_from_eeprom();
    
    // If EEPROM is empty (first run), set default password
    if(password == 0xFFFF) { // EEPROM default value
        password = 1234;
        write_password_to_eeprom(password);
    }

    //if password is false ---> make a loop until he writen the correct password 
    //and if the pasword is written 3 times incorrect make it wait 1 sec to try again
    //and if he write the coorect password it will break the loop
    //while(strcmp(password, "1234") != 0)//this if we dont cast string to integer
    while(1)
    { 
      lcd_clear();
      lcd_gotoxy(0, 0);
      lcd_printf("Enter password:");
      user_password =Enter_The_Password(); //function to enter the password
      //if pasword is true
      if (user_password ==password) //string compare function
        {
            lcd_clear();
            lcd_gotoxy(0, 0);  //go to x y 
            lcd_printf("correct Password");
            _delay_ms(500);
            lcd_clear();
            lcd_printf("unlocked....");
            _delay_ms(500);
            lcd_clear();
            lcd_printf("System is Ready!");
            break;
        }
    //this for change the password
      if(user_password==0000)
       {
        password=change_password();
        write_password_to_eeprom(password); // Save to EEPROM
        lcd_clear();
        continue;// Go back to password entry
       }
      //this for if the password is incorrect
      if(user_password != password)
      {
        lcd_clear();
        lcd_gotoxy(0, 0);
        lcd_printf("Incorrect Password..");
        _delay_ms(500);
        
        counter++; //if false this will count
        if (counter==3)
            { 
                lcd_clear();
                lcd_gotoxy(0, 0);
                lcd_printf("U have Entered 3");
                lcd_gotoxy(0, 1);
                lcd_printf("incorrect password..");
                _delay_ms(2000);
                for(int t=60;t>0;t--)
                { lcd_clear();
                    lcd_gotoxy(0, 0);
                    lcd_printf("please wait....");
                    lcd_gotoxy(0, 1);
                    lcd_printf("%d seconds",t);
                    _delay_ms(100);
                    counter=0; // to make the counter work from begining
                }
            } //end for loop of 3 times incorrect password
            if(user_password==password)
                {
                break; //to exit from the loop
                }
            lcd_clear();
            lcd_printf("Try Again.."); //we write it here to prevent try agin to appear in the third time 
            _delay_ms(500);
      }//end of incorrect password condition
      
      
    }//end of while loop
   
}
/**************************************************************************************** */
char keypad(void)
{
    while (1)
    {
        // Use individual pin checking for safety
        PORTD = 0b01111110; 
        _delay_us(1);
        if (!(PIND & (1 << 3))) { _delay_ms(1); return '1'; }
        if (!(PIND & (1 << 4))) { _delay_ms(1); return '4'; }
        if (!(PIND & (1 << 5))) { _delay_ms(1); return '7'; }
        if (!(PIND & (1 << 6))) { _delay_ms(1); return '*'; }

        PORTD = 0b01111101;
        _delay_us(1);
        if (!(PIND & (1 << 3))) { _delay_ms(1); return '2'; }
        if (!(PIND & (1 << 4))) { _delay_ms(1); return '5'; }
        if (!(PIND & (1 << 5))) { _delay_ms(1); return '8'; }
        if (!(PIND & (1 << 6))) { _delay_ms(1); return '0'; }

        PORTD = 0b01111011;
        _delay_us(1);
        if (!(PIND & (1 << 3))) { _delay_ms(1); return '3'; }
        if (!(PIND & (1 << 4))) { _delay_ms(1); return '6'; } // Number 6
        if (!(PIND & (1 << 5))) { _delay_ms(1); return '9'; }
        if (!(PIND & (1 << 6))) { _delay_ms(1); return '#'; }
        
        _delay_ms(1);
    }
}


int Enter_The_Password()
{  // variables
    char password[5]; // Character array for 4 digits + null terminator
    int i =0;//for the password limit

    //_delay_ms(500);
    //lcd_clear();
    lcd_gotoxy(0, 1);// to make the password written in the second line
    while (i<4) //this loop to write the 4 numbers of the pasword 
    {   
        char key = keypad();
        lcd_printf("%c",key);
        _delay_ms(300);
        password[i]=key; //here each number is clicked is save to password
        i++;
    }

    int pass = 0;
    // Convert "1234" to integer 1234
    for(int i = 0; i < 4; i++) {
        pass = pass * 10 + (password[i] - '0');
    }
    // number now equals 1234
    return pass;
}

int change_password()
{   
    lcd_clear();
    lcd_gotoxy(0,0);
    lcd_printf("Enter the old");
    lcd_gotoxy(0, 1);  // Second line  
    lcd_printf("Password");
    _delay_ms(800);
    // Clear and show input prompt
    lcd_clear();
    lcd_gotoxy(0, 0);
    lcd_puts("Old Password:");
    lcd_gotoxy(0, 1);  // Input will be on second line
    int old_password;
    int counter=0;
    while(old_password != password)
    { 
      int old_password =Enter_The_Password(); //function to enter the password
      //if pasword is true
      if (old_password ==password) //string compare function
        {
            lcd_clear();
            lcd_gotoxy(0, 0);  //go to x y 
            lcd_printf("correct Password");
            _delay_ms(800);
            lcd_clear();
            break;
        }

      //this for if the password is incorrect
      if(old_password != password)
       {
            lcd_clear();
            lcd_gotoxy(0, 0);
            lcd_printf("Incorrect Password..");
            _delay_ms(800);
            
            counter++; //if false this will count
            if (counter==3)
            { 
                lcd_clear();
                lcd_gotoxy(0, 0);
                lcd_printf("U have Entered 3");
                lcd_gotoxy(0, 1);
                lcd_printf("incorrect password..");
                _delay_ms(1000);
                for(int t=60;t>0;t--)
                {   lcd_clear();
                    lcd_gotoxy(0, 0);
                    lcd_printf("please wait....");
                    lcd_gotoxy(0, 1);
                    lcd_printf("%d seconds",t);
                    _delay_ms(100);
                    counter=0; // to make the counter work from begining
                }
            } 
                lcd_clear();
                lcd_printf("Try Again.."); //we write it here to prevent try agin to appear in the third time 
                _delay_ms(800);
                lcd_clear();
                lcd_printf("Old Password: ");  
        }//end of wrong old password condition
    }//end of while loop

    lcd_clear();
    lcd_gotoxy(0,0);
    lcd_printf("Enter the new");
    lcd_gotoxy(0, 1);  // Second line  
    lcd_puts("Password");
    _delay_ms(800);
    // Clear and show input prompt
    lcd_clear();
    lcd_gotoxy(0, 0);
    lcd_printf("New Password:");
    lcd_gotoxy(0, 1);  // Input will be on second line
    int new_password=Enter_The_Password();
    lcd_clear();
    lcd_gotoxy(0, 0);
    lcd_printf("Confirm the");
    lcd_gotoxy(0, 1);
    lcd_printf("new password");
    _delay_ms(700);
    
    int confirm_password;
    while (confirm_password!=new_password)
    {   
        lcd_clear();
        lcd_printf("Repeat password:");
        confirm_password=Enter_The_Password();
        if(confirm_password==new_password)
        {
            break; //to exit from the loop
        }
        lcd_clear();
        lcd_gotoxy(0, 0);
        lcd_printf("Incorrect...");
        lcd_gotoxy(0, 1);
        lcd_printf("Try Again..");
        _delay_ms(700);
    }
    lcd_clear();
    lcd_gotoxy(0, 0);
    lcd_printf("the password has");
    lcd_gotoxy(0, 1);
    lcd_printf("been changed");
    _delay_ms(1000);
    write_password_to_eeprom(new_password); // Save to EEPROM


    return new_password;
}