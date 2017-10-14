# SWBF I The Sith Launcher  
## English
It is the launcher for Star Wars Battlefront I, which expend standart game abilities.  

This software is written on C++ (Embarcadero RAD Studio 10.2 Tokyo : C++ Builder).  
Including packages :  
- [AlphaControls](http://www.alphaskins.com/index.php)  
- [ZipForge](http://www.componentace.com/zip_component_zip_delphi_zipforge.htm)  

Including additional libraries :
- LevelPack.exe
- LocalizeMunge.exe
- Battlebelk's Custom Resolution Launcher (ResolutionChanger.exe)

### Bugs or other questions
Write your issue [there](https://github.com/Foxente/SWBF-I-The-Sith-Launcher/issues) or you can write me a private letter (aradam@o-coder.pp.ua).

### How to contribute/edit this project
1) Install [RAD Studio 10.2 Tokyo (It contains Delphi and C++ Builder)](https://www.google.com/search?q=RAD+Studio+10.2+Tokyo+download+torrent) or [C++ Builder XE 10.2 Tokyo only](http://www.google.com/search?q=C%2B%2B+Builder+XE+10.2+Tokyo+download+torrent). 
2) Install the latest version of [AlphaControls for XE 10.2](http://www.alphaskins.com/dwnld.php). All guides are [there](http://www.alphaskins.com/showdoc.php?l=en&n=1).
3) Install the latest version of [ZipForge for XE 10.2](http://www.componentace.com/download/). You must run install.exe and install this lib.
4) You must remember the folders where are this libs.As for me, i install it in my folder "libs" : **C:\Program Files (x86)\RadStudio\libs\AlphaSkins** and **C:\Program Files (x86)\RadStudio\libs\ZipForge\Lib\Delphi 10.2 and C++ Builder 10.2 (Tokyo)**.
5) You must add global paths to packages in the IDE :  
  5.1) Open the IDE (as for me it is file **C:\Program Files (x86)\RadStudio\bin\bds.exe**).  
  5.2) Open Tools->Options...  
  ![default](https://user-images.githubusercontent.com/12220551/31548642-2b4fc506-b034-11e7-9405-9bbc1b143b62.png)  
  5.3) Open Environment Options-> C++ Options -> Paths and Directories.  
  ![default](https://user-images.githubusercontent.com/12220551/31548987-5f31d5b6-b035-11e7-8bc9-5c4fcdc8c31a.png)  
  5.4) Click on the [...] button (near System **Include Path**) and add ZipForge's path.  
  ![default](https://user-images.githubusercontent.com/12220551/31549116-dad8d2dc-b035-11e7-8123-85a30ca4a79c.png)  
  5.5) Click on the [...] button (near **Library Path**) and add package's path.  
  ![default](https://user-images.githubusercontent.com/12220551/31549311-77fb5198-b036-11e7-972e-f7941b705112.png)  
6) Download the launcher's source code from this repository and open **SWBF-I-The-Sith-Launcher.cbproj**.
7) Enjoy! You can do pull requests and send your changes to this repository.

### Recommendations
If you want to edit this source code - you must disable options that control Tab/space symbols  
(it is important for saving readability of code on the any device)  
- [ ] Tools -> Options... -> Editor Options -> Source Options -> Use tab character
- [x] Tools -> Options... -> Editor Options -> Source Options -> Show tab character
- [x] Tools -> Options... -> Editor Options -> Source Options -> Show space character  
  
The names of **constants** must be in upcase like AUTHOR, CURRENT_VERSION.  
The names of **variables** must be in different registers like int I, UnicodeString AddonName.  
The names of **functions** must be in different registers like GetLauncherDataPath, IsBattlefrontRunning.  

### Some C++/IDE pranks :
1) Error:  
> [ILINK32 Warning] Warning: unknown heap name : 0x08000000 / 0x08000000  
> [ILINK32 Warning] Warning: Error detected (LME286)  
> [ILINK32 Warning] Warning: Unable to perform incremental link - performing full link...  
> [ILINK32 Warning] Warning: unknown heap name : 0x08000000 / 0x08000000  
> [ILINK32 Warning] Warning: unknown heap name : 0x08000000 / 0x08000000  
> [ILINK32 Warning] Warning: Error detected (LME286)  
> [ILINK32 Error] Error: Unable to perform link

Solution: You must run your IDE (bds.exe) with admin privileges.  
