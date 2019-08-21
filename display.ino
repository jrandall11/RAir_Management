/* API to display Hello World string on the screen */
void HelloWorld()
{
	/* Change the below string for experimentation */
	const char Display_string[12] = "Hello World";
	
	/* Display list to display "Hello World" at the centre of display area */
	LCD.DLStart();//start the display list. Note DLStart and DLEnd are helper apis, Cmd_DLStart() and Display() can also be utilized.
	LCD.ColorRGB(0xFF,0xFF,0xFF);//set the color of the string to while color
	LCD.Cmd_Text(FT_DISPLAYWIDTH/2, FT_DISPLAYHEIGHT/2, 29, FT_OPT_CENTER, Display_string);//display "Hello World at the center of the screen using inbuilt font handle 29 "
	LCD.DLEnd();//end the display list
	LCD.Finish();//render the display list and wait for the completion of the DL
}