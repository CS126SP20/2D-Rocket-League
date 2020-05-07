# Development

- **4/20/20** Both external libraries added
  - Cloned project into cinder/my-projects
  - Added Box2D in final-project/app/CMakeLists.txt in my-app
  
- **4/21/20** Generated Box2D world with basic borders
  - Added Box2D into src CMake file as well
  - Generated a static body rectangle border representing the
    game ceiling, walls and ground
  - Using cinder::gl, drew a ground box and ceiling box,
  along with an imported soccer background for the app
  - Created the ball as a dyanamic body that responds to gravity
  in the Box2D world and drew a circle based off its position in the app

-  **4/27/20** Added in full graphics for game and fixed bugs
   - Fixed bug where image would not render properly
   - Figured out how to render images perfectly use rectf in cinder
- **4/28/20** Fixed ball bouncing off all walls including ground
   - Figured out a way to make ball bounce off ground by reversing velocity
   - Added 0.6f bounce factor to control how bouncy the ball is
   - All game now needs is to add in 2 cars with scoreboard logic
- **5/04/20** Added friction and fixed wall glitches in game
   - Figured out how to add friction on ground, so ball stops rolling
   - Ball no longer falls through ground and fixed bug where ball glitches through wall
- **5/05/20** Added in all car logic and gameplay
   - Created red car and blue car in box2d world using a special polygon with 5 vertecies
   - Implemented graphics of car using car image in real Cinder game world
   - Added in ability to move forward and backwards for both cars using linear velocity
   - Added in ability to rotate car and added in graphics to correspond to that rotation
- **5/06/20** Added in boosting feature and game engine with scoreboard
   - Car can now dodge in certain direction in air and boost on the ground
   - Fixed rotation glitch and fixed jumping bugs with lots of small constants tweaking
   - Added in scoreboard with tracking of when each player scores in goal
   - Added in crossbar to block high shots like in normal rocket league
   - Added in game engine logic with timer so that end of the game displays who wins

### To-Do

- [x] Fix background bug where image does not fix constraint
- [x] Fix background glitch near screen bottom
- [x] Fix ball not bouncing off ground like it should
- [x] Fix ground being hardcoded as a stop to gravity
- [ ] Refactor code so not everything is in my-app
- [x] Add in 2 cars with key responses so they can move
- [x] Configure game sensors so when ball goes in goal score is recorded
- [ ] Make code efficient for memory/runtime
---
