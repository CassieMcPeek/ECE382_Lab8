ECE382_Lab8
===========

# Lab 8 - Robot Maze

# Purpose

This lab will combine the two previous lab assignments in order to program my robot to navigate through a maze. The robot must autonomously navigate through the maze meeting the following requirements:
 1. The robot must always start in the home position
 2. It is considered successful only if the robot finds one of the three exits and moves partially out of the maze.
 3. Door 1 - required functionality
 4. Door 2 - B functionality
 5. Door 3 - A Functionalit
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

# Functionality

# Conclusion

# Documentation

C2C Dusty Weisner assisted me a lot in debugging my code. He gave me the idea to use a max and min threshold for how close the robot should be to the left wall in order to make it through the maze. He also helped me a lot in determining the threshold of my sensors in order to have them be triggered at a reasonable distance from the wall. 
