# Axolotl Remote Operation Vehicle(ROV)


![Wet testing](https://i.imgur.com/QgJ95M6.jpg)

This repo tracks the built progress of the Axolotl ROV.

Axolotl is a wirelessly controlled ROV concept,
designed and built as a dissertation project for ELMEPA.

## Key Features
* Four reversibe motors. Two for sink and resurfacing control(Z axis), plus two for direction control (X/Y axis).

* Wireless 2-way Communication using the 2.4Ghz band between the ROV and the base station.

* Enviromental data collection, including pressure, light intensity and water temperature.

* Live streaming video feed to the base station using the 5.8Ghz band.

* Visualisation of the data collected at pre-set intervals.

* Modular design upgradeability.

## Build Logic.
The Axolotl ROV is intended to be a scientific observation class ROV. It's purpose is to collect scientific enviromental data, push them to the base station where they are presented to the operator in an LCD screen and finally saved in an SD memory card as a .txt file. The base station has a color LCD screen for the video feed and an LCD monochrome display for telemetry information.

The user has access to a four-way joystick that controls the ROV's movement in the X-Y axis, a two-way switch controlling the movement in the Z axis and a potentiometer that adjusts the speed / sensitivity of the ROV.

The main feature that differentiates this ROV system from other similar builds, is it's "wireless" connectivity between the controller and the vehicle. The drawback is that the ROV has to be connected with a float at the surface containing the com antennas at all times, as the radiowaves are not able to penetrate water.

The ROV has a metal frame and a pvc main body. The camera is housed separately in a metal watertight enclosure. Navigating in horizontal plane is achieved by two DC motors with coarse pitch propellers which are mounted in the front part of the vehicle. Navigation in the vertical plane, is achieved by two less powerful motors with fine pitch propellers, mounted at the top side of the vehicle. All the motors are connected to H-bridges that allows them to be driven in both directions. The front motors are able to move independently from each other. The top motors are "tied" to work together from our software. The vehicle's weight is adjusted manually before a diving session by adding or removing weight from  two canisters at the bottom of the ROV. We can adjust it for Negative/Neutral/Positive buoyancy.

The communication for control and telemetry works as follows: Every command input is checked and saved in a structure that contains a sum of the commands. That structure is then transmitted to the ROV that constantly listens and works it's motors according to the content of the structure. The vehicle also collects and transmits values from the environmental sensors in every microcontroller circle. The base station receives the telemetry in every microcontroller circle but only logs and presents the results to the user in preset intervals.


## Repo Structure
* Bill of materials - Contains a file documenting all the materials needed for this build.
* Built sample photos - Contains some photographs documenting the process of building the two versions of the ROV.
* Receiver_Rov Code - Contains the .ino file with the code for the microcontroller mounted on the ROV.
* Schematics - Contains two subfolders named "Controller" and "Rov_main" that in turn they contain the respective Schematics of the Main ROV and the base.
* Transmitter_Rov Code - Contains the .ino file with the code for the microcontroller mounted on the base station.
* Buit_process.pdf - A build log of the project.

### Initial testing sample photos.


![Data stream](https://i.imgur.com/tYGLUbs.jpg)

![Data log](https://i.imgur.com/Z2U7ToKg.jpg)

![Dry testing](https://i.imgur.com/3jcBtBa.jpg)
