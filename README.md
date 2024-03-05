# psychic-barnacle
 hazl dll is intended to be injected with hazlaunch which is also
 barebones as hell. the goal is the following:

# STEP 0: we don't do this
 launch to main game process (handled by hazlaunch) but v. easy

# STEP 1: making it not hell to debug
 open a channel to deliver data to the user/developer since like
 stdout is barred from us on this mortal coil or something??

# STEP 2: the extreme basics
 do the detours prerequisite rain dance to activate its
 magic and make sure there's an export def being loaded by VS

# STEP 3: Config
 VCPKG: vcpkg install detours 
 get nop's d2mooheaders or d2moo,
 add all that to the dependencies. 
 you might need c++17 and vc17
 but I might have set them for a library I abandoned. set the vcpkg
 install folder.
 add include folders, i ended up with fog/storm/d2game/d2lang just to
 pull strcat from Unicode (the bastardized Diablo 2 Unicode) and the
 linker settings are tedious as well. set the def while you're there

# STEP 4: Actually Doing Something
 hook LoadLibraryA and LoadLibraryW, we don't need the others
 watch loadlibrary for something we want to patch like d2game
 this is tricky because the game will do recursive reads of dlls
 otoh i don't see the problem if we just do DetourFindPayload or whatever
 and just skip that file if it's a problem. I'm not quite sure 
 how I'm going to handle memory addresses but I can probably do like
 locations["goku.dll"] + 80085 to do goku.dll+80085..
 Ordinals are off the table for now until I become smarter.
