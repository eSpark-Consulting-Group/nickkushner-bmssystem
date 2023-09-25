# nickkushner-bmssystem
This repository will contain the latest project progress


## Project Requirements Document v1.0

## Introduction
Design a custom BMS for 18650 Battery packs. The BMS should have all standard functions including: Over charging protection, balance charging, over discharge protection and high temp detection.

## Requirements
1. Design for BMS should be done with a 3S1P 18650 Battery Pack 11.1V.
2. The board should have over charging protection, balance charging, over discharge protection and high temp detection.
3. Modular design allowing the combination of boards to manage very large battery packs in series. This means that the BMS can be stacked with another BMS to increase the capability of the overall product.
4. The ability to detect and locate bad batteries in a cell.
5. Variable max current charge and discharge settings.
6. Communication via I2C for more advance projects to monitor battery information.
7. Easy charging for any size of pack with variable voltage supplies (etc 5V for smaller packs but 24V for larger packs combined with multiple boards.

## Concept Image
![image](https://github.com/eSpark-Consultants/nickkushner-bmssystem/assets/76909080/4c234384-0dee-4cd2-a84b-85dfaf8b73d3)

## To confirm
1. Client hasn't yet confirmed the maximum current limit. This is in negotiation.
