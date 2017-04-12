This repository was created for a project using the raspberry pi. Files included are a schematic of the PCB used in conjunction with the pi along with the necessary files to run a GUI to plot outputs.  
Sensors used include:  
1- Temperature Sensor  
2- Moisture/Sweat Sensor  
3- Pulse/Heart Rate Sensor  

The software requires the download of the qt4 and qwt libraries inclusing:
   - qt4-dev-tools
   - ibqt4-dev
   - libqwt-dev


To run the software:  
1- Clone the repository onto your pi with the following link: https://github.com/RaspberryPiTeam5/Exercise-Sensor  
2- build with the command "qmake" followed by "make"  
3- Run the program with "startx ./Exercise" (assuming no X is running whilst on an SSH).  
    
If you require any assistance with regards to this project, please contact either:  
Mustafa Miyasar - 2015221M@student.glasgow.ac.uk  
Roheel Arshad - 2018987A@student.glasgow.ac.uk
