# Meeting Notes
In this file, you are required to take notes for your weekly meetings.
In each meeting, you are required to discuss:


1. What each member has done during the week?
2. Are there challenges or problems? Discuss the possible solutions
3. Plan for the next week for everyone
4. Deviations and changes to the project plan, if any




# Meeting 29.10.2023 14:30-16:30


**Participants**:
1. Artur Brander
2. Aape Hartikainen
3. Jaakko Karhu
4. Jiri Simell


## Summary of works
All of the group members introduced themselves to the project description.
The project description and guidelines were used to create a project plan.


## Challenges


1. It’s a bit difficult to figure out all of the classes and their functions and variables in the UML diagram now at the beginning of the project because there can always be some variables that are left unnoticed which can affect the whole implementation. Thus it’s important to follow and implement the plan carefully and also make corrections and additions to the initial plan if needed throughout the project.


## Actions
1. The group is going to start to work on the main classes of the simulator. Probably need to assure a couple of details about the functionalities from the group assistant.
2. Artur is going to start working on the Road class.
3. Aape is going to start working on the Building and Person classes.
4. Jaakko is going to start working on the Car and Lane classes.
5. Jiri is going to start working on the TrafficLight and Intersection classes.




## Project status
We have familiarized ourselves with the project requirements. The initial plan for the project is completed. We have agreed on how the work is divided and have discussed what classes and functionality we should implement. 


### TODOs
1. Artur: Implement Road class.
2. Aape: Implement Building and Person classes.
3. Jaakko: Implement Car and Lane classes.
4. Jiri: Implement TrafficLight and Intersection classes.

# Meeting 8.11.2023 10:15-10:45

**Participants**:
Artur Brander
Aape Hartikainen
Jaakko Karhu
Jiri Simell

## Summary of works
1. Aape started implementing the abstract Building class and the residential, industrial and commercial classes inherited from this abstract class. Also the person class is in the making.
2. Artur started the implementation of the Road class
3. Jaakko started to work on the Car and Lane classes.
4. Jiri started to implement the Intersection class.

## Challenges
1. Testing the classes is quite difficult, since the classes have dependencies on features that are yet to be implemented.
2. Commits to the project repository should be made more frequently.

## Actions
1. The group is going to focus on the main classes of the simulator.
2. The group assistant hinted that the group should introduce themselves to the libraries of the project
3. Artur is going to finish the Road class and start working on the Analysis class
4. Aape is going to finish the Building classes and Person class.
5. Jaakko is going to finish the Car and Lane classes.
6. Jiri is going to continue working on the Intersection class and start working on the TrafficLight class.

## Changes to plan 
We will implement a class for a grid and a class for analysis. This will help with structuring the code.

## Project status
The group members have started to work on the classes and they should be finished as soon as possible to acquire information about incompatibilities between the class declarations. 

## TODOs
1. Artur: Finish Road class. Start working on the Analysis class.
2. Aape: Finish Building classes and Person class. Test the functionality of these classes and start looking at the Analysis class.
3. Jaakko: Finish the implementation for Car and Lane classes. Look into the grid class implementation.
4. Jiri: finish the TrafficLight and Intersection classes.
5. Each team member should think about how the addition of the Analysis class and the Grid class will affect the classes they are implementing.

# Meeting 16.11.2023 10:00-11:00

**Participants:**
Artur Brander
Aape Hartikainen
Jaakko Karhu
Jiri Simell

## Summary of works
1. Aape finished the Building class and is working on Person class and started working on the Analysis class together with Artur.
2. Artur finished working on the Road class and started working on the Analysis class with Aape
3. Jaakko implemented the grid and cell classes. Started working on the City class. Started working on the GUI.
4. Jiri created initial implementations of the TrafficLight and Intersection classes.

## Challenges
1. There was a problem with adding an object inherited from Building in the City class. Aape will take a look.
2. How to integrate the SMFL-library to the existing classes.
3. How to calculate the roads that a car should take.
4. There were difficulties with properly implementing the TrafficLight and Intersection classes with no proper Road class implementation.
5. How to add randomness to the simulation.
6. How is time used in the simulation: fast forwarding/starting/pausing the simulation

