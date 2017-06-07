#pragma once

class Entity
{
public:
	/*Health functions*/
	float GetHealth() const;
	void SetHealth(float value);
	
	void SetMaxHealth(float value);
	void IncreaseHealth(float value);
	void DecreaseHealth(float value);
	void IncreaseMaxHealth(float value);
	void DecreaseMaxHealth(float value);
	void CheckHealth();
	virtual void Die();
protected:
	float health;
	float maxHealth;

};