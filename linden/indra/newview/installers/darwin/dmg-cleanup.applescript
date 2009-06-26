-- First, convert the disk image to "read-write" format with Disk Utility or hdiutil
-- Mount the image, open the disk image window in the Finder and make it frontmost, then run this script from inside Script Editor
-- More than likely, the background will be "white" and the background.jpg invisible. There's a bunch of things to do then...
-- Open a Terminal window and navigate to the opened volume, something like : cd /Volumes/Second Life Installer
-- Make the background file visible: SetFile -a v background.jpg
-- With the disk image window still frontmost, go to Finder > View > Show View Options
-- Set the "background" radio button to "Picture" and select the background.jpg file which is in the installer folder
-- In the Terminal window, make the background file invisible again: SetFile -a V background.jpg
-- You need to copy the .DS_Store now but you *need* to close the window, unmount the dmg and remount it! (the .DS_Store is not guaranteed to be updated otherwise!)
-- Copy the .DS_Store file off the dmg to the installers/darwin/<your install> folder from the command line: cp .DS_Store /Users/.../_DS_Store
-- Don't forget to commit that file to svn

tell application "Finder"
	
	set foo to every item in front window
	repeat with i in foo
		if the name of i is "Applications" then
			set the position of i to {391, 165}
		else if the name of i ends with ".app" then
			set the position of i to {121, 166}
		end if
	end repeat
	
	-- There doesn't seem to be a way to set the background picture with applescript, but all the saved .DS_Store files should already have that set correctly.
	
	set foo to front window
	set current view of foo to icon view
	set toolbar visible of foo to false
	set statusbar visible of foo to false
	set the bounds of foo to {100, 100, 600, 399}
	
	-- set the position of front window to {100, 100}
	-- get {name, position} of every item of front window
	
	get properties of front window
end tell
