#pragma once
class Player
{
public:
	Player();
	~Player();

	// Health functions
	float GetHealth();
	void SetHealth(float startingHealth);
	void IncreaseHealth(float heal);
	void DecreaseHealth(float dmg);
	void IncreaseMaxHealth(float permaHeal);
	void DecreaseMaxHealth(float permaDmg);

private:
	void Die();

	float health;
	float maxHealth;
};

