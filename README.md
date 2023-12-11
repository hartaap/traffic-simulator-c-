# Traffic Simulator
The purpose of this program is to simulate and analyze the traffic of a city model inputted as a JSON file.

This document contains instructions on how to use the program.

# Group
- Artur Brander
- Aape Hartikainen
- Jaakko Karhu
- Jiri Simell

# Repository organization
Your project implementation should follow the skelaton organization in this repository.
See readme.md files in each folder.

# Instructions on how to use the program

**Dependencies**
The simulator might require some additional libraries that are required to be installed through terminal, so run these commands:
1. `sudo apt-get install libxrandr-dev libxcursor-dev libsfml-dev`

**Building and running the program**
  1. Clone `https://version.aalto.fi/gitlab/karhuj5/traffic-simulator-henrik-toikka-4.git`
  2. Create build directory in the project's root folder: `mkdir build`
  3. Navigate to the folder `cd build`
  4. Generate makefile with CMake: `cmake ..`
  5. Build the file in the same directory `make`
  6. Navigate to the root folder `cd ..`
  7. Run the file `build/./main`

**How to use the simulation:**
The si

# JSON file template for city loading
The city is loaded from a JSON file which should be located in the root folder of the project. A template for the JSON files is provided below. If the JSON file is invalid, the program will continue asking for a new file until the file is valid. The root folder of this project contains two example JSON files: city.json and smallcity.json.

Requirements:
- The order of the elements must be the same as in the template. 
- All the locations of the buildings, intersections, roads, and traffic lights must be inside city boundaries.
- The building type must be on of the following types: "Residential", "Industrial", "Gym", "Shop", or "Restaurant".
- The starting and ending points of roads must be either intersections or buildings.
- The PersonType parameter of person objects must be one of the following types: "Lazy", "Active", "Neutral", "Gentleman", or "Angry".
- The workplace of a person must be one of the Industrial buildings added to the city (i.e. the name of the workplace must be found in the added Industrial buildings' names)
- The home of a person must be one of the Residential buildings added to the city (i.e. the name of the home building must be found in the added Residential buildings' names)
- The traffic lights must have the same coordinates as one of the intersections.
- The objects must be placed in locations where there are no other objects (excluding traffic lights, which must be placed on top of intersections).

The template:
```json
{
  "x": vertical_city_size(int),
  "y": horizontal_city_size(int),
  "buildings": [
    {"name": ["building type", [x-coordinate(int), y-coordinate(int)]]}
  ],
  "intersections": [
    [x-coordinate(int), y-coordinate(int)]
  ],
  "roads": [
    [starting_x-coordinate(int), starting_y-coordinate(int), ending_x-coordinate(int), ending_y-coordinate(int)]
    ],
  "persons": [
    ["name", "PersonType", "name of workplace", "name of home building"]
  ],
  "trafficLights": [
    [[x-coordinate(int), y-coordinate(int)], red_light_duration(int), yellow_light_duration(int), green_light_duration(int)]
  ]
}
```
