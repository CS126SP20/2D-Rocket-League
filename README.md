# 2D Rocket League

**Author**: Tanay Abichandani

## What is 2D Rocket League?

<img src="https://github.com/CS126SP20/final-project-tanay2/blob/master/assets/game-view.jpg" width="300"> |

2D Rocket League is like a combination of the PC/Console game Rocket 
League and Head Soccer. It is a 2 player game with each player spawning 
on one side of the screen by their respective goals. Games are 90 seconds
long and from there its just like soccer with cars. You can move forward, back,
boost, jump and change direction in the air in order to hit the ball, which spawns in the middle,
into the goal. At the end of the time, either red/blue wins or it is a draw.

## Controls

#### Keyboard
Key | Action
------------ | -------------
a | Red car moves left if on ground or rotates left if in air
d | Red car moves right if on ground or rotates right if in air
w | Red car jumps up and can double jump while in air
s | Red car boosts while on ground and dodges forward if in air
left | Blue car moves left if on ground or rotates left if in air
right | Blue car moves right if on ground or rotates right if in air
up | Blue car jumps up and can double jump while in air
down | Blue car boosts while on ground and dodges forward if in air

## How to build and play 2D Rocket League

To play this game, you will need CLion, Cinder and Box2D. First, you will need
to get JetBrains C++ IDE: CLion. If you do not already have it,
you can get it at this link, https://www.jetbrains.com/clion/. You will
also need to download Cinder which is available at this link, https://libcinder.org/download.
Once you have Cinder, you must build the Cinder library. To do this, first, 
take the download Cinder file and open it in CLion. Then click the build button
near the top of the screen that looks like a hammer. It may take a while,
but it will build the library. It may also already contain Box2D in the /blocks directory.
If it does not, you can get Box2D at this link, https://github.com/cinder/Cinder/tree/master/blocks/Box2D.
You can clone this directory straight into /blocks in Cinder. Now, you must create a director
in Cinder for your projects. Once you have that directory, you can clone this
project into that directory. Finally, you can run and play the game!
