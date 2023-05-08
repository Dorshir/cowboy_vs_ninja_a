#include "doctest.h"
#include <limits>
#include <cmath>
#include "sources/Team.hpp"

TEST_CASE("Point") {

    SUBCASE("Constructor") {

        SUBCASE("Integer initialize") {

            int x = 10, y = 20;
            CHECK_NOTHROW(Point(x, y)); // Cast from integer to double should work fine

            double expectedX = 10.0, expectedY = 20.0;
            Point p(x, y);
            CHECK_EQ(expectedX, p.getX());
            CHECK_EQ(expectedY, p.getY());
        }

        SUBCASE("Max/min double values initialize") {

            double x = numeric_limits<double>::max();
            double y = numeric_limits<double>::min();
            CHECK_NOTHROW(Point(x, y));
        }
    }

    SUBCASE("Distance") {

        SUBCASE("Similar/unsimilar point values") {

            Point p1(1.0, 2.0);
            Point p2(4.0, 6.0);

            double expectedDistance = sqrt(pow(p2.getX() - p1.getX(), 2) + pow(p2.getY() - p1.getY(), 2));
            double calculatedDistance = p1.distance(p2);

            CHECK_EQ(expectedDistance, calculatedDistance);


            Point p3(5.33, 9.5);
            Point p4(5.33, 9.5);

            expectedDistance = 0.0;
            calculatedDistance = p3.distance(p4);

            CHECK_EQ(expectedDistance, calculatedDistance);
        }

        SUBCASE("Max/min double values handling - overflow") {

            Point p5(numeric_limits<double>::max(), numeric_limits<double>::max());
            Point p6(numeric_limits<double>::min(), numeric_limits<double>::min());

            double expectedDistance = -1.0;
            double calculatedDistance = p5.distance(p6);

            CHECK_EQ(expectedDistance, calculatedDistance); // Special case - cannot calculate, -1.0 indicator
        }
    }

    SUBCASE("moveTowards") {

        SUBCASE("Same position and distance > 0") {

            Point p1(2.3, 3.3);
            Point p2(2.3, 3.3);

            Point s = Point::moveTowards(p1, p2, 5.0);
            CHECK_EQ(s.getX(), p1.getX());
            CHECK_EQ(s.getY(), p2.getY());
        }

        SUBCASE("Source and destination points that are already within the given distance") {

            Point p1(1.0, 1.0);
            Point p2(2.0, 2.0);

            Point s = Point::moveTowards(p1, p2, 2.0);
            CHECK_EQ(s.getX(), p2.getX());
            CHECK_EQ(s.getY(), p2.getY());
        }

        SUBCASE("Source and destination point that are further apart than the given distance") {

            Point p1(1.0, 1.0);
            Point p2(6.0, 6.0);

            Point s = Point::moveTowards(p1, p2, 3.0);

            CHECK_LE(s.distance(p1), 3.0); // Point s is within distance of 3.0 or less from point p1
            CHECK_LT(s.distance(p2), p1.distance(p2)); // Point s is closer to p2 than point p1 close to p2
        }

        SUBCASE("Source and destination point that are further apart than the given distance, negative coordinates") {

            Point p1(-1.0, -1.0);
            Point p2(-5.0, -5.0);

            Point s = Point::moveTowards(p1, p2, 3.0);

            CHECK_LE(s.distance(p1), 3.0); // Point s is within distance of 3.0 or less from point p1
            CHECK_LT(s.distance(p2), p1.distance(p2)); // Point s is closer to p2 than point p1 close to p2
        }

        SUBCASE("Horizontal/vertical movement") {

            Point p1(0.0, 0.0);
            Point p2(10.0, 0.0);
            Point p3(0.0, 10.0);

            Point s1 = Point::moveTowards(p1, p2, 5.0);
            Point s2 = Point::moveTowards(p1, p3, 7.0);

            CHECK_EQ(s1.getY(), 0.0);
            CHECK_EQ(s2.getX(), 0.0);
            CHECK_LE(s1.distance(p1), 5.0); // Point s1 is within distance of 5.0 or less from point p1
            CHECK_LT(s1.distance(p2), p1.distance(p2)); // Point s1 is closer to p2 than point p1 close to p2

            CHECK_LE(s2.distance(p1), 7.0); // Point s2 is within distance of 5.0 or less from point p1
            CHECK_LT(s2.distance(p3), p1.distance(p3)); // Point s2 is closer to p3 than point p1 close to p3

        }


    }

    SUBCASE("Print") {

        SUBCASE("Regular expression") {

            Point p(2.5, 3.5);

            // Redirect output stream
            std::ostringstream oss;
            std::streambuf *oldCoutBuffer = std::cout.rdbuf();
            std::cout.rdbuf(oss.rdbuf());
            p.print();

            // Restore output stream
            std::cout.rdbuf(oldCoutBuffer);

            std::string output = oss.str();
            const string expectedOutput = "(2.5,3.5)";
            CHECK_EQ(output, expectedOutput);
        }

        SUBCASE("Small values") {

            Point p(0.000001, 0.000000001);

            // Redirect output stream
            std::ostringstream oss;
            std::streambuf *oldCoutBuffer = std::cout.rdbuf();
            std::cout.rdbuf(oss.rdbuf());
            p.print();

            // Restore output stream
            std::cout.rdbuf(oldCoutBuffer);

            std::string output = oss.str();
            const string expectedOutput = "(0.000001,0.000000001)";
            CHECK_EQ(output, expectedOutput);
        }

        SUBCASE("Negative values") {

            Point p(-2.7, -3.3);

            // Redirect output stream
            std::ostringstream oss;
            std::streambuf *oldCoutBuffer = std::cout.rdbuf();
            std::cout.rdbuf(oss.rdbuf());
            p.print();

            // Restore output stream
            std::cout.rdbuf(oldCoutBuffer);

            std::string output = oss.str();
            const string expectedOutput = "(-2.7,-3.3)";
            CHECK_EQ(output, expectedOutput);
        }
    }

}

