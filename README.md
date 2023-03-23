# Tracking The Sun: An Innovative Dual Axis Solar Tracker With Enhanced Weather Monitoring
This project was completed as part of the **Training_1_On_Mechatronics_MTE390 (internal training)** in my Mechatronics degree at Mansoura University in Egypt.

![image](https://user-images.githubusercontent.com/75787889/227113955-970cc9a1-7100-45d6-b6c1-d4e949467815.png)

## Project Overview
The project aimed to create a solar tracker system that would optimize the amount of solar energy collected while also providing information on weather conditions in real-time. The system makes use of light sensors, temperature sensors, and a rain sensor to accurately monitor weather conditions, while also using a 2 servo motors to track the sun and maximize energy collection.

The project's extensive documentation is contained in **DAST Book Final.pdf**, which provides a detailed account of the entire design and implementation process, including the hardware components used, circuit diagrams, and programming code. The report also includes detailed testing and validation results, demonstrating the effectiveness and accuracy of the solar tracker system in different weather conditions.

![image](https://user-images.githubusercontent.com/75787889/227113739-f211d9a4-123a-4a7c-9f07-20c165f405d4.png) 

## Hardware Components and Overall Budget Analysis
All prices are in Egyptian Pound (EGP)

![image](https://user-images.githubusercontent.com/75787889/227119376-cd952b3e-7283-47eb-be35-6168204bacba.png)

## GENERAL DUAL AXIS TRACKING LOGIC

![image](https://user-images.githubusercontent.com/75787889/227119424-4bd4f149-6d84-46ae-a7f3-b77dc62c4f35.png)

The logic involves a series of steps that work together to ensure accurate and efficient tracking of the sun's movement. The following is an overview of the general dual axis tracking logic:

![image](https://user-images.githubusercontent.com/75787889/227119473-c345ffc7-6b22-448a-b958-b77219a723ef.png)


1-	The first step in the general dual axis tracking logic is to measure the values of the 4 LDR (light dependent resistor) sensors. These sensors are strategically placed and calibrated to accurately measure the light intensity of the sun and determine the direction of the sun's movement.

2-	Next, we compare each opposite pair of sensor readings to determine where the value of the light intensity is greater. This is done to ensure that the solar panel is aligned in the direction of the sun and is receiving the maximum amount of sunlight.

3-	By comparing the Top Left sensor to the Top Right sensor, we are able to determine whether the horizontal servo needs to move to the left or the right. The same process is applied to the Bottom Left and Bottom Right sensors. This allows for precise horizontal tracking of the sun's movement.

4-	Lastly, by comparing the Top Left sensor to the Bottom Left sensor, we are able to determine whether the vertical servo needs to move up or down. The same process is applied to the Top Right and Bottom Right sensors. This allows for precise vertical tracking of the sun's movement.

![image](https://user-images.githubusercontent.com/75787889/227119603-3bf6a8d7-6ddf-4c72-8d55-f229e8c363d3.png)



