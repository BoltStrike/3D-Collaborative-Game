# 3D-Collaborative-Game
A 3D videogame and videogame engine created in C++ using OpenGL v3.3 and GLFW v3.3.2 libraries.
<!--## Table of Contents
* [Files](##-Files)
  * [File Formats](#-File-Formats)
    * [JSON](#-JSON)
    * [UBJ](#-UBJ)
  * File Types
    * Settings
    * Game Save
    * Assets
-->
## Managers
The manages all control diffrent parts of the game. The interface of each of the managers shoul be kept simple, so that future changes to the internals of the manager do not change the interface.

One thing that is missing is some way to store all the items.
### Physics Manager
The physics manager controls the simulation of all bodies in the game. It is also responsabel for physics updates.
#### Collider Manager
This part of the Physics Manager is responsabel for loading the collider modles from the files
### Graphics Manager
This manages all graphics. It will also likly have a model manager componant.
### Input Manager
The Input Manager is responsable for taking in raw user input and maping it to the correct action. For instance in one context the key 'W' may mean forward while in others it means the char 'W'
### Event Manager (are we doing it this way?)
### Game Save manager
This manages the game save. This includes autosaves (probably a long way out) and loading in chuncks as needed. This manager will have to interact with many other manages.
### Log Manager
This manager is a bit diffrent thant the others in that it will be the first thign to run. It will then start up the main loop in a new thread. This will make it so that if the game crashes then the log will still be intact. This will require mutexes for the data. It will also need to check on the status of the other thread and if it has crashed then access the data behing the mutex, so that all entreis are recorded. The log files will have to be named using the time and date in a particular time zone, to prevent overighting previous logs.
## Files
This section describes all the non programing files
### File Formats
This section describes how the files are encoded. The file extention is influenced by [File Type](#File-Type) more than the format.
#### JSON
JSON is a standard file fromat that alows for data to be stored in a human readable format. More information can be found here: https://www.json.org/json-en.html

In the context of the game this format is only to be used when a file may need to be editable by the player and does not contain large amounts of data. JSON should not be used for anything that need to be read quickly.
#### UBJ
UBJ stands for Universal Bianary JSON. It is a modified version of JSON. The advantage it has is that numbers are already stored in the same format as the cmputer needs them leading to faster load times. Using UBJ over JSON can also reduce filesize by cutting out some formating overhead and useing binary when posible, as oposed to ASCII.It also alows arrays and strings to be loaded into C++ easer. More information can be found here: https://ubjson.org/

This format should be used, unless there is a strong reason to do otherwise. Currently there is no fully functional editor for this file format. There is the (UBJconsoleEditor)[../ubjViewerTool/tools/ubjConsoleEditor], but it is incompleate and only has the UI to view the file. This will likly be replaced by an HTML5 & JavaScript version.
### File Types
#### Settings
Format: JSON (posibly with whitespace)

The setting file store all the user adjustable settings.This includes graphics, audio, and keybindings. It will be in JSON. It may even be worth adding in the standard whitespace to make it easer to read and edit. The file should get loaded once at startup and saved anytime the player accepts changes to the settings.
#### Game Save
Format: UBJ

This file should contain all information needed to load the game from where it was last saved. This file sould contain the minimum amount of information to store the game state.
#### Assets
Format: UBJ (multiple files)

These file should contain all the assets for the game including graphics and static physics information. These will be seperate files as needed. The assets should make up the bulk of the size of the game.
