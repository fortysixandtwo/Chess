# SDL-Chess
<br>
## Chess Game written in C++ with SDL.


### DISCLAIMER:

Development continues on [GitLab](https://gitlab.com/fortysixandtwo/SDL-Chess) <br>
At the time of this writing I haven't bothered
tidying everything into a releasable state.

### Beware: Some functions were found on SO, Tutorial pages and the like.
I should have annotated this where applicable, but may have forgotten
to give you credit.
In this case please contact me and I will rectify the situation :)

For now I just want to use git for cvs.

I continue working on this and i will be updating
this repository somewhat regularly and try to only
update the master branch with somewhat working code :D.

I view this as a project to learn more about cmake, git, SDL and C++ in general.
If you find anything useful, that is nice.
If not, that's okay too.

This is the biggest solo project I've worked on so far.
Basically I want to have this for use on my Raspberry Pi with the
official 7" LCD.
I want to learn about machine learning and neural networks
to create a chess AI (this is somewhat the endgoal to this project).
I hope to learn something about GPU programming along the way.

### About the targets
Chess is the main executable which will have server/client baked into it.
ChessServ and ChessClient are headless servers/clients which I just use
to test stuff.


### WHAT WORKS SO FAR:
UI Rendering to a certain degree. <br>
Server/Client

### WHAT DOES NOT:
Everything else (actually playing the game)

### REQUIREMENTS:
SDL2 <br>
SDL2_net <br>
SDL2_image <br>
SDL2_ttf <br>


### BUILDING:
For a clean building environment I suggest to <br>

$ mkdir build && cd build <br>
$ cmake .. <br>
$ make && make install <br>

### This is what it looks like
![Multiplayer action!](https://fortysixandtwo.github.io/img/chess_promo.png)


