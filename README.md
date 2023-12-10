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

The order of the elements must be similar to the one in the template. If the JSON file is invalid, the program will continue asking for a new file until the file is valid.

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
    ["name", "PersonType", workplace given in similar format as the buildings above, 
    home given in similar format as the buildings above]
  ],
  "trafficLights": [
    [[x-coordinate(int), y-coordinate(int)], red light duration(int),
    yellow light duration(int), green light duration(int)]
  ]
}
