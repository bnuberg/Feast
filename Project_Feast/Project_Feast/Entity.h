#pragma once

class Entity
{
public:
	/*Health functions*/
	float GetHealth() const;
	void CheckHealth();
	void SetMaxHealth(float value);
	void SetHealth(float value);
	void IncreaseHealth(float value);
	void DecreaseHealth(float value);
	void IncreaseMaxHealth(float value);
	void DecreaseMaxHealth(float value);
	virtual void Die();
protected:
	float health;
	float maxHealth;

};