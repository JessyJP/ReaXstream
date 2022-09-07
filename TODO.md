# TODO.md
This is the file that will be updated along with new ideas, suggestions, notes and qustions.

## Question
- [ ] Should I Change the mobile app name ["ReaStreamMobile"](https://github.com/JessyJP/ReaStreamMobile) to "ReaXstreamMobile" also?

## ToDO list

### + Logo
- [ ] Logo. 
	- [ ] Make a logo That could be text or image. 
	- [ ] Put it at the top of the GUI.
	
### + Logger
- [ ]  Improve the logger.
	- [ ] Make the messages more useful and consistent.
	- [ ] Logger button for enable/disable that hides/shows a 
		  separate logger windows or text field under the existing GUI.
	- [ ] Decide if the logger should be kept in the releases, therefore the enable disable button should be very useful.
		  In that case a location for file should be chosen.
		  Naming scheme should be chosen.
		  
### + GUI
- [ ] GUI
	- [ ] Fix the selection enable/disable of protocols when the mode is selected.
	- [ ] Make extra text fields that will be hidden or shown for the shared memory and USB protocols.
		  Technically the same text filed and label could be used, but it would be better to have 3 and show/hide accordingly. This way the fields can keep their values and be used for setting storage in between changes.
    - [ ] Suitable background image should be selected. 
	- [ ] Fancy button image would be nice. 
	- [ ] IP/URL:port filed should have suitable input validation method.
	- [ ] It would be nice to figure out how to add the text filed listener function (that actually works) and use it 	   directly without having to press the apply button. Instead of the apply button the changes should be applied 	 on pressing enter from the user upon changes.

### + Internal
- [ ] Complete Interconnector Class
	- [ ] Establish a UDP connection for transmission
	- [ ] Establish a TCP connection for transmission
	- [ ] Establish a SharedMemory connection for transmission
	- [ ] Establish a USB connection for transmission
	- [ ] Establish a UDP connection for reception
	- [ ] Establish a TCP connection for reception
	- [ ] Establish a SharedMemory connection for reception
	- [ ] Establish a USB connection for reception
- [ ] Complete ReaStreamFrame class
	- [ ] audio frame segmentation for UDP transmission
	
### + VST parameters
- [ ] Which part of the GUI can be parametrised via VST parameters and should I do that?
- [ ] VST parametrization can enable Load/Save of presets or alternatively a different method could be used to load save the presets.
	  External file could also be used.

	
	
	