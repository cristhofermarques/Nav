## Nav
A small game framework using C

### Build :

* Download and install [XMake](https://xmake.io/#/)

### Windows

* Clone the Repository
* Open the terminal in the 'Nav' folder
* Set compiler that you want to use:

- #### Mingw64 
* Download and install [MSYS](https://www.msys2.org/)
* Open MSYS and run the command to install mingw64
  ######
       pacman -S mingw-w64-x86_64-gcc
       
* Run the command to setup mingw in XMake 
  ######
       xmake f --mingw="[MSYS Install Path]/mingw64"

* Run the command to use Mingw

  ###### Debug
       xmake f -p mingw -m debug
       
  ###### Release
       xmake f -p mingw -m release
       
       
- #### MSVC
* Download and Install Visual Studio
* Install the C/C++ Workload

  ![image](https://user-images.githubusercontent.com/65502434/180671089-8b3b4aed-9695-4c19-aa80-95ce42e5bfbc.png)

* Run the command to use MSVC

  ###### Debug
       xmake f -p windows -m debug
       
  ###### Release
       xmake f -p windows -m release

 
* Run the command to build
  ######
       xmake build
       
