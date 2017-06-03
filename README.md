# SWBF I The Sith Launcher  
It is the launcher for Star Wars Battlefront I, which expend standart game abilities.  

This software is written on C++ (Embarcadero RAD Studio 10.1 Berlin : C++ Builder).  
Including packages :  
- [AlphaControls](http://www.alphaskins.com/index.php)  
- [ZipForge](http://www.componentace.com/download/download.php?editionid=12)  

Including additional libraries :
- LevelPack.exe
- LocalizeMunge.exe

For opening the project you must open **SWBF-I-The-Sith-Launcher.cbproj**  

Also if you want edit something you must disable **Automatic tabs setting** :  
(it is important for saving readability of code on the any device)  
- [ ] Tools -> Options -> Editor Options -> Source Options -> Use tab character
- [x] Tools -> Options -> Editor Options -> Source Options -> Show tab character
- [x] Tools -> Options -> Editor Options -> Source Options -> Show space character  

Some C++/IDE pranks :
1) Error:  
> [ILINK32 Warning] Warning: unknown heap name : 0x08000000 / 0x08000000  
> [ILINK32 Warning] Warning: Error detected (LME286)  
> [ILINK32 Warning] Warning: Unable to perform incremental link - performing full link...  
> [ILINK32 Warning] Warning: unknown heap name : 0x08000000 / 0x08000000  
> [ILINK32 Warning] Warning: unknown heap name : 0x08000000 / 0x08000000  
> [ILINK32 Warning] Warning: Error detected (LME286)  
> [ILINK32 Error] Error: Unable to perform link

Solution: You must run your IDE (bds.exe) with admin privileges.  