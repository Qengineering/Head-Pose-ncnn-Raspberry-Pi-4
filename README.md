# Head Pose estimation Raspberry-Pi-4
![output image]( https://qengineering.eu/images/HeadPose_9.jpg )
## Head pose with the ncnn framework. <br/>
[![License](https://img.shields.io/badge/License-BSD%203--Clause-blue.svg)](https://opensource.org/licenses/BSD-3-Clause)<br/><br/>
Special made for a bare Raspberry Pi 4, see [Q-engineering deep learning examples](https://qengineering.eu/deep-learning-examples-on-raspberry-32-64-os.html)

------------

## Dependencies.
To run the application, you have to:
- A raspberry Pi 4 with a 32 or 64-bit operating system. It can be the Raspberry 64-bit OS, or Ubuntu 18.04 / 20.04. [Install 64-bit OS](https://qengineering.eu/install-raspberry-64-os.html) <br/>
- The Tencent ncnn framework installed. [Install ncnn](https://qengineering.eu/install-ncnn-on-raspberry-pi-4.html) <br/>
- OpenCV 64 bit installed. [Install OpenCV 4.5](https://qengineering.eu/install-opencv-4.5-on-raspberry-64-os.html) <br/>
- Code::Blocks installed. (```$ sudo apt-get install codeblocks```)

------------

## Installing the app.
To extract and run the network in Code::Blocks <br/>
$ mkdir *MyDir* <br/>
$ cd *MyDir* <br/>
$ wget https://github.com/Qengineering/Head-Pose-ncnn-Raspberry-Pi-4/archive/refs/heads/main.zip <br/>
$ unzip -j master.zip <br/>
Remove master.zip, LICENSE and README.md as they are no longer needed. <br/> 
$ rm master.zip <br/>
$ rm LICENSE <br/>
$ rm README.md <br/> <br/>
Your *MyDir* folder must now look like this: <br/> 
9.jpg <br/>
Group2.jpg <br/>
Group4.jpg <br/>
HeadPose.cpb <br/>
main.cpp <br/>
FaceDetector.cpp <br/>
FaceDetector.h <br/>
face.bin <br/>
face.param <br/>

------------

## Running the app.
To run the application load the project file HeadPose.cbp in Code::Blocks.<br/> 
Next, follow the instructions at [Hands-On](https://qengineering.eu/deep-learning-examples-on-raspberry-32-64-os.html#HandsOn).<br/><br/>
We only use 5 landmarks. For the PnP solver you need at least 6 points. The sixth point (chin) is interpolated from the nose and the corners of the mouth.
Needless to say, there are more accurate methods. But they all require more computing power. The processing speed will therefore be much lower.

------------

### Thanks.
https://github.com/Tencent/ncnn<br/>
https://github.com/nihui<br/>
https://github.com/Linzaer/Ultra-Light-Fast-Generic-Face-Detector-1MB<br/>
https://github.com/biubug6/Face-Detector-1MB-with-landmark/tree/master/Face_Detector_ncnn<br/><br/>

![output image]( https://qengineering.eu/images/HeadPose_2.jpg )

------------

[![paypal](https://qengineering.eu/images/TipJarSmall4.png)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=CPZTM5BB3FCYL) 
