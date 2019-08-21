/* Api to bootup FT801, verify FT801 hardware and configure display/audio pins */
/* Returns 0 in case of success and 1 in case of failure */
int16_t BootupConfigure()
{
	uint32_t chipid = 0;
	LCD.Init(FT_DISPLAY_RESOLUTION);//configure the display to the WQVGA

	delay(20);//for safer side
	chipid = LCD.Read32(FT_ROM_CHIPID);
	
	/* Identify the chip */
	if(FT801_CHIPID != chipid)
	{
		Serial.print("Error in chip id read ");
		Serial.println(chipid,HEX);
		return 0;
	}
	
	/* Set the Display & audio pins */
	LCD.SetDisplayEnablePin(FT_DISPENABLE_PIN);
    LCD.SetAudioEnablePin(FT_AUDIOENABLE_PIN); 
	LCD.DisplayOn(); 	
	LCD.AudioOn();  		
	return 1;
}