## Actions
1. Artur is working on the Analysis class. Also going to look into the JSON-file and time libraries. 
2. Aape is working on Person and Analysis classes and starts looking into the SFML library.
3. Jaakko is working on the Car and City classes and getting them to work with the SMFL-library.
4. Jiri is going to continue working on the TrafficLight and Intersection classes.

## Project status
Discarded the implementation of the Lane class and continued to implement these functionalities in the Road class for improved clarity.

## Deviations from the plan:
The plan did not include a Grid class or a Cell class. These were implemented to make the City implementation more clear and easy to manage. 


## TODOs
1. Artur: Try to obtain a .csv file from road analysis and try to output a histogram with this data. Also look into the JSON-file and time libraries.
2. Aape: Look into the random deviation of Persons schedule and finish the Person class. Work on Analysis class.
3. Jaakko: Finish the implementation for Car and get everything to work with the GUI.
4. Jiri: finish the TrafficLight and Intersection classes.

# Meeting 23.11.2023 15:00-16:00
**Participants:**
Artur Brander
Aape Hartikainen
Jaakko Karhu
Jiri Simell

## Summary of works 
1. Aape has worked on the Person class on how the schedule works and on the random property. Also started to work on the Analysis class.
2. Artur struggled with the integration of the JSON- and SFML-libraries. Also continued working on the Analysis class.
3. Jaakko implemented a Node class, worked with the SFML-library to draw the city and cars. Started working on the car movement implementation. 
4. Jiri improved the implementations of the TrafficLight and Intersection classes, and connected them to the City class. Additionally, Jiri created a simple function to the main file that creates a small city.

## Challenges
1. Some of the team members had challenges with running the code.
2. The documentations of some libraries can be a bit cumbersome to digest
3. How to integrate a path finding algorithm for the car movement. 

## Actions
1. Artur is working on the Analysis class. Going to have a look at new JSON libraries, since the older ones didn’t compile.
2. Aape is working on Person and Analysis class. Started looking at SFML library to get the main file to work.
3. Jaakko is working on the Car movement and how to implement some algorithm to calculate optimal paths.
4. Jiri is working on adapting the implementations of the TrafficLight and Intersection classes with the modified City class.

## Project status
## Deviations from the plan:
The plan did not include a Node class. Node class was implemented in order to make it possible to calculate paths for cars. 


## TODOs
1. Artur: Find a new way to use JSON-files in the project. Look more into the data and try to analyze it.
2. Aape: Start modifying the building looks in GUI. Work on Persons schedule and analysis class.
3. Jaakko: Simplify the code in the City class, make cars move in the city according to a schedule. Start implementing an algorithm for path calculation. 
4. Jiri: Implement the handling of situations where the JSON file contains an invalid city.
Each team member should be able to run & compile the project

# Meeting 3.12.2023 11:30-12:30
**Participants:**
Artur Brander
Aape Hartikainen
Jaakko Karhu
Jiri Simell

## Summary of works 
1. Aape has worked on building profiles, adding different types of buildings with their own properties.
2. Artur integrated the JSON-library into the project and made unit tests for it. Additionally, added an initial implementation of the simulator class to decouple the GUI from the simulator itself. Looked a bit into analysis as well.
3. Jaakko implemented the car movement. Cars calculate shortest paths using Dijkstras algorithm. Added a visualization class to decouple the simulation and GUI.
4. Jiri improved the implementations of the TrafficLight and Intersection classes, and modified the City class according to the changes. Additionally, Jiri spent time on solving the configuration issues of the project.

## Challenges
1. The code finally compiled with modifications to the CMake configuration.
2. How to make cars not crash into each other, how to integrate traffic lights. 

## Actions
1. Artur is working on the Simulator class.
2. Aape is working on Building and Person profiles.
3. Jaakko is working on the the visualization class and how traffic lights and other cars affect car movement.
4. Jiri: Look into testing.

## Project status
## Deviations from the plan:
Created new Simulator & Visualization classes for the project to decouple the GUI and simulation.


## TODOs
1. Artur: Try to progress with the Simulator class as much as possible. Create the text interface for the user to enter commands to start/pause/stop/load the simulation. Finish the JSON file loading.
2. Aape: Modify City class function AddBuilding so it functions with building profiles. Figure out what a person does when it has no event on schedule and is in some building other than home.
3. Jaakko: Finish the visualization class, integrate traffic lights to the city and make cars move according to them. Also make cars avoid crashes.
4. Jiri: Implement some tests.
