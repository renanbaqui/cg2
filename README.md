# Computer Graphics University Project - 3D Penguin Game [![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0) [![Terminal](https://badgen.net/badge/icon/terminal?icon=terminal&label)](https://www.microsoft.com/en-us/windows)

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
1. Implemente dois atores que tenham a forma de pinguins. Modele o pinguim utilizando esferas, elipsóides e cones.
Alguns exemplos são apresentados a seguir.
2. Modele os peixes que irão aparecer (aleatoriamente) sob o gelo utilizando elipsóides e cones.
3. Permita que, ao utilizar as setas do teclado, o pinguim pai se movimente de maneira correspondente. No caso das
setas para cima e para baixo, o pinguim deve se deslocar ou para frente ou para trás, seguindo o eixo que ela está
direcionada. Já com as setas da esquerda e da direita, o pinguim deve rotacionar em torno do seu próprio eixo.
Questão bônus - Durante o seu deslocamento o pinguim deve movimentar as asas para frente e para trás, simulando o
andar.
4. Implemente o aparecimento aleatório de buracos no caminho do pinguim sob o gelo.
5. Implemente quatro janelas para visualização da cena, definindo quatro viewports distintos, obedecendo `às seguintes
restrições:
• Deve haver pelo menos uma janela em que a câmera está “posicionada” acima da cena, no eixo Y;
• Deve haver pelo menos uma janela em que a câmera está “posicionada” do lado da cena, no eixo X;
• Deve haver pelo menos uma janela em que a câmera está “posicionada” de frente para a cena, no eixo Z;
• Deve haver pelo menos uma janela em que a câmera está “posicionada” em uma posição livre, como por
exemplo nas coordenadas (3.0, 2.0, 10.0).
4. Manipule a função gluLookAt(...) de maneira a sempre manter o pinguim pai no centro da porção visível da cena. Isso
significa que a câmera deve ter como ponto focal central a aranha, em todas as janelas do programa.
6. Insira três texturas na cena, dando um maior grau de realismo nos personagens (pinguins e peixes), placa de gelo e
buracos e ao redor da cena.
• A escolha das imagens que serão utilizadas como texturas é livre.

> Made using Eclipse IDE, OpenGL and GLUT

Game Screenshot:

![Screen](https://github.com/renanbaqui/cg2/blob/main/CG2.jpeg)
