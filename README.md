ECE382_Lab8
===========

# Lab 8 - Robot Maze

# Purpose

This lab will combine the two previous lab assignments in order to program my robot to navigate through a maze. The robot must autonomously navigate through the maze meeting the following requirements:
 1. The robot must always start in the home position
 2. It is considered successful only if the robot finds one of the three exits and moves partially out of the maze.
 3. Door 1 - required functionality
 4. Door 2 - B functionality
 5. Door 3 - A Functionality
     a. Robot cannot hit a wall.
 6. Must solve the maze in less than 3 minutes
 7. Robot will be stopped if it touches a wall more than twice
 8. Must use IR sensors to find path through the maze
    
# Prelab

I plan on having my robot follow the left wall out of the maze, regardless of which door it is going through. The main loop will look something like this:

      for (;;)
          If center sensor is not detected 
            Then move forward
          else if center sensor is detected and no other sensor triggered
            turn left
          else if center sensor && left sensor triggered
            turn right
          if left sensor not trigggered
            make slight left movement until triggered then move forward
            
The schematic below combines the wiring from the past two labs to form the functioning robot. 
            
  ![alt text] (https://raw.github.com/CassieMcPeek/ECE382_Lab8/master/Schematic.jpg "Schematic")

# Required Functionality

I had a lot of problems at the beginning of this lab. I could get my IR sensors to sense at pretty decent distances, which I checked using the LEDS. But once I put it in the maze, they didn't seem to work very well. First, I had to play with the threshold values a lot to try and find ones that worked for each sensor individually. That was a constant struggle for the longest time, but once I had those sort of figured out, I had to fix the speed. My robot moves extremely fast, even when the duty cycles are decreased. In order to combat this, I had to decrease the duty cycles as well as add multiple delay cycles statements to help slow the robot down. 

Before I tired slowing down my robot, it would go so fast that it would slam into the center wall without even slowing down. Unfortunately, once it slammed into the wall, it tried to turn, but struggled. After multiple times of this occuring, I decided to slow it down like I described above. Once I had slowed the robot down enough for the IR sensors to dectect walls, it seemed to work better. 

Another issue I ran into was my logic. I began with a very complicated logic scheme in order to try and get A functionality right away. I soon found out that it was much easier to program the robot in stages instead of overwhelming it right away. I then focused on required functionaly only. This was a pretty easy thing to code because it only had one turn in it. So I used the code below to have the robot move forward until it sensed a wall, and then turn left. 

    if (centerSensor >=0x190)
     {
         turnLeftBig();
         _delay_cycles(10000);
       	 stopMovement();
       	 _delay_cycles(100000);
      }
    else if (centerSensor() < 0x190)
    	 {
    		 moveForward();
    		 _delay_cycles(100000);
    	 }

This code worked well for the required functionality, and I demonstrated this to Dr. Coulston on 11 DEC 2014 at 1500.

# B Functionality

The code above worked will with required functionality, but for B functionality, there is a right turn that must be made, which the code doesn't account for. Therefore, I decided to follow the left wall through the maze by using Dusty Weisner's technique of using a max and min threshold of how close the robot should be to the left wall. This took some more time to determine useful values for the max and min thresholds of the left IR sensor. Once I found the thresholds, I had to make sure that if the robot was not within that distance from the wall, that it corrected itself. I used the following code to do this:

       	 if(leftSensor() < 0x190)
    	     {
    		      	turnLeftLittle();
    			     _delay_cycles(9000);
    			     stopMovement();
    		    	_delay_cycles(100000);
    	     }
    	    if(leftSensor() >= 0x180)
    	     {
    		      turnRightLittle();
    		     _delay_cycles(9000);
    		      stopMovement();
   			    _delay_cycles(100000);
    	     }

Once I had that done, I needed to add the code to make a right turn if both the left sensor and center senser were triggered. The following code completed this task:

      	 if (centerSensor() >=0x180 && leftSensor() >= 0x170)
    	      {
    		        turnRightBig();
    		        _delay_cycles(10000);
    		        stopMovement();
    		       _delay_cycles(100000);
    	       }
    	       
While this code had the right logic, there was a slight issue with it. Because I had it following the left wall, instead of waiting until it sensed the center wall to turn left (like in required functionality), I wanted it to make a turn as soon as the left wall was no longer detected. This was done by using the threshold code above, but it made too wide of a turn. The wide turn made it hard for the robot to get back and follow the left wall in time to detect the center wall and make a right turn. So, in order to make the robot turn sharper, I changed the way the robot turned. Instead of stopping one motor and only having one move forward to turn the robot, I did a tank turn. For this, I had one motor moving forward, while the other moved backwards. This made the turn sharper and therefore the robot could follow the wall more easily.

# A/Bonus functionality

I have good code to get through the third door, the only problem is that my robot hits the wall at various times. I think this is due to the shadows in the maze that distract the IR sensors. In order to combat this, I tried using a different maze and increasing the threshold for sensing the left wall. 

After playing with the threshold values and trying all three mazes, I was able to acheive A functionality and Bonus functionality. I cemonstrated A functionality to Capt Trimble, and then demonstrated Bonus functionality to Mr. Evans during class on 12 DEC 2014 around 1250. 

# Conclusion

This lab was quite frustrating at times becuse the IR sensors were not very reliable. It took a lot of testing and debugging to find the right thresholds for the sensors that would guide the robot through the maze. Once I was able to find decent thresholds, it just took a lot of testing to complete the A and Bonus functionalities. With the shadows in the mazes, the robot would make it through fine one time, but the next time would run into a wall at a random point. Even though there were a lot of isseus, this was defintely the best lab out of the class

# Documentation

C2C Dusty Weisner assisted me a lot in debugging my code. He gave me the idea to use a max and min threshold for how close the robot should be to the left wall in order to make it through the maze. He also helped me a lot in determining the threshold of my sensors in order to have them be triggered at a reasonable distance from the wall. 
