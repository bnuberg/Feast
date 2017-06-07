// unittest_Feast.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "gtest/gtest.h"

#include "Player.h"
#include "Rarity.h"

// Test the SetHealth and GetHealth methods
TEST(testPlayerHP, myPlayerHPTest)
{
	Player player = Player();

	float testHealth = 10;
	player.SetHealth(testHealth);

	// Health should equal the set health
    EXPECT_EQ(player.GetHealth(), testHealth);
}

// Test the DecreaseHealth method
TEST(testPlayerHPDecrease, myPlayerHPDecreaseTest)
{
	Player player = Player();

	float startHealth = 10;
	player.SetHealth(startHealth);

	float decrease = 5;
	player.DecreaseHealth(decrease);

	// Starting health is 10, decreased by 5 it should equal 5
	EXPECT_EQ(player.GetHealth(), 5);

	decrease = 50;
	player.DecreaseHealth(decrease);

	// Health is decreased by 50 but it can't go below 0
	EXPECT_EQ(player.GetHealth(), 0);
}

// Test the IncreaseHealth method
TEST(testPlayerHPIncrease, myPlayerHPIncreaseTest)
{
	Player player = Player();

	float startHealth = 10;
	player.SetHealth(startHealth);

	float decrease = 8;
	player.DecreaseHealth(decrease);

	float increase = 2;
	player.IncreaseHealth(increase);

	// Health has been decreased to 2, after increasing by 2 it should be 4
	EXPECT_EQ(player.GetHealth(), 4);

	increase = 50;
	player.IncreaseHealth(increase);

	// Health is increased by 50 but it can't exceed the starting health
	EXPECT_EQ(player.GetHealth(), startHealth);
}

TEST(testRarity, myRarityTest)
{
	Rarity rarity = Rarity();

	rarity.ApplyRarity(10, 5, 50, 30);

	ASSERT_LE(rarity.GetDamageValue(), 10);
	ASSERT_GE(rarity.GetDamageValue(), 5);
	ASSERT_LE(rarity.GetSpeedValue(), 50);
	ASSERT_GE(rarity.GetSpeedValue(), 30);
}