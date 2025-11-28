# Multi-Mode-HID

This was a College project. We were told to use an STM32 mictrcontroller (Specifically the NUCLEO-F303RET6) to make anything we want
the basic requiremnt from there side was to use nothing but C lang to make the project, or so i thought apprently we couldve used a lot 
more things. 

Anyway most of this project is done is C, but because of the fact that the Nucelo board can't have an HID port connected to it (and the connecter 
that can kind of work around this i didn't have). That aside the project files work for two types of connection to run these payloads.

Either through USB conenctivity(How a HID ideally should be working) or using UART connectivty (what i Used to run the Demo for my project)
The IOC file has connection specifics if one wants to use the USB connectivity, but i would suggest if you are doing so it's ideal you have a 
Blue pill (STME32F303RET6) bare chip and not a board so that you can actually attach an HID USB port to its pins.

