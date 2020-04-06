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
The Axolotl ROV is intended to be a scientific observation class ROV. It's purpose is to collect scientific enviromental data, push them to the base station where they are presented to the operator in an LCD screen and saved in an SD memory card as a .txt file. The base station has a color LCD screen for the video feed and an LCD monochrome display for telemetry information. The user has access to a four-way joystick that controls the ROV's movement in the X-Y axis, a two-way switch controlling the movement in the Z axis and a potentiometer that adjusts the speed / sensitivity of the ROV. The main feature that differentiates this ROV system, is it's "wireless" connectivity between the controller and the vehicle.

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
