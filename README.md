# Traffic Simulator
This is the template for the projects. Please copy the project description here. 
You can use Markdown language to render it as formatted **HTML** file.

# Group
- Artur Brander
- Aape Hartikainen
- Jaakko Karhu
- Jiri Simell

# Repository organization
Your project implementation should follow the skelaton organization in this repository.
See readme.md files in each folder.

# Instructions on how to use the program
Add instructions


# JSON file template for city loading
The city in the program is loaded from a JSON file which should be located in the root folder of the project. A template for these JSON files is provided below. 

Requirements:
- The order of the elements must be similar to the one in the template. If the JSON file is invalid, the program will continue asking for a new file until the file is valid.
- The PersonType parameter of persons must be one of the following types: "Lazy", "Active", "Neutral", "Gentleman", or "Angry".
- The building type must be "Residential", "Industrial", "Gym", "Shop", or "Restaurant".
- The home of a person must be one of the Residential buildings added to the city (i.e. the name of the home building must be found in the added Residential buildings' names)
- The workplace of a person must be one of the Industrial buildings added to the city (i.e. the name of the workplace must be found in the added Industrial buildings' names)

```json
{
  "x": vertical city size(int),
  "y": horizontal city size(int),
  "buildings": [
    {"name": ["building type", [x-coordinate(int),
    y-coordinate(int)]]}
  ],
  "intersections": [
    [x-coordinate(int), y-coordinate(int)]
  ],
  "roads": [
    [starting x-coordinate(int), starting y-coordinate(int), ending
    x-coordinate(int), ending y-coordinate(int)]
    ],
  "persons": [
    ["name", "PersonType", "name of workplace", "name of home building"]
  ],
  "trafficLights": [
    [[x-coordinate(int), y-coordinate(int)], red light duration(int),
    yellow light duration(int), green light duration(int)]
  ]
}
```