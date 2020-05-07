// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <cinder/Rand.h>

#include <mylibrary/example.h>
#include "Box2D/Box2D.h"

using namespace mylibrary;

/**
 * Note: This is the only thing I can really test with this project.
 * The rest is represented graphically and is in the box2d world, which cannot
 * be initiated here as we lack access to myApp
 */

TEST_CASE("Checking if goal is properly recorded", "[random]") {
  b2Vec2 ball_position;

  SECTION("Goals for Red Team") {
    // Should be a goal for red and not blue
    ball_position.Set(120, 0);
    REQUIRE(mylibrary::CheckGoalScored(ball_position, false));
    REQUIRE_FALSE(mylibrary::CheckGoalScored(ball_position, true));

    // Never a goal
    ball_position.Set(50, 30);
    REQUIRE_FALSE(mylibrary::CheckGoalScored(ball_position, false));
  }

  SECTION("Goals for Blue Team") {
    // Should be a goal for red and not blue
    ball_position.Set(0, 0);
    REQUIRE(mylibrary::CheckGoalScored(ball_position, true));
    REQUIRE_FALSE(mylibrary::CheckGoalScored(ball_position, false));

    // Never a goal
    ball_position.Set(50, 30);
    REQUIRE_FALSE(mylibrary::CheckGoalScored(ball_position, true));
  }
}