TEST_CASE("Character") {

    SUBCASE("Abstract cases") {

        SUBCASE("isAlive") {

            SUBCASE("Alive") {

                Point p(0.0, 0.0);

                Cowboy c("Johnny", p);
                OldNinja n1("Nebuchadnezzar", p);
                TrainedNinja n2("David", p);
                YoungNinja n3("Shlomo", p);

                CHECK(c.isAlive()); // Cowboy initialized with 110 hitpoints, hence should be alive
                CHECK(n1.isAlive()); // OldNinja initialized with 150 hitpoints, hence should be alive
                CHECK(n2.isAlive()); // TrainedNinja initialized with 120 hitpoints, hence should be alive
                CHECK(n3.isAlive()); // YoungNinja initialized with 100 hitpoints, hence should be alive

                // Should act as any other character
                c.hit(105);
                n1.hit(33);
                n2.hit(55);
                n3.hit(1);
                CHECK(c.isAlive());
                CHECK(n1.isAlive());
                CHECK(n2.isAlive());
                CHECK(n3.isAlive());
            }

            SUBCASE("Not alive") {

                Point p(5.0, 5.0);

                Cowboy c("Johnny", p);
                OldNinja n1("Nebuchadnezzar", p);
                TrainedNinja n2("David", p);
                YoungNinja n3("Shlomo", p);

                // Should act as any other character
                c.hit(110); // -> hitpoints == 0
                n1.hit(200); // -> hitpoints == -50
                n2.hit(120); // -> hitpoints == 0
                n3.hit(150); // -> hitpoints == -50
                CHECK_FALSE(c.isAlive());
                CHECK_FALSE(n1.isAlive());
                CHECK_FALSE(n2.isAlive());
                CHECK_FALSE(n3.isAlive());
            }

        }

        SUBCASE("Distance") {

            SUBCASE("Characters at the same location") {

                Point p1(1.0, 1.0);


                double expectedDistance = 0.0;
                Cowboy c("Johnny", p1);
                OldNinja n1("Nebuchadnezzar", p1);
                CHECK_EQ(expectedDistance, c.distance(&n1));
            }

            SUBCASE("Characters at different locations") {

                Point p1(1.0, 1.0);
                Point p2(2.5, 3.5);
                TrainedNinja n2("David", p1);
                YoungNinja n3("Shlomo", p2);

                double expectedDistance = sqrt(pow(p2.getX() - p1.getX(), 2) + pow(p2.getY() - p1.getY(), 2));
                CHECK_EQ(expectedDistance, n2.distance(&n3));
            }

            SUBCASE("Negative location") {

                Point p1(1.0, 1.0);
                Point p2(-2.0, -3.0);
                Cowboy c("Johnny", p1);
                YoungNinja n3("Shlomo", p2);

                double expectedDistance = sqrt(pow(p2.getX() - p1.getX(), 2) + pow(p2.getY() - p1.getY(), 2));
                CHECK_EQ(expectedDistance, c.distance(&n3));
            }

            SUBCASE("Max/min double value locations - overflow") {

                Point p1(numeric_limits<double>::max(), numeric_limits<double>::max());
                Point p2(numeric_limits<double>::min(), numeric_limits<double>::min());
                TrainedNinja n2("David", p1);
                YoungNinja n3("Shlomo", p2);

                double expectedDistance = -1.0;
                CHECK_EQ(expectedDistance, n2.distance(&n3)); // Special case - cannot calculate, -1.0 indicator
            }


        }

        SUBCASE("Hit") {

            SUBCASE("Can hit") {

                Point p(1.0, 2.0);
                Cowboy c("Johnny", p);
                OldNinja n1("Nebuchadnezzar", p);
                TrainedNinja n2("David", p);

                CHECK_NOTHROW(c.hit(110)); // hitpoints -> -50

                CHECK_NOTHROW(n1.hit(200)); // hitpoints -> -50

                while (n2.isAlive()) { // Reduce n2 hitpoints to 0
                    n2.hit(1);
                }
                CHECK_FALSE(n2.isAlive());
            }

            SUBCASE("Cannot hit") {

                Point p(1.0, 2.0);
                Cowboy c("Johnny", p);
                OldNinja n1("Nebuchadnezzar", p);
                TrainedNinja n2("David", p);
                YoungNinja n3("Shlomo", p);

                c.hit(110); // hitpoints -> 0
                CHECK_THROWS(c.hit(2));

                n1.hit(200); // hitpoints -> -50
                CHECK_THROWS(n1.hit(2));

                while (n2.isAlive()) { // Reduce n2 hitpoints to 0
                    n2.hit(1);
                }
                CHECK_THROWS(n2.hit(1));

                CHECK_THROWS(n3.hit(-50)); // Negative int
            }


        }

        SUBCASE("Print") {

            SUBCASE("Alive character") {

                Point p(10.5, 7.2);
                OldNinja n("Ninja", p);

                string output = n.print();

                bool containsName = output.find(n.getName()) != std::string::npos;
                bool containsHitpoints =
                        output.find("150") != std::string::npos; // 150 for OldNinja initialized hitpoints
                bool containsLocation = output.find("(10.5,7.2)") != std::string::npos;
                CHECK(containsName);
                CHECK(containsHitpoints);
                CHECK(containsLocation);
            }

            SUBCASE("Dead character") {

                Point p(10.5, 7.2);
                Cowboy c("Cowboy", p);

                c.hit(200);
                string output = c.print();

                bool containsName = output.find("(Cowboy)") != std::string::npos;
                bool containsHitpoints = output.find("-90") ==
                                         std::string::npos; // -50 for Cowboy initialized hitpoints(110) - hit of 200 points

                CHECK(containsName); // Form of (Name)
                CHECK(containsHitpoints); // Should not be found since dead characters doesnt print hitpoints
            }
        }

    }

    SUBCASE("Specific cases") {

        SUBCASE("Cowboy") {

            SUBCASE("Constructor") {

                Point p(1.0, 2.0);

                Cowboy c1("Johnny", p);
                Cowboy c2("George", p);

                CHECK(c1.isAlive());
                CHECK(c1.hasboolets()); // Construct with positive number of bullets
                for (int i = 0; i < 5; ++i) {
                    c1.shoot(&c2);
                }
                CHECK_FALSE(c1.hasboolets()); // Check correctness of init with exactly 6 bullets

                CHECK_NOTHROW(c1.hit(110)); // Construct a Cowboy with 110 hitpoints
                CHECK_THROWS(c1.hit(2));
            }

            SUBCASE("Shoot") {

                Point p(3.0, 2.0);

                Cowboy c("Johnny", p);
                Cowboy enemy("Jaffer", p);

                int bulletCounter = 1;
                while (enemy.isAlive() || c.hasboolets()) { // enemy hitpoints 110 -> 50
                    c.shoot(&enemy);
                    bulletCounter++;
                }
                CHECK_EQ(bulletCounter, 6); // Cowboy c should empty his stack of 6 bullets since enemy is not dead

                enemy.hit(40); // Reduce enemy's hitpoints to 10(Damage of 1 bullet)
                c.shoot(&enemy);
                CHECK(enemy.isAlive()); // No bullets left for the c cowboy, therefor no damage to the enemy and still alive
                c.reload(); // Reload the pistol with 6 new bullets
                c.shoot(&enemy); // Should be able to shoot the enemy now, has bullets and enemy is alive
                CHECK_FALSE(enemy.isAlive()); // enemy hitpoints 10 -> 0
                CHECK_THROWS(c.shoot(&enemy)); // enemy is dead already
                CHECK_THROWS(enemy.shoot(&c)); // enemy is dead, he cannot shoot anyone
                CHECK_THROWS(c.shoot(&c)); // Shoot himself
            }

            SUBCASE("hasBullets") {

                Point p(3.0, 2.0);

                Cowboy c("Johnny", p);
                Cowboy enemy("Jaffer", p);

                CHECK(c.hasboolets()); // A cowboy should start with 6 bullets

                int bulletCounter = 1;
                while (c.hasboolets()) {
                    c.shoot(&enemy);
                    bulletCounter++;
                }
                CHECK_EQ(bulletCounter, 6); // Indeed 6 bullets were shoot
                CHECK_FALSE(c.hasboolets()); // 0 bullets left after shooting 6 of them without reloading
                c.reload();
                CHECK(c.hasboolets());
            }

            SUBCASE("Reload") {

                Point p(5.5, 5.5);

                Cowboy c("Hamudi", p);
                Cowboy enemy("Jaffer", p);

                while (c.hasboolets()) {
                    c.shoot(&enemy);
                }
                CHECK_FALSE(c.hasboolets());
                c.reload();
                CHECK(c.hasboolets()); // After a reload

                enemy.hit(50); // Enemy hitpoints 50 -> 0
                CHECK(enemy.isAlive()); // Confirm enemy is indeed dead
                CHECK_THROWS(enemy.reload()); // Reload within a dead character should raise an exception
            }

        }

        SUBCASE("YoungNinja") {

            SUBCASE("Constructor") {

                Point p(1.0, 2.0);

                YoungNinja n1("Johnny", p);

                CHECK(n1.isAlive());

                CHECK_NOTHROW(n1.hit(100)); // Construct a YoungNinja with 100 hitpoints
                CHECK_THROWS(n1.hit(2));
            }

            SUBCASE("Move") {

                SUBCASE("Same location") {

                    Point p1(1.1, 2.2);
                    YoungNinja n("Yaakov", p1);
                    Cowboy enemy1("Bob", p1);

                    n.move(&enemy1); // Same position situation, no movement
                    CHECK_EQ(p1.getX(), n.getLocation().getX());
                    CHECK_EQ(p1.getY(), n.getLocation().getY());
                }

                SUBCASE("Far location") {

                    Point p1(1.1, 2.2);
                    Point p2(100.0, 100.0);
                    YoungNinja n("Yaakov", p1);
                    Cowboy enemy("Alice", p2);

                    double expectedDistance = sqrt(pow(p2.getX() - p1.getX(), 2) + pow(p2.getY() - p1.getY(), 2)) - 14;
                    n.move(&enemy); // YoungNinja should move in speed of 14
                    CHECK_EQ(expectedDistance, n.distance(&enemy));
                }

                SUBCASE("Location is closer than the speed of the ninja") {

                    Point p1(1.1, 2.2);
                    Point p2(5.0, 5.0);
                    YoungNinja n("Yaakov", p1);
                    Cowboy enemy("Alice", p2);

                    n.move(&enemy); // Should move to the destination and not farther
                    CHECK_EQ(p2.getX(), n.getLocation().getX());
                    CHECK_EQ(p2.getY(), n.getLocation().getY());
                }

                SUBCASE("Dead ninja/enemy") {

                    Point p1(1.1, 2.2);
                    Point p2(5.0, 5.0);
                    YoungNinja n("Yaakov", p1);
                    YoungNinja enemy("Alice", p2);

                    enemy.hit(200);
                    CHECK_FALSE(enemy.isAlive()); // Confirm the enemy is dead
                    CHECK_THROWS(n.move(&enemy)); // Trying to move to a dead enemy
                    CHECK_THROWS(enemy.move(&n)); // Trying to call move() from a dead ninja

                }

                SUBCASE("Move with the same ninja") {

                    Point p1(1.1, 2.2);
                    YoungNinja n("Yaakov", p1);

                    CHECK_THROWS(n.move(&n));
                }

            }

            SUBCASE("Slash") {

                SUBCASE("The Ninja and the enemy are alive and within range to slash the enemy") {

                    Point p1(1.1, 2.2);
                    YoungNinja n("Yaakov", p1);
                    Cowboy enemy("Bob", p1);

                    enemy.hit(87); // Enemy hitpoints 100 -> 13
                    CHECK(enemy.isAlive()); // Confirm enemy is alive
                    n.slash(&enemy);
                    CHECK_FALSE(enemy.isAlive()); // Enemy should be dead after slashing 13 hitpoints

                }

                SUBCASE("The Ninja and the enemy are alive but the ninja is too far to slash the enemy") {

                    Point p1(1.1, 2.2);
                    Point p2(50.0, 50.0);
                    YoungNinja n("Yaakov", p1);
                    Cowboy enemy("Alice", p2);

                    enemy.hit(90); // Enemy hitpoints 100 -> 10
                    CHECK(enemy.isAlive()); // Confirm enemy is alive
                    n.slash(&enemy);
                    CHECK(enemy.isAlive()); // Enemy should remain alive since the ninja is too far
                }

                SUBCASE("Ninja/enemy is dead") {

                    Point p1(1.1, 2.2);
                    YoungNinja n("Yaakov", p1);
                    YoungNinja enemy("Alice", p1);

                    enemy.hit(199); // Enemy hitpoints 100 -> -99
                    CHECK_FALSE(enemy.isAlive()); // Confirm enemy is dead
                    n.slash(&enemy); // Enemy is already dead

                    string output = enemy.print();

                    bool containsRemainedHP = output.find("-99") != std::string::npos;
                    CHECK(containsRemainedHP); // Search for "-99" as the hitpoints value, since slashing a dead enemy remain his hitpoints as it was before
                    CHECK_THROWS(enemy.slash(&n)); // Enemy ninja is dead already, should not be able to slash anyone

                }

            }

        }

        SUBCASE("TrainedNinja") {

            SUBCASE("Constructor") {

                Point p(1.0, 2.0);

                TrainedNinja n1("George", p);

                CHECK(n1.isAlive());

                CHECK_NOTHROW(n1.hit(120)); // Construct a YoungNinja with 120 hitpoints
                CHECK_THROWS(n1.hit(2));
            }

            SUBCASE("Move") {

                SUBCASE("Same location") {

                    Point p1(1.1, 2.2);
                    TrainedNinja n("Hezi", p1);
                    Cowboy enemy1("Bob", p1);

                    n.move(&enemy1); // Same position situation, no movement
                    CHECK_EQ(p1.getX(), n.getLocation().getX());
                    CHECK_EQ(p1.getY(), n.getLocation().getY());
                }

                SUBCASE("Far location") {

                    Point p1(1.1, 2.2);
                    Point p2(100.0, 100.0);
                    TrainedNinja n("Hezi", p1);
                    Cowboy enemy("Alice", p2);

                    double expectedDistance =
                            sqrt(pow(p2.getX() - p1.getX(), 2) + pow(p2.getY() - p1.getY(), 2)) - 12;
                    n.move(&enemy); // TrainedNinja should move in speed of 12
                    CHECK_EQ(expectedDistance, n.distance(&enemy));
                }

                SUBCASE("Location is closer than the speed of the ninja") {

                    Point p1(1.1, 2.2);
                    Point p2(5.0, 5.0);
                    TrainedNinja n("Hezi", p1);
                    Cowboy enemy("Alice", p2);

                    n.move(&enemy); // Should move to the destination and not farther
                    CHECK_EQ(p2.getX(), n.getLocation().getX());
                    CHECK_EQ(p2.getY(), n.getLocation().getY());
                }

                SUBCASE("Dead ninja/enemy") {

                    Point p1(1.1, 2.2);
                    Point p2(5.0, 5.0);
                    TrainedNinja n("Hezi", p1);
                    TrainedNinja enemy("Alice", p2);

                    enemy.hit(200);
                    CHECK_FALSE(enemy.isAlive()); // Confirm the enemy is dead
                    CHECK_THROWS(n.move(&enemy)); // Trying to move to a dead enemy
                    CHECK_THROWS(enemy.move(&n)); // Trying to call move() from a dead ninja

                }

                SUBCASE("Move with the same ninja") {

                    Point p1(1.1, 2.2);
                    TrainedNinja n("Hezi", p1);

                    CHECK_THROWS(n.move(&n));
                }

            }

            SUBCASE("Slash") {

                SUBCASE("The Ninja and the enemy are alive and within range to slash the enemy") {

                    Point p1(1.1, 2.2);
                    TrainedNinja n("Yaakov", p1);
                    Cowboy enemy("Bob", p1);

                    enemy.hit(107); // Enemy hitpoints 120 -> 13
                    CHECK(enemy.isAlive()); // Confirm enemy is alive
                    n.slash(&enemy);
                    CHECK_FALSE(enemy.isAlive()); // Enemy should be dead after slashing 13 hitpoints

                }

                SUBCASE("The Ninja and the enemy are alive but the ninja is too far to slash the enemy") {

                    Point p1(1.1, 2.2);
                    Point p2(50.0, 50.0);
                    TrainedNinja n("Yaakov", p1);
                    Cowboy enemy("Alice", p2);

                    enemy.hit(110); // Enemy hitpoints 120 -> 10
                    CHECK(enemy.isAlive()); // Confirm enemy is alive
                    n.slash(&enemy);
                    CHECK(enemy.isAlive()); // Enemy should remain alive since the ninja is too far
                }

                SUBCASE("Ninja/enemy is dead") {

                    Point p1(1.1, 2.2);
                    YoungNinja n("Yaakov", p1);
                    YoungNinja enemy("Alice", p1);

                    enemy.hit(219); // Enemy hitpoints 120 -> -99
                    CHECK_FALSE(enemy.isAlive()); // Confirm enemy is dead
                    n.slash(&enemy); // Enemy is already dead

                    string output = enemy.print();

                    bool containsRemainedHP = output.find("-99") != std::string::npos;
                    CHECK(containsRemainedHP); // Search for "-99" as the hitpoints value, since slashing a dead enemy remain his hitpoints as it was before
                    CHECK_THROWS(enemy.slash(&n)); // Enemy ninja is dead already, should not be able to slash anyone

                }

            }

        }

        SUBCASE("OldNinja") {

            SUBCASE("Constructor") {

                Point p(1.0, 2.0);

                OldNinja n1("Master Splinter", p);

                CHECK(n1.isAlive());

                CHECK_NOTHROW(n1.hit(150)); // Construct an OldNinja with 150 hitpoints
                CHECK_THROWS(n1.hit(2));
            }

            SUBCASE("Move") {

                SUBCASE("Same location") {

                    Point p1(1.1, 2.2);
                    OldNinja n("Master Splinter", p1);
                    Cowboy enemy1("Bob", p1);

                    n.move(&enemy1); // Same position situation, no movement
                    CHECK_EQ(p1.getX(), n.getLocation().getX());
                    CHECK_EQ(p1.getY(), n.getLocation().getY());
                }

                SUBCASE("Far location") {

                    Point p1(1.1, 2.2);
                    Point p2(100.0, 100.0);
                    OldNinja n("Master Splinter", p1);
                    Cowboy enemy("Alice", p2);

                    double expectedDistance =
                            sqrt(pow(p2.getX() - p1.getX(), 2) + pow(p2.getY() - p1.getY(), 2)) - 8;
                    n.move(&enemy); // OldNinja should move in speed of 8
                    CHECK_EQ(expectedDistance, n.distance(&enemy));
                }

                SUBCASE("Location is closer than the speed of the ninja") {

                    Point p1(1.1, 2.2);
                    Point p2(5.0, 5.0);
                    OldNinja n("Master Splinter", p1);
                    Cowboy enemy("Alice", p2);

                    n.move(&enemy); // Should move to the destination and not farther
                    CHECK_EQ(p2.getX(), n.getLocation().getX());
                    CHECK_EQ(p2.getY(), n.getLocation().getY());
                }

                SUBCASE("Dead ninja/enemy") {

                    Point p1(1.1, 2.2);
                    Point p2(5.0, 5.0);
                    OldNinja n("Master Splinter", p1);
                    OldNinja enemy("Alice", p2);

                    enemy.hit(200);
                    CHECK_FALSE(enemy.isAlive()); // Confirm the enemy is dead
                    CHECK_THROWS(n.move(&enemy)); // Trying to move to a dead enemy
                    CHECK_THROWS(enemy.move(&n)); // Trying to call move() from a dead ninja

                }

                SUBCASE("Move with the same ninja") {

                    Point p1(1.1, 2.2);
                    OldNinja n("Yaakov", p1);

                    CHECK_THROWS(n.move(&n));
                }
            }

            SUBCASE("Slash") {

                SUBCASE("The Ninja and the enemy are alive and within range to slash the enemy") {

                    Point p1(1.1, 2.2);
                    OldNinja n("Hamudi", p1);
                    Cowboy enemy("Bob", p1);

                    enemy.hit(137); // Enemy hitpoints 150 -> 13
                    CHECK(enemy.isAlive()); // Confirm enemy is alive
                    n.slash(&enemy);
                    CHECK_FALSE(enemy.isAlive()); // Enemy should be dead after slashing 13 hitpoints

                }

                SUBCASE("The Ninja and the enemy are alive but the ninja is too far to slash the enemy") {

                    Point p1(1.1, 2.2);
                    Point p2(50.0, 50.0);
                    OldNinja n("Hamudi", p1);
                    Cowboy enemy("Alice", p2);

                    enemy.hit(140); // Enemy hitpoints 150 -> 10
                    CHECK(enemy.isAlive()); // Confirm enemy is alive
                    n.slash(&enemy);
                    CHECK(enemy.isAlive()); // Enemy should remain alive since the ninja is too far
                }

                SUBCASE("Ninja/enemy is dead") {

                    Point p1(1.1, 2.2);
                    OldNinja n("Hamudi", p1);
                    OldNinja enemy("Alice", p1);

                    enemy.hit(249); // Enemy hitpoints 150 -> -99
                    CHECK_FALSE(enemy.isAlive()); // Confirm enemy is dead
                    n.slash(&enemy); // Enemy is already dead

                    string output = enemy.print();

                    bool containsRemainedHP = output.find("-99") != std::string::npos;
                    CHECK(containsRemainedHP); // Search for "-99" as the hitpoints value, since slashing a dead enemy remain his hitpoints as it was before
                    CHECK_THROWS(
                            enemy.slash(&n)); // Enemy ninja is dead already, should not be able to slash anyone

                }

            }

        }
    }

}