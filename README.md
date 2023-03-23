# Tracking The Sun: An Innovative Dual Axis Solar Tracker With Enhanced Weather Monitoring
This project was completed as part of the **Training_1_On_Mechatronics_MTE390 (internal training)** in my Mechatronics degree at Mansoura University in Egypt.

![image](https://user-images.githubusercontent.com/75787889/227113955-970cc9a1-7100-45d6-b6c1-d4e949467815.png)

## Project Overview
The project aimed to create a solar tracker system that would optimize the amount of solar energy collected while also providing information on weather conditions in real-time. The system makes use of light sensors, temperature sensors, and a rain sensor to accurately monitor weather conditions, while also using a 2 servo motors to track the sun and maximize energy collection.

The project's extensive documentation is contained in **[DAST Book Final.pdf](https://github.com/H3EsAwY/TrackingTheSun/blob/main/DAST%20Book%20Final.pdf)**, which provides a detailed account of the entire design and implementation process, including the hardware components used, circuit diagrams, and programming code. The report also includes detailed testing and validation results, demonstrating the effectiveness and accuracy of the solar tracker system in different weather conditions.

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

## Photo Journal

![image](https://user-images.githubusercontent.com/75787889/227121586-072e4279-560d-40fb-a9f2-c29c4188a0fc.png)

![image](https://user-images.githubusercontent.com/75787889/227121618-25ca04a6-ba94-4ac2-b51c-316f24c2ec02.png)

![image](https://user-images.githubusercontent.com/75787889/227122324-64944235-c591-4a00-b120-7ce87eb400a9.png)

![image](https://user-images.githubusercontent.com/75787889/227122411-e122de18-4798-48d0-9968-73f7f9f86ff4.png)

![image](https://user-images.githubusercontent.com/75787889/227121758-4adb8523-203a-4329-baaf-6e7289bb169e.png)

![image](https://user-images.githubusercontent.com/75787889/227121786-6bd4b9ef-08c7-4f03-9b56-335e7227d58a.png)

![20230114_233555](https://user-images.githubusercontent.com/75787889/227121857-ab12edd7-b6bd-497c-8195-86929e3fb0ed.jpg)

![20230114_234853](https://user-images.githubusercontent.com/75787889/227121897-1b85394f-3cd4-4949-9972-a25ae0a412c5.jpg)

![20230116_001851](https://user-images.githubusercontent.com/75787889/227121994-ed1a9aea-85a0-4712-a9ee-c28f4f290fc3.jpg)

![20230116_004705](https://user-images.githubusercontent.com/75787889/227122018-5f0a8a51-5b99-44ee-8259-77e1d4a70fbf.jpg)

![image](https://user-images.githubusercontent.com/75787889/227122599-da2c2798-7033-44a7-aeb5-67ad573579be.png)

![image](https://user-images.githubusercontent.com/75787889/227122652-3433158e-8c60-4f06-9ab6-9e518a9e1d77.png)




