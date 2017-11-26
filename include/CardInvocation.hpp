#pragma once
#include "Card.hpp"
#include "CardEquipement.hpp"

class CardInvocation : public Card
{
public:
	CardInvocation(vili::ComplexAttribute& cardObject);
	unsigned int CardInvocation::getAtk() const;
	unsigned int CardInvocation::getDef() const;
	const std::vector<CardFamilies::CardFamily>& getFamilies() const;
	void equip(CardEquipement* equipement);
	const CardEquipement* getEquipement() const;

private:
	unsigned int m_atk;
	unsigned int m_def;
	std::vector<CardFamilies::CardFamily> m_families;
	CardEquipement* m_equipement;
};
