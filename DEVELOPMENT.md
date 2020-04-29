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

### To-Do

- [x] Fix background bug where image does not fix constraint
- [x] Fix background glitch near screen bottom
- [x] Fix ball not bouncing off ground like it should
- [ ] Fix ground being hardcoded as a stop to gravity
- [ ] Refactor code so not everything is in my-app
- [ ] Add in 2 cars with key responses so they can move
- [ ] Configure game sensors so when ball goes in goal score is recorded
---
