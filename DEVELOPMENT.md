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

### To-Do

- [x] Fix background bug where image does not fix constraint
- [ ] Fix background glitch near screen bottom
- [ ] Fix ball not bouncing off ground like it should
- [ ] Fix ground being hardcoded as a stop to gravity
- [ ] Refactor code so not everything is in my-app
---
