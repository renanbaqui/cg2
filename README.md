# Computer Graphics University Project - 3D Penguin Game [![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0) [![Windows](https://badgen.net/badge/icon/windows?icon=windows&label)](https://www.microsoft.com/en-us/windows)

## Project Requirements

- The project should be implemented using the OpenGL API, and the libraries gl, glu, glut the only ones that can be used
- Only two programming languages allowed: C e C++
- The penguins (father and son) must be over an ice sheet
- The son penguin will remaing still in the center of the ice sheet and the father will look for fishes that will appear randomly over the ice
- In order to capture a fish the penguin must collide with it. To represent a penguin that has already catched a fish, the fish should be drawn stuck to the penguin's beek
- After having a fish in its beek, the penguin can't capture anymore fish, until it delivers to his son
- The father penguin must take care to not fall on the holes that randomly appear on the ice sheet
- Food gives energy to the son penguin so that it can survive for 1 minute. After that the penguin dies and the game ends
- To feed his son, the penguim should only get close to it while carrying a fish. After this movement the fish disappears from the penguin's mouth
- The game must last at maximum 5 minutes. If the son penguim remains alive within this time, the player wins the game.
- Bonus points: During its movement the father penguin should flap its wings

### Other Requirements
1. The penguins and fish must be modeled using spheres, ellipsoids and cones.
2. Allow that, when using the arrow keys, the father penguin moves accordingly. When pressing the up and down keys, the penguin must move forward or backward, following the axis that it is directed. However when pressing left and right keys, the penguin should rotate around its own axis. Bonus question: When moving the penguin should flap its wings forward and backward, simulating its stroll.
3. Implement the appearance of random holes in the way of the penguin under the ice.
4. Implement four visualization windows of the scence, defining four different viewpoints, obeying the following restrictions:
- At least one window that the camera is positioned above the scence, in the Y axis.
- At least one window that the camera is positioned besides the scence, in the X axis.
- At least one window that the camera is positioned in front of the scence, in the Z axis.
- At least one window that the camera is positioned on a free position, for example in the coordinates (3.0, 2.0, 10.0).
5. Manipulate the gluLookAt(...) funcion in a way that it always keeps the father penguin at the center of the visible area of the scence. That means that the camera must have the penguin as its central focus, in all the windows of the program.
6. Add three textures on the scene, giving a larger degree of realism to the characters (penguins and fishes), ice sheet, holes and background.
- The choice of images that are going to be used as textures is free.

> Made using Eclipse IDE, OpenGL and GLUT

Game Screenshot:

![Screen](https://github.com/renanbaqui/cg2/blob/main/CG2.jpeg)
