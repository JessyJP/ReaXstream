# TODO.md
This is the file that will be updated along with new ideas, suggestions, notes and qustions.

## Question
- [ ] Should I Change the mobile app name ["ReaStreamMobile"](https://github.com/JessyJP/ReaStreamMobile) to "ReaXstreamMobile" also?
- [ ] Should i use ReaXstream image Logo ?
- [ ] Should logger  convenience features be added for beta testers.
- [ ] Should the connection identifier be limited to alphanumerical characters? Technically, it doesn't matter and people can put in whatever they want. 

## ToDO list

### + Logo
- [x] Logo. 
	- [x] Make a logo That could be text or image. 
	- [x] Put it at the top of the GUI.
	
### + Logger
- [x]  Improve the logger.
	- [ ] Make the messages more useful and consistent.
	- [x] Logger button for enable/disable that hides/shows a 
		  separate logger windows or text field under the existing GUI.
		- [ ] This introduces a problem that the logger window is not managed by the editor. Fix this bug.
	- [ ] Decide if the logger should be kept in the releases, therefore the enable disable button should be very useful.
		  In that case a location for file should be chosen.
		  Naming scheme should be chosen.
		  
	- [x] The logger now has a "_CHECK_" macro which can be called with the function call and the expected output.
		  This can be useful to validate functions that have output. Very easy to do a lot of tests on a whole file and can be called anywhere allowing validating under specific input condition. 
		  
		  
### + Unit Test file
- [x] Unit test file made
	- [x] Unit tests can output to the logger, logged file or the standard output depending on wether the logger is enabled.
		  
### + GUI
- [x] GUI improved.
	- [x] GUI redesigned and streamlined. Note: the new design takes less space and is more compact.
 	- [x] Fix the selection enable/disable of protocols when the mode is selected.
		  Notes: about the fix and the issue included at the bottom of the constructor.
	- [x] Technically, the transportation protocol shouldn't be active before the mode is selected. 
		  The mode can be selected before or after the direction of communication. 
		  All protocols will be disabled by default until the user selects the appropriate mode.
	- [ ] Make extra text fields that will be hidden or shown for the shared memory and USB protocols.
		  Technically the same text filed and label could be used, but it would be better to have 3 and show/hide accordingly. This way the fields can keep their values and be used for setting storage in between changes.
    - [ ] Suitable background image should be selected. 
	- [ ] Fancy button image would be nice. 
	- [ ] IP/URL:port filed should have suitable input validation method.
	- [ ] It would be nice to figure out how to add the text filed listener function (that actually works) and use it directly without having to press the apply button. Instead of the apply button the changes should be applied on pressing enter from the user upon changes.
	- [ ] The connection identifier should be limited to 31 characters.
	

### + Internal
- [ ] Complete Interconnector Class
	- [x] Establish a UDP connection for transmission
	- [ ] Establish a TCP connection for transmission
	- [ ] Establish a SharedMemory connection for transmission
	- [ ] Establish a USB connection for transmission
	- [x] Establish a UDP connection for reception
	- [ ] Establish a TCP connection for reception
	- [ ] Establish a SharedMemory connection for reception
	- [ ] Establish a USB connection for reception
	- [x] Close connection UDP
	- [ ] Close connection TCP
	- [ ] Close connection USB
	- [ ] Close connection SharedMemory
- [ ] Complete ReaStreamFrame class
	- [ ] audio frame segmentation for UDP transmission
	
- [ ] Enable ASIO driver for the stand-alone application mode.
	
### + VST parameters
- [ ] Which part of the GUI can be parametrised via VST parameters and should I do that?
- [ ] VST parametrization can enable Load/Save of presets or alternatively a different method could be used to load save the presets.
	  External file could also be used.

	
	